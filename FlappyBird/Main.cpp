#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace sf;
using namespace std;

// Function to check collision between bird and pipes
bool collides(FloatRect birdArea, FloatRect pipeArea)
{
    birdArea.left += 28.0f;
    birdArea.width -= 28.0f;
    birdArea.top += 28.0f;
    birdArea.height -= 28.0f;

    // Reduce the pipe's collision area from all sides
    pipeArea.left += 28.0f;
    pipeArea.width -= 28.0f;
    pipeArea.top += 28.0f;
    pipeArea.height -= 28.0f;
    // Returns true if the bird and pipe areas overlap
    return birdArea.intersects(pipeArea);
}

// Function to save the highest score in a file
void saveHighScore(int highScore)
{
    // Open highscore.txt in writing mode
    ofstream file("highscore.txt");
    if (file.is_open()) // check file is opened
    {
        file << highScore; // write highest score in the file
        file.close(); // close file after writing
    }
}

// Load high score from a file
int loadHighScore()
{
    ifstream file("highscore.txt");
    int highScore = 0; // firstly set highscore to zero
    if (file.is_open())
    {
        file >> highScore; // read the saved high score from the file
        file.close();
    }
    return highScore; // return the loaded highest score
}

int main()
{
    // Create the game window
    RenderWindow window(VideoMode(1000, 600), "Flappy Bird");
    window.setFramerateLimit(70); // Set the game speed to 70 frames per second
    srand(time(0)); // generate random numbers

    int highScore = loadHighScore();  // Load the previously saved high score

    const int MAX_PIPES = 100; // Maximum number of pipes allowed in the array
    Sprite pipes[MAX_PIPES];  // Array to store all pipe sprites
    int pipeCount = 0;

    bool pipeScored[MAX_PIPES] = { false }; // Track if the pipe pair was already scored

    Texture birdTexture, pipeTexture, backgroundTexture, gameOverTexture;
    // Load all game images from the assets folder
    if (!backgroundTexture.loadFromFile("./assets/background.png") ||
        !pipeTexture.loadFromFile("./assets/pipes.png") ||
        !gameOverTexture.loadFromFile("./assets/gameover1.jpg") ||
        !birdTexture.loadFromFile("./assets/bird.png"))
    {
        // Display an error if any image fails to load
        cout << "Error: Failed to load textures.\n";
        return -1;
    }

    Sprite flappy; // creating the bird sprite

    flappy.setTexture(birdTexture); //Attaching the bird image to the sprite

    flappy.setPosition(400.0f, 250.0f);//set starting position of bird

    flappy.setScale(0.5f, 0.5f);    // Reduce the bird's original size by half

    float flappyVelocity = 0.0f; //initially bird has 0 velocity
    const float gravity = 0.5f;   // Gravity continuously pulls the bird downward

    // Define the three possible states of the game
    enum GameState { lobby, started, gameover }
    gameState = lobby;

    int score = 0, frames = 0;

    Font font; // create a font object
    // Load the font from the assets folder
    if (!font.loadFromFile("./assets/timesnewroman.ttf"))
    {
        // Display an error if the font cannot be loaded
        cout << "Error: Failed to load font." << endl;
        return -1;
    }

    Music bgMusic;
    if (!bgMusic.openFromFile("./assets/bheem.ogg"))
    {
        cout << "Error: Failed to load music." << endl;
        return -1;
    }
    bgMusic.setLoop(true);
    bgMusic.setVolume(60);
    bgMusic.play();
    SoundBuffer fahBuffer, laughBuffer;
    if (!fahBuffer.loadFromFile("./assets/fah.wav") ||
        !laughBuffer.loadFromFile("./assets/catlaugh.wav"))
    {
        cout << "Error: Failed to load sound effects." << endl;
        return -1;
    }
    Sound fahSound(fahBuffer);
    Sound laughSound(laughBuffer);

    Clock deathClock;
    bool laughPlayed = false;

    //Creating text objs for current score and high score
    Text currentScore, highScoreText;
    currentScore.setFont(font);
    highScoreText.setFont(font);
    currentScore.setCharacterSize(30);
    highScoreText.setCharacterSize(30);
    currentScore.setFillColor(Color::Cyan);   // Set the current score text color to cyan
    highScoreText.setFillColor(Color::Cyan);  // Set the high score text color to cyan
    //setting positions of both current and high scores
    currentScore.setPosition(20.0f, 20.0f);
    highScoreText.setPosition(20.0f, 50.0f);

    // Create an array of three background sprites
    Sprite backgrounds[3];
    for (int i = 0; i < 3; i++)
    {
        // Set the same background image for all three sprites
        backgrounds[i].setTexture(backgroundTexture);
        // Place backgrounds next to each other
        backgrounds[i].setPosition(333.0f * i, 0.0f);
    }

    //Loading game over texture
    Sprite gameOverSprite;
    gameOverSprite.setTexture(gameOverTexture);
    // Set its position on the screen
    gameOverSprite.setPosition(275.0f, 125.0f);
    // Increase its size by 2 times
    gameOverSprite.setScale(2.0f, 2.0f);

    // Main agme loop start from here 
    while (window.isOpen())    // It continues running until the window is closed
    {
        Event event; // create event obj to detect user actions

        while (window.pollEvent(event))
        {

            // Check if the user clicks the close button
            if (event.type == Event::Closed)
            {
                window.close();
            }
            // Check if the user presses any keyboard key
            if (event.type == Event::KeyPressed)
            {
                // Handle space key
                if (event.key.code == Keyboard::Space)
                {
                    if (gameState == lobby)
                    {
                        gameState = started;
                    }

                    if (gameState == started)
                    {
                        flappyVelocity = -8.0f; //give bird upward movement
                    }
                }

                // Check if Enter is pressed after game over
                if (event.key.code == Keyboard::Enter && gameState == gameover)
                {
                    // Return the game to the starting screen
                    gameState = lobby;
                    flappy.setPosition(400.0f, 250.0f); // Set the bird back to its original position
                    flappyVelocity = 0.0f;
                    score = 0;
                    pipeCount = 0;

                    // Reset scored status for pipes
                    for (int i = 0; i < MAX_PIPES; i++)
                    {
                        pipeScored[i] = false;
                    }
                    bgMusic.play();
                    cout << "Game reset! Score: " << score << endl;
                }

                // Check if Escape is pressed on the lobby or game over screen
                if (event.key.code == Keyboard::Escape && (gameState == gameover || gameState == lobby))
                {
                    window.close(); // closing the window
                    cout << "Game closed by user." << endl;
                }
            }
        }
        // Run the following code only when the game has started
        if (gameState == started)
        {
            flappy.move(0.0f, flappyVelocity);
            flappyVelocity += gravity;             //first movement

            // Check if the bird goes above the screen
            if (flappy.getPosition().y < 0.0f)
            {
                // Bring the bird back to the top of the screen
                flappy.setPosition(400.0f, 0.0f);
                flappyVelocity = 0.0f;
            }
            // Check if the bird goes below the screen
            else if (flappy.getPosition().y > 600.0f)
            {
                gameState = gameover; // end the game
                bgMusic.stop();
                fahSound.play();
                deathClock.restart();
                laughPlayed = false;

                cout << "Game Over! Final Score: " << score << endl;
                // Check if the current score is greater than the high score
                if (score > highScore)
                {
                    //updates the high score
                    highScore = score;
                    saveHighScore(highScore);
                }
            }
            // Generate pipes after the score reaches 10
            if (score >= 10)
            {
                // Generate new pipes after every 80 frames
                // Also check that the pipe array has enough space

                if (frames % 80 == 0 && pipeCount + 2 < MAX_PIPES)
                {
                    // Set the vertical gap between the two pipes
                    int gap = 170;
                    // Generate a random vertical position for the pipes
                    int randomY = rand() % 300 + 75;

                    //settings for upper pipe
                    pipes[pipeCount].setTexture(pipeTexture);
                    pipes[pipeCount].setPosition(1000.0f, randomY + gap);
                    pipes[pipeCount].setScale(0.5f, 2.0f);  // Set its horizontal and vertical size

                    pipeScored[pipeCount] = false;  // Mark this pipe as not scored yet
                    pipeCount++;

                    //lower pipe
                    pipes[pipeCount].setTexture(pipeTexture);
                    pipes[pipeCount].setPosition(1000.0f, randomY);
                    pipes[pipeCount].setScale(0.5f, -2.0f);

                    pipeScored[pipeCount] = false; // Reset scored status
                    pipeCount++;
                }

            }
            // Generate pipes before the score reaches 10
            else if (frames % 150 == 0 && pipeCount + 2 < MAX_PIPES)
            {
                int gap = 170; // gap between 2 pipes
                int randomY = rand() % 300 + 75;

                // pipe settings

                //upper pipe
                pipes[pipeCount].setTexture(pipeTexture);
                pipes[pipeCount].setPosition(1000.0f, randomY + gap);
                pipes[pipeCount].setScale(0.5f, 2.0f);

                pipeScored[pipeCount] = false; // Reset scored status
                pipeCount++;

                //lower pipe
                pipes[pipeCount].setTexture(pipeTexture);
                pipes[pipeCount].setPosition(1000.0f, randomY);
                pipes[pipeCount].setScale(0.5f, -2.0f);

                pipeScored[pipeCount] = false; // Reset scored status
                pipeCount++;
            }

            // Move all pipes from right to left

            for (int i = 0; i < pipeCount; i++)
            {
                // If score is 10 or greater, increase pipe speed
                if (score >= 10)
                {
                    // Move the pipe 5 pixels to the left
                    pipes[i].move(-5.0f, 0.0f);
                }
                else
                {
                    // Move the pipe 3 pixels to the left
                    pipes[i].move(-3.0f, 0.0f);
                }
            }

            // Update the total number of remaining pipes
            int newPipeCount = 0;


            // Remove pipes that have moved outside the screen
            for (int i = 0; i < pipeCount; i++)
            {
                // Keep the pipe if its x-position is greater than -75
                if (pipes[i].getPosition().x > -75.0f)
                {
                    // Copy the remaining pipe to the next available position
                    pipes[newPipeCount++] = pipes[i];
                    pipeScored[newPipeCount - 1] = pipeScored[i]; // Maintain scored status
                }
            }
            // Update the total number of remaining pipes
            pipeCount = newPipeCount;

            // Increment score for each pipe pair passed
            for (int i = 0; i < pipeCount; i++)
            {
                if (i % 2 == 0)
                { // Only process lower pipes (even-indexed)
                    if (pipes[i].getPosition().x + 52.0f < flappy.getPosition().x && !pipeScored[i])
                    {
                        score++; // Increment score for the pipe pair
                        pipeScored[i] = true; // Mark the pipe as scored
                        cout << "Score: " << score << endl;
                    }
                }
            }

            // Check for collisions with pipes
            FloatRect birdBounds = flappy.getGlobalBounds();
            // Check every pipe in the array
            for (int i = 0; i < pipeCount; i++)
            {
                // Get the current pipe's collision rectangle
                FloatRect pipeBounds = pipes[i].getGlobalBounds();
                // Call the collision function to check overlap
                if (collides(birdBounds, pipeBounds))
                {
                    gameState = gameover; // end game if collide
                    bgMusic.stop();
                    fahSound.play();
                    deathClock.restart();
                    laughPlayed = false;

                    cout << "Game Over! Final Score: " << score << endl;
                    if (score > highScore)
                    {
                        highScore = score; // updating the high score
                        saveHighScore(highScore);
                    }
                }
            }
        }

        // Move the background only when the game is running or on the lobby screen
        if (gameState == started || gameState == lobby)
            for (int i = 0; i < 3; i++)
            {

                // Move each background sprite to the left
                backgrounds[i].move(-3.0f, 0.0f);
                // Check if the background has moved completely off the left side
                if (backgrounds[i].getPosition().x <= -333.0f)
                {
                    // Place it again at the right side of the screen
                    backgrounds[i].setPosition(667.0f, 0.0f);
                }
            }

        // Update the current score displayed on the screen
        // Convert the integer score into a string
        currentScore.setString("Score: " + to_string(score));

        highScoreText.setString("High Score: " + to_string(highScore));

        window.clear();    // Clear the previous frame from the window

        // Draw everything
         // Draw all three background sprites
        for (int i = 0; i < 3; i++)
        {
            window.draw(backgrounds[i]);
        }

        for (int i = 0; i < pipeCount; i++) //draw all the pipes
        {
            window.draw(pipes[i]);
        }

        window.draw(flappy); // draw the bird

        if (gameState == gameover)
        {
            if (deathClock.getElapsedTime().asSeconds() >= 1.0f)
            {
                window.draw(gameOverSprite);
                if (!laughPlayed)
                {
                    laughSound.play();
                    laughPlayed = true;
                }
            }
        }

        window.draw(currentScore);// Display the current score
        window.draw(highScoreText); // Display the highest score
        window.display(); // Show everything that was drawn on the screen
        frames++; // Increase the frame counter by one
    }

    return 0;
}
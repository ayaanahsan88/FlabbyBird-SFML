# 🐦 Flappy Bird – 2D Game Using C++ and SFML

## 📌 Project Overview

Flappy Bird is a 2D graphical user interface (GUI)-based game developed using **C++** and the **SFML (Simple and Fast Multimedia Library)**.

In this game, the player controls a bird that must fly through gaps between pipes without colliding with them. The bird is affected by gravity and continuously falls downward. The player must press the **Spacebar** to make the bird jump and stay in the air.

The player earns points by successfully passing through obstacles. If the bird collides with a pipe or the game window boundary, the game ends.

The game also includes a high-score system that saves the player's best score in a text file, allowing the player to try to beat their previous record.

This project demonstrates fundamental programming concepts such as variables, conditional statements, loops, functions, structures, event handling, collision detection, and file handling.

## 👨‍💻 Project Members

| Student Name | Roll Number |
|---|---|
| Muhammad Ayaan Ahsan | 26L-0818 |
| Abdul Raheem Bhatti | 26L-0819 |

## ✨ Features

- **Bird Movement:** The bird jumps whenever the player presses the Spacebar and falls due to gravity.
- **Pipe Generation:** Pipes continuously appear as obstacles with gaps for the bird to fly through.
- **Collision Detection:** The game detects collisions between the bird, pipes, and window boundaries.
- **Score System:** The player's score increases each time the bird successfully passes through a pair of pipes.
- **High-Score System:** The game saves the highest score in a text file named `highscore.txt` and loads it when the game starts.
- **Graphical User Interface:** SFML is used to display the bird, pipes, and score.
- **Game Over:** The game ends when the bird collides with an obstacle or a boundary.
- **Keyboard Controls:** The player uses the Spacebar to control the bird and Escape to exit the game.
- **Continuous Gameplay:** Pipes continuously move across the screen, challenging the player to avoid obstacles.

## 🛠️ Technologies Used

| Category | Technology |
|---|---|
| Programming Language | C++ |
| Graphics Library | SFML |
| Development Environment | Microsoft Visual Studio |
| Platform | Microsoft Windows |

### Programming Concepts

- Data Types and Variables
- Conditional Statements (if-else)
- Loops (for and while)
- Functions
- Structures
- Keyboard Event Handling
- Collision Detection
- File Handling with Text Files

## ⚙️ Installation and Setup

Follow these steps to install and run the project:

1. Install **Microsoft Visual Studio** and make sure the C++ development tools are included.
2. Install an SFML version compatible with your Visual Studio version.
3. Open the `Final Project.sln` file in Visual Studio.
4. Configure the SFML include and library directories in the project settings.
5. Select the **x64** build configuration and platform, ensuring that the SFML libraries match the selected configuration.
6. Make sure `highscore.txt` is present in the working directory. The game will create this file if it does not already exist.
7. Build the project in Visual Studio and run the application.

After completing these steps, the game will open in a graphical window, allowing the player to enjoy Flappy Bird.

## 🎮 How to Play

When the game starts, a window appears displaying the bird and pipes.

### Keyboard Controls

| Key | Action |
|---|---|
| Spacebar | Make the bird jump |
| Escape | Exit the game |

### Gameplay Steps

1. Run the application to open the game window.
2. The bird appears on the screen while pipes move across the playing area.
3. Press the Spacebar to make the bird jump.
4. Continue pressing the Spacebar at appropriate intervals to keep the bird in the air.
5. Guide the bird through the gaps between the pipes without hitting them.
6. Each successfully passed pair of pipes increases the score by one point.
7. Avoid colliding with pipes or the boundaries of the game window.
8. When a collision occurs, the game ends.
9. The game compares the current score with the saved high score and updates the record if the current score is higher.
10. Press Escape to exit the application.

## 🧪 Examples

### Example 1: Bird Movement
- **Input:** The player presses the Spacebar.
- **Expected Output:** The bird moves upward briefly before gravity pulls it downward again.

### Example 2: Passing Through Pipes
- **Input:** The player successfully guides the bird through a gap between two pipes.
- **Expected Output:** The bird continues flying, and the score increases by one point.

### Example 3: Collision with a Pipe
- **Input:** The bird collides with an obstacle.
- **Expected Output:** The game ends, and the final score is displayed if supported by the game interface.

### Example 4: Saving a High Score
- **Input:** The player finishes a game with a score higher than the previously saved record.
- **Expected Output:** The new highest score is saved in `highscore.txt` and can be loaded during a future session.

### Example 5: Loading a Previous High Score
- **Input:** The player launches the game after a previous session.
- **Expected Output:** The game reads the saved score from `highscore.txt` and displays it if supported by the interface.

### Example 6: Exiting the Game
- **Input:** The player presses Escape.
- **Expected Output:** The application closes.

## 📚 Acknowledgements

We would like to acknowledge the developers and maintainers of **SFML** for providing a graphics library that makes it possible to develop graphical applications and games using C++.

### Development Resources
- SFML Official Website: https://www.sfml-dev.org/

## 📞 Contact Information

**Muhammad Ayaan Ahsan**
- Roll Number: 26L-0818
- Email: l260818@lhr.nu.edu.pk

**Abdul Raheem Bhatti**
- Roll Number: 26L-0819
- Email: l260819@lhr.nu.edu.pk

## 📝 Project Summary

Flappy Bird is a 2D game developed using C++ and SFML. It provides an interactive graphical interface where players control a bird using keyboard inputs to avoid obstacles, detect collisions, track scores, and save their highest scores in a text file.

This project demonstrates how fundamental programming concepts can be combined to create an interactive and enjoyable game while providing practical experience with C++, graphical programming, and SFML.

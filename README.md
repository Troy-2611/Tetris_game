# Tetris Game

A classic Tetris game implementation in C++ using the terminal with colored Unicode blocks for a visually appealing experience. Built with object-oriented programming principles, this game includes all the standard Tetris mechanics like piece movement, rotation, and hard drops.

## Features
- **Colorful Tetrominoes**: Uses Unicode colored blocks (🟦, 🟨, 🟪, etc.) to represent different pieces.
- **Interactive Controls**: Move, rotate, and drop pieces with simple key presses.
- **Game Mechanics**: Includes piece rotation, hard drop, pause, restart, and exit functionality.
- **Dynamic Rendering**: Real-time updates in the terminal with a clean game board display.
- **Random Piece Generation**: Tetrominoes are spawned randomly for varied gameplay.

## Controls
| Key       | Action          |
|-----------|-----------------|
| `A`       | Move Left       |
| `D`       | Move Right      |
| `S`       | Move Down       |
| `W`       | Rotate Piece    |
| `Space`   | Hard Drop       |
| `P`       | Pause/Resume    |
| `R`       | Restart Game    |
| `X`       | Exit Game       |

## Prerequisites
- A C++ compiler (e.g., `g++`)
- A Unix-like terminal (Linux, macOS, or WSL on Windows) for proper rendering and input handling.
- Basic libraries: `<iostream>`, `<vector>`, `<cstdlib>`, `<ctime>`, `<unistd.h>`, `<termios.h>`, `<sys/ioctl.h>` (included in most Unix systems).

## Installation
1. **Clone or Download**: Save the code in a file named `tetris.cpp`.
2. **Compile the Code**:
   Open a terminal in the directory containing `tetris.cpp` and run:

## How to Play
- The game starts automatically with a random tetromino at the top of the board.
- Use the controls to move, rotate, or drop the pieces.
- Stack the pieces to fill the board without letting them reach the top.
- Press `P` to pause, `R` to restart, or `X` to exit at any time.

## Code Structure
- **`Tetromino` Class**: Manages the shape, position, and rotation of each piece.
- **`GameBoard` Class**: Handles the game grid, collision detection, and rendering.
- **`TetrisGame` Class**: Controls the game loop, input handling, and game state.

## Notes
- The game uses `usleep(500000)` for a 0.5-second delay between updates. Adjust this value in the `run()` function for faster or slower gameplay.
- Designed for terminals supporting Unicode and ANSI escape codes (e.g., most modern Linux/macOS terminals).
- Windows users may need to use WSL or a compatible terminal emulator for full functionality.

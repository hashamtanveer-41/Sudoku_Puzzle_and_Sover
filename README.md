# Sudoku Game Puzzle and Solver

This is a **C++ Sudoku game** with a graphical interface using the SFML library.  
The game allows users to play interactively, auto-solve puzzles, and select different difficulty levels.  
It also tracks solver statistics such as attempts, backtracks, and time taken.



## Team Members

1. **Hasham Tanveer**  (Team Lead and Logic Builder)
2. **Muhammad Hamza** (Documentation and GUI)
3. **Asfand Khan** (Tester)


## Features

- **Interactive GUI** 
- **Difficulty Levels**
- **Auto-Solver**
- **Reset**  
- **Completion Detection** 
- **Visual Highlights** 

## Instructions

1. Start the game.  
2. Generate a puzzle of the desired difficulty level.  
3. Click a cell and enter the **row**.  
4. Enter the **column**.  
5. Enter the **value**.  
6. Enter `0` at any point to quit.  
7. Press the solver function to auto-solve the puzzle anytime.  


## Functions Overview

| Function | Description |
|----------|-------------|
| `solveSudoku(int arr[9][9], int row, int col)` | Solves the puzzle recursively using backtracking. |
| `makePuzzle(int arr[9][9], int holes)` | Generates a solvable puzzle with a specified number of empty cells. |
| `isValid(int arr[9][9], int row, int col, int num)` | Checks if a number can be placed in a cell according to Sudoku rules. |
| `rowCheck`, `columnCheck`, `boxChecker` | Helper functions used to validate moves. |


## Example Gameplay


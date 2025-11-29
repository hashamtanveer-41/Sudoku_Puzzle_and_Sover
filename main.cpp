#include <iostream>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <string> // needed for GUI text
#include <SFML/Graphics.hpp> // adding sfml library

using namespace std;


// Global variable and constants
const int size1 = 9;

// these function wil check the attempts, upon each attempt becomes attempt++
// and backtracks also goes the same
int attempts = 0;
int backtracks = 0;

// Function prototypes
bool rowCheck(int arr[][size1], int row, int num);
bool columnCheck(int arr[][size1], int col, int num);
bool boxChecker(int arr[][size1], int row, int col, int num);
bool isValid(int arr[][size1], int row, int col, int num);
bool solveSudoku(int arr[][size1], int row, int col);
void printArr(int arr[][size1]);
void randomNumbers(int nums[]);
void makePuzzle(int arr[][size1], int holes);

// these three functions were made by ASFAND
bool isBoardFull(int arr[][size1]); // checks if all the entries are full
void playGame(int arr[][size1]); // makes user enter the values and quit the game by breaking the loop
void printStats(double timeTaken); // prints game stats in the end like time,attempts,backtracks etc

// constants for the gui window
const int CELL_SIZE = 60;
const int GRID_SIZE = 9;
const int SCREEN_SIZE = CELL_SIZE * GRID_SIZE;
const int BOTTOM_BAR = 120; // increased space for difficulty instructions

int main() {
    srand(time(0));

    // creating the window with fixed size so grid calculation stays correct
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE + BOTTOM_BAR), "Sudoku Game", sf::Style::Titlebar | sf::Style::Close);

    // loading font for numbers
    sf::Font font;
    // trying local file first, then system file
    if (!font.loadFromFile("arial.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            
        }
    }

    int board[9][9] = { 0 };
    bool gameWon = false; // flag to track if user completed the puzzle

    // generating initial puzzle (defaulting to Medium/30 holes like option 2)
    makePuzzle(board, 30);

    // variables for mouse selection
    int selectedRow = -1;
    int selectedCol = -1;

    // main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // handling mouse clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // getting exact mouse position relative to window view
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                    int col = worldPos.x / CELL_SIZE;
                    int row = worldPos.y / CELL_SIZE;

                    // checking if click is inside grid area
                    if (row >= 0 && row < 9 && col >= 0 && col < 9) {
                        selectedRow = row;
                        selectedCol = col;
                        gameWon = false; // reset win message if player keep clicking
                    }
                    else {
                        // Clicking outside deselects (allows changing difficulty)
                        selectedRow = -1;
                        selectedCol = -1;
                    }
                }
            }

            // handling keyboard inputs
            if (event.type == sf::Event::KeyPressed) {
                // enter key solves the board
                if (event.key.code == sf::Keyboard::Enter) {
                    attempts = 0;
                    backtracks = 0;
                    clock_t start = clock();

                    solveSudoku(board, 0, 0);

                    clock_t end = clock();
                    double timeTaken = double(end - start) / CLOCKS_PER_SEC;
                    printStats(timeTaken);
                    gameWon = true; // Auto-solve counts as winning/completed
                }

                // DIFFICULTY LEVELS
                // Only allow changing difficulty if NO CELL is selected
                // This prevents accidentally resetting the board when trying to type 1, 2, or 3
                if (selectedRow == -1 && selectedCol == -1) {
                    // Press 1 for Easy (25 holes)
                    if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                        makePuzzle(board, 25);
                        gameWon = false;
                        cout << "Generated Easy Puzzle (25 holes)" << endl;
                    }
                    // Press 2 for Medium (30 holes)
                    if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                        makePuzzle(board, 30);
                        gameWon = false;
                        cout << "Generated Medium Puzzle (30 holes)" << endl;
                    }
                    // Press 3 for Difficult (40 holes)
                    if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                        makePuzzle(board, 40);
                        gameWon = false;
                        cout << "Generated Difficult Puzzle (40 holes)" << endl;
                    }
                }

                // R key resets the board
                if (event.key.code == sf::Keyboard::R) {
                    for (int i = 0; i < 9; i++)
                        for (int j = 0; j < 9; j++)
                            board[i][j] = 0;
                    gameWon = false;
                }
            }

            // handling number typing
            if (event.type == sf::Event::TextEntered) {
                if (selectedRow != -1 && selectedCol != -1) {
                    // checking if input is number 1-9
                    if (event.text.unicode >= '1' && event.text.unicode <= '9') {
                        int num = event.text.unicode - '0';

                        // using the logic to check if move is valid
                        if (isValid(board, selectedRow, selectedCol, num)) {
                            board[selectedRow][selectedCol] = num;

                            // CHECKING FOR COMPLETION (Restored Feature)
                            if (isBoardFull(board)) {
                                gameWon = true;
                                cout << "Puzzle Completed! Great job!" << endl;
                            }
                        }
                        else {
                            cout << "invalid move at " << selectedRow << ", " << selectedCol << endl;
                        }
                    }
                    // checking for backspace to delete
                    else if (event.text.unicode == 8) {
                        board[selectedRow][selectedCol] = 0;
                        gameWon = false;
                    }
                }
            }
        }

        // drawing section
        window.clear(sf::Color::White);

        // drawing green highlight for selected cell
        if (selectedRow != -1 && selectedCol != -1) {
            sf::RectangleShape highlight(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            highlight.setPosition(selectedCol * CELL_SIZE, selectedRow * CELL_SIZE);
            highlight.setFillColor(sf::Color(190, 255, 200));
            window.draw(highlight);
        }

        // drawing grid lines
        for (int i = 0; i <= 9; i++) {
            // vertical lines
            sf::RectangleShape vLine(sf::Vector2f(2, SCREEN_SIZE));
            vLine.setPosition(i * CELL_SIZE, 0);
            // making 3x3 borders thicker and black
            if (i % 3 == 0) {
                vLine.setFillColor(sf::Color::Black);
                vLine.setSize(sf::Vector2f(4, SCREEN_SIZE));
            }
            else {
                vLine.setFillColor(sf::Color(192, 192, 192));
            }
            window.draw(vLine);

            // horizontal lines
            sf::RectangleShape hLine(sf::Vector2f(SCREEN_SIZE, 2));
            hLine.setPosition(0, i * CELL_SIZE);
            if (i % 3 == 0) {
                hLine.setFillColor(sf::Color::Black);
                hLine.setSize(sf::Vector2f(SCREEN_SIZE, 4));
            }
            else {
                hLine.setFillColor(sf::Color(192, 192, 192));
            }
            window.draw(hLine);
        }

        // drawing numbers on the board
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != 0) {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(to_string(board[i][j]));
                    text.setCharacterSize(32);
                    text.setFillColor(sf::Color::Black);
                    // centering numbers
                    text.setPosition(j * CELL_SIZE + 20, i * CELL_SIZE + 10);
                    window.draw(text);
                }
            }
        }

        // drawing bottom info panel
        sf::RectangleShape infoPanel(sf::Vector2f(SCREEN_SIZE, BOTTOM_BAR));
        infoPanel.setPosition(0, SCREEN_SIZE);

        // Change color to green if game is won
        if (gameWon) {
            infoPanel.setFillColor(sf::Color(200, 255, 200));
        }
        else {
            infoPanel.setFillColor(sf::Color(220, 220, 220));
        }
        window.draw(infoPanel);

        sf::Text instructions;
        instructions.setFont(font);
        instructions.setCharacterSize(18);
        instructions.setFillColor(sf::Color::Black);
        instructions.setPosition(10, SCREEN_SIZE + 10);

        if (gameWon) {
            instructions.setString("PUZZLE COMPLETED! GREAT JOB!\nPress [1], [2], or [3] for a new game.");
            instructions.setCharacterSize(24);
            instructions.setStyle(sf::Text::Bold);
        }
        else {
            instructions.setString("DIFFICULTY: [1] Easy  [2] Medium  [3] Hard\nClick cell + Type 1-9 to fill\n[ENTER] Auto-Solve    [R] Clear");
        }
        window.draw(instructions);

        window.display();
    }

    return 0;
}



//LOGIC FUNCTIONS BELOW

bool rowCheck(int arr[][size1], int row, int num) {
    for (int col = 0; col < 9; col++)
        if (arr[row][col] == num)
            return false;
    return true;
}

bool columnCheck(int arr[][size1], int col, int num) {
    for (int row = 0; row < 9; row++)
        if (arr[row][col] == num)
            return false;
    return true;
}

bool boxChecker(int arr[][size1], int row, int col, int num) {
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (arr[startRow + i][startCol + j] == num)
                return false;
    return true;
}

void printArr(int arr[][size1]) {
    cout << "\nGenerated Sudoku:\n\n";
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << arr[i][j] << " ";
            if (j % 3 == 2) cout << "  ";
        }
        cout << "\n";
        if (i % 3 == 2) cout << "\n";
    }
}

void randomNumbers(int nums[]) {
    for (int i = 0; i < 9; i++)
        nums[i] = i + 1;
    random_shuffle(nums, nums + 9);
}

bool isValid(int arr[][size1], int row, int col, int num) {
    return columnCheck(arr, col, num) && rowCheck(arr, row, num) && boxChecker(arr, row, col, num);

}

void makePuzzle(int arr[][size1], int holes) {
    // clearing board first to ensure clean generation
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            arr[i][j] = 0;

    solveSudoku(arr, 0, 0);

    while (holes--) {
        int r = rand() % 9;
        int c = rand() % 9;

        if (arr[r][c] != 0)
            arr[r][c] = 0;
        else
            holes++;
    }
}
bool solveSudoku(int arr[][size1], int row, int col) {
    if (row == 9) return true;

    if (col == 9) return solveSudoku(arr, row + 1, 0);

    if (arr[row][col] != 0)
        return solveSudoku(arr, row, col + 1);

    int nums[9];
    randomNumbers(nums);

    for (int i = 0; i < 9; i++) {
        int num = nums[i];
        attempts++;

        if (isValid(arr, row, col, num)) {
            arr[row][col] = num;

            if (solveSudoku(arr, row, col + 1))
                return true;

            arr[row][col] = 0;
            backtracks++;
        }
    }
    return false;
}

// initialized by ASFAND
bool isBoardFull(int arr[][size1]) {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (arr[i][j] == 0)
                return false;
    return true;
}

// initialized by ASFAND
// note: this function is kept but replaced by gui interactions in main
void playGame(int arr[][size1]) {
    int row, col, num;

    cout << "\n--- INTERACTIVE SUDOKU MODE ---\n";
    cout << "Enter values step-by-step.\n";
    cout << "Enter row, then column, then value.\n";
    cout << "Enter 0 to quit at any time.\n";

    while (true) {

        printArr(arr);

        if (isBoardFull(arr)) {
            cout << "Puzzle Completed! Great job!\n";
            break;
        }

        cout << "Enter row (1-9): ";
        cin >> row;

        if (row == 0) {
            cout << "Exiting game.\n";
            break;
        }

        cout << "Enter column (1-9): ";
        cin >> col;

        if (col == 0) {
            cout << "Exiting game.\n";
            break;
        }

        cout << "Enter value (1-9): ";
        cin >> num;

        if (num == 0) {
            cout << "Exiting game.\n";
            break;
        }

        row--;
        col--;

        if (row < 0 || row >= 9 || col < 0 || col >= 9) {
            cout << "Invalid row or column.\n";
            continue;
        }

        if (arr[row][col] != 0) {
            cout << "Cell already filled. Try another.\n";
            continue;
        }

        if (num < 1 || num > 9) {
            cout << "Invalid number.\n";
            continue;
        }

        if (!isValid(arr, row, col, num)) {
            cout << "Invalid move! Violates Sudoku rules.\n";
            continue;
        }

        arr[row][col] = num;
        cout << "Value added.\n";
    }
}

// prints the final results eg stats.
void printStats(double timeTaken) {
    cout << "\n--- SOLVER STATS ---\n";
    cout << "Time taken: " << timeTaken << " seconds\n";
    cout << "Attempts: " << attempts << "\n";
    cout << "Backtracks: " << backtracks << "\n";
}
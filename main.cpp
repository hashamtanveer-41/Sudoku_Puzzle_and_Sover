#include <iostream>
#include <algorithm>
#include <ctime>
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

int main() {
    srand(time(0));

    int board[size1][size1] = {0};

    clock_t start = clock();
    solveSudoku(board, 0, 0);
    clock_t end = clock();

    double timeTaken = double(end - start) / CLOCKS_PER_SEC;

    cout << "\n\n--- FULL SOLVED BOARD ---\n";
    printArr(board);
    printStats(timeTaken);

    makePuzzle(board, 40);

    cout << "\n--- PUZZLE WITH HOLES ---\n";
    printArr(board);

    playGame(board);
    solveSudoku(board, 0, 0);
    printArr(board);
    makePuzzle(board, 40); 
    printArr(board);
    return 0;
}

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
    return columnCheck(arr, col, num)&& rowCheck(arr, row, num)&& boxChecker(arr, row, col, num);

}

void makePuzzle(int arr[][size1], int holes) {
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
        randomNumbers(nums);

        for (int i = 0; i < 9; i++) {
            int num = nums[i];

            if (isValid(arr, row, col, num)) {
                arr[row][col] = num;

                if (solveSudoku(arr, row, col + 1))
                    return true;

                backtracks++;
            }
        }

        arr[row][col] = 0;
        return false;
    }
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

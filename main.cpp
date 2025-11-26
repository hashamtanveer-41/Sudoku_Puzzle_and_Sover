#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;


// Global variable declaration
const int size1 = 9;

// Function prototypes
bool rowCheck(int arr[][size1], int , int);
bool columnCheck(int arr[][size1], int , int );
bool boxChecker(int arr[][size1], int , int , int);
void printArr(int arr[][size1]);
bool isValid(int arr[][size1], int , int , int);
void randomNumbers(int nums[]);
void makePuzzle(int arr[][size1], int holes);
bool solveSudoku(int arr[][size1], int row, int col) ;
int main() {
    srand(time(0));

    int board[size1][size1] = {0};

    solveSudoku(board, 0, 0); // generate solved board

    printArr(board);

    makePuzzle(board, 40); // remove 40 cells for puzzle

    printArr(board);

    return 0;
}

bool rowCheck(int arr[][9], int row, int num) {
    for (int col= 0; col< 9 ; col++) {
        if (num ==arr[row][col]) {
            return true;
        }
    }
    return false;
}

bool columnCheck(int arr[][9], int num, int col){
    for ( int row= 0; row< 9 ; row++) {
        if (num ==arr[row][col]) {
            return true;
        }
    }
    return false;
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
bool isValid(int arr[][size1], int row, int col, int num) {
    return columnCheck(arr, col, num)&& rowCheck(arr, row, num)&& boxChecker(arr, row, col, num);

}
void randomNumbers(int nums[]) {
    for (int i = 0; i < 9; i++)
        nums[i] = i + 1;

    random_shuffle(nums, nums + 9);
}
void makePuzzle(int arr[][size1], int holes) {
    while (holes--) {
        int r = rand() % 9;
        int c = rand() % 9;

        if (arr[r][c] != 0)
            arr[r][c] = 0;
        else
            holes++;   // try again
    }
}
bool solveSudoku(int arr[][size1], int row, int col) {
    if (row == 9) return true;

    if (col == 9) return solveSudoku(arr, row + 1, 0);

    if (arr[row][col] != 0)
        return solveSudoku(arr, row, col + 1);

    int nums[9];
    randomNumbers(nums);   // <-- shuffle numbers each call

    for (int i = 0; i < 9; i++) {
        int num = nums[i];

        if (isValid(arr, row, col, num)) {
            arr[row][col] = num;

            if (solveSudoku(arr, row, col + 1))
                return true;
        }
    }

    arr[row][col] = 0;
    return false;
}

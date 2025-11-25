#include <iostream>
using namespace std;


// Global variable declaration
const int size1 = 9;
const int r = 9;
const int c = 9;

// Function prototypes
bool rowCheck(int arr[][size1], int , int);
bool columnCheck(int arr[][size1], int , int );
bool boxChecker(int arr[][size1], int , int , int);
void printArr(int arr[][size1], int i_a[][size1]);
bool isValid(int arr[][size1], int , int , int);

int main() {
    srand(time(0));
    int board[size1][size1] = { { rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9},
    { rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9},
    { rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9},
    { rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9},
    { rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9},
    { rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9},
    { rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9},
    { rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9},
    { rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9}};
    printArr(board, board);
    return 0;
}

bool rowCheck(int arr[][9], int num, int row) {
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
bool boxChecker(int arr[][size1], int row, int col, int num){

    int box;
    if (row<= 2 && row>= 0 && col>= 0 && col <= 2)
    {
        box = 1;
        for (int i = 0; i <= 2; i++){
            for (int j = 0; j <= 2; j++){
                if (num == arr[i][j]){
                    return true;
                }
            }
        }
        return false;
    }
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
bool boxChecker(int arr[][size1], int row, int col, int num) {
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

        if (row <= 2 && row >= 0 && col > 2 && col <= 5){
            box = 2;
            for (int i = 0; i <= 2; i++){
                for (int j = 3; j <= 5; j++){
                    if (num == arr[i][j]){
                        return true;
                    }
                }
            }
            return false;
        }

        if (row <= 2 && row >= 0 && col > 5 && col <= 8){
            box = 3;
            for (int i = 0; i <= 2; i++){
                for (int j = 6; j <= 8; j++){
                    if (num == arr[i][j]){
                        return true;
                    }
                }
            }
            return false;
        }

        //pt2
        if (row <= 5 && row > 2 && col >= 0 && col <= 2)
        {
            box = 4;
            for (int i = 3; i <= 5; i++){
                for (int j = 0; j <= 2; j++){
                    if (num == arr[i][j]){
                        return true;
                    }
                }
            }
            return false;
        }

        if (row <= 5 && row > 2 && col > 2 && col <= 5)
        {
            box = 5;
            for (int i = 3; i <= 5; i++){
                for (int j = 3; j <= 5; j++){
                    if (num == arr[i][j]){
                        return true;
                    }
                }
            }
            return false;
        }

        if (row <= 5 && row > 2 && col > 5 && col <= 8)
        {
            box = 6;
            for (int i = 3; i <= 5; i++){
                for (int j = 6; j <= 8; j++){
                    if (num == arr[i][j]){
                        return true;
                    }
                }
            }
            return false;
        }

        //pt3
        if (row <= 8 && row > 5 && col >= 0 && col <= 2){
            box = 7;
            for (int i = 6; i <= 8; i++){
                for (int j = 0; j <= 2; j++){
                    if (num == arr[i][j]){
                        return true;
                    }
                }
            }
            return false;
        }

        if (row <= 8 && row > 5 && col > 2 && col <= 5)
        {
            box = 8;
            for (int i = 6; i <= 8; i++){
                for (int j = 3; j <= 5; j++){
                    if (num == arr[i][j]){
                        return true;
                    }
                }
            }
            return false;
        }

        if (row <= 8 && row > 5 && col > 5 && col <= 8){
            box = 9;
            for (int i = 6; i <= 8; i++){
                for (int j = 6; j <= 8; j++){
                    if (num == arr[i][j]){
                        return true;
                    }
                }
            }
            return false;
        }
        return false;
    }
}

void printArr(int arr[][size1], int i_a[][size1]){
    cout << "\n";
    cout << "\n";
    cout << "\t";
    cout << "   ";
    for (int i = 1; i <= size1; i++) {
        cout << i << " ";
        if (i == 3){
            cout <<"  ";
        }
        if (i == 6) {
            cout << "  ";
        }
    }
    cout << "\n";
    cout << "\t";

    for (int i = 0; i < 25; i++){
        cout << "_";
    }
    cout << endl;
    cout << "\t";
    for (int i = 0; i < 25; i++){
        cout << "-";
    }
    cout << "\n";

    for (int i = 0; i < size1; i++){
        cout << "\t" << i + 1;
        cout << "| ";

        for (int j = 0; j < 9; j++){
            cout << arr[i][j] << " ";
            if (j == 2 || j == 5 || j == 8){
                cout << "| ";
            }
        }
        cout << endl;

        if (i == 2 || i == 5 || i == 8){
            cout << "\t";
            for (int i = 0; i <= 25; i++){
                cout << "_";
            }
            cout << endl;
            cout << "\t";
            for (int i = 0; i < 25; i++){
                cout << "-";
            }
            cout << "\n";
        }
    }
}

bool isValid(int arr[][size1], int row, int col, int num) {
    if (columnCheck(arr, row, col)&& rowCheck(arr, row, col)&& boxChecker(arr, row, col, num)) {
        return true;
    }
    return false;
}
#include <iostream>
using namespace std;

int main() {


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

    return 0;
}
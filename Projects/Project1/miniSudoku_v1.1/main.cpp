/*
Author: Lucy Blanks
Date:5/5/2026
Purpose: Mini-Sudoku: 6x6

//v.1.1 ~ Basic Board Generation
        generating a row of numbers and making sure each one is unique - DONE!
        turning this algorithm into a function                         - DONE!
        create rows via structures? 6-D vectors? (multi-d vector)      - DONE!    
        validate columns and rows functions                            - DONE!
        BUG: isInRow && isInCol not working, || creates ∞ loop         - FIXED!
        BUG: Board keeps getting turned to zeroes                      - FIXED!
*/

//system libraries
#include <iostream> //input/output library
#include <iomanip> //formatting library
#include <cstdlib> //random library
#include <vector> //vector library
using namespace std; //using namepace standard

//user libaries

// global constant not variable
//science, math, conversion, dimension

//function prototypes
bool isInRow(vector<vector<int>>&, int, int);
bool isInCol(vector<vector<int>>&, int, int);
void genBrd(vector<vector<int>>&);
void prtBrd(vector<vector<int>>&);

//execution begins here at main
int main( int argc, char **argv ) {
    //set random number seed
    srand(time(0));

    //declare variables
    vector<vector<int>> board(6, vector<int>(6,0));

    //display input/outputs
    genBrd(board);
    prtBrd(board);
    
    //clean up memory, close files

    //exit the program
    return 0;
}

bool isInRow(vector<vector<int>> &vec, int row, int n) {
    for (int i = 0; i < 6; i++) {
        if (vec[row][i] == n) {
            return true;
        }
    }

  return false;
}

bool isInCol(vector<vector<int>> &vec, int col, int n) {
    for (int i = 0; i < 6; i++) {
        if (vec[i][col] == n) {
            return true;
        }
    }

  return false;
}

void genBrd(vector<vector<int>> &b) {
    //declare variables
    int digit;

    //fill vector, validate rows are unique numbers
     for (int i = 0; i < 6; i++){ 
        for (int j = 0; j < 6; j++) {
            //declare variables
            bool failed = false;
            int tries = 0;

            do {
                //generate random number
                digit = rand() % 6 + 1;
                tries++;

                //backtrack
                if (tries > 1000) {
                    for (int k = 0; k < 6; k++) {
                             b[i][k] = 0;
                    }
                    j = -1;
                    tries = 0;
                    failed = true;
                    break;
                }

           } while (isInRow(b, i, digit) || isInCol(b, j, digit));

           if (!failed) {
            b[i][j] = digit;
           }
         }
    }
}

void prtBrd(vector<vector<int>> &b){
    cout << "----------------" << endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            cout << b[i][j] << "  ";
        }
        cout << endl;
    }
  cout << "----------------" << endl;
}

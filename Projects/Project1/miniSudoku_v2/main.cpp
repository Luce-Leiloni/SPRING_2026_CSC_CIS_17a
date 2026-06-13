/*
Author: Lucy Blanks
Date:5/6/2026
Purpose: Mini-Sudoku: 6x6

//v.2 ~ Advanced Board Generation
        validate 2x3 boxes                                             - DONE!
        empty random vectors with 0                                    - DONE!
        leave an empty space for every element that is 0               - DONE!
        add dividers for board                                         - DONE!
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
bool isInBox(vector<vector<int>>&, int, int, int);
void genBrd(vector<vector<int>>&);
void filZero(vector<vector<int>> &vec);
void prtBrd(vector<vector<int>>&);

//execution begins here at main
int main( int argc, char **argv ) {
    //set random number seed
    srand(time(0));

    //declare variables
    vector<vector<int>> board(6, vector<int>(6,0));

    //display input/outputs
    genBrd(board);
    filZero(board);
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

bool isInBox(vector<vector<int>> &vec, int row, int col, int n) {
    //declare variables
    int rBox = row - (row % 2);
    int cBox = col - (col % 3);

    //verify 2x3 box
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            if (vec[rBox + i][cBox + j] == n) {
                return true;
            }
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

           } while (isInRow(b, i, digit) || isInCol(b, j, digit) || isInBox (b, i, j, digit));

           if (!failed) {
            b[i][j] = digit;
           }
         }
    }
}

void filZero(vector<vector<int>> &vec) {
    //declare variables
    int count = 0;

    while (count < 15) {
        //geneate random row and column to pick from
        int r = rand() % 6;
        int c = rand() % 6;

        //fill chosen element to be zero
        if (vec[r][c] != 0) {
            vec[r][c] = 0;
            count++;
        }

    }

}

void prtBrd(vector<vector<int>> &b){
    //top of board
    cout << "---------------------" << endl;
    
    for (int i = 0; i < 6; i++) {
        
            //horizontal divider
            if (i % 2 == 0 && i > 0) {
                cout << "|---------|---------|" << endl;
            }

        for (int j = 0; j < 6; j++) {

            //vertical divider
            if (j % 3 == 0) {
                cout << "|";
            }

            //display sign if there is an empty space
            if (b[i][j] == 0) {
                cout << " - ";
            } else {
                cout << " " << b[i][j] << " ";
            }

        }
        //separate rows and skip lines
        cout << "|" << endl;
    }
  
  //bottom of board
  cout << "---------------------" << endl;
}

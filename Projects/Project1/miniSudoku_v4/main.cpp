/*
Author: Lucy Blanks
Date:5/6/2026
Purpose: Mini-Sudoku: 6x6

//v.4 ~ Locating and filling in elements
        create inputs to locate rows and columns                       - DONE!
        create input for user to enter number                          - DONE!
        verify the user got the correct answer                         - DONE!
        manage loop until board is solved                              - DONE!
        update board for each answer correct                           - DONE!
        Game is now fully functional!
*/

//system libraries
#include <iostream> //input/output library
#include <iomanip> //formatting library
#include <cstdlib> //random library
#include <vector> //vector library
using namespace std; //using namepace standard

//structures
struct board {
    vector<vector<int>> solved;
    vector<vector<int>> puzzle;

};

//function prototypes
bool isInRow(vector<vector<int>>&, int, int);
bool isInCol(vector<vector<int>>&, int, int);
bool isInBox(vector<vector<int>>&, int, int, int);
bool correct (board &, int, int, int);
void genBrd(vector<vector<int>>&);
void filZero(vector<vector<int>> &vec);
void prtBrd(vector<vector<int>>&);
void solve(board &, int, int, int);

//execution begins here at main
int main( int argc, char **argv ) {
    //set random number seed
    srand(time(0));

    //declare variables
    int rowIn;
    int colIn;
    int numIn;

    //initialize variables
    board sudoku;
    sudoku.solved.assign(6, vector<int>(6,0));
    sudoku.puzzle.assign(6, vector<int>(6,0));

    //display input/outputs
    genBrd(sudoku.solved);

    //match boards
    sudoku.puzzle = sudoku.solved;

    //create and print puzzle based on complete board
    filZero(sudoku.puzzle);
    prtBrd(sudoku.puzzle);

    cout << endl;

    //play game until solved
    do {
    solve(sudoku, rowIn, colIn, numIn);
    prtBrd(sudoku.puzzle);
    } while (sudoku.puzzle != sudoku.solved);

    cout << "You win!!"
   
    //clean up memory, close files

    //exit the program
    return 0;
}

//functions

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

bool correct (board &b, int r, int c, int n) {
    if (b.solved[r][c] == n) {
        return true;
    } else {
        return false;
    }
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

void solve (board &b, int r, int c, int n) {
    //collect values from user
    //collect rows
    do {
        cout << "Enter row:" << endl;
        cin >> r;
    } while (r > 6 || r <= 0);

    //collect columns
    do {
        cout << "Enter column:" << endl;
        cin >> c;
    } while (c > 6 || c <= 0);

    //verify numbers
    if (b.puzzle[r - 1][c - 1] != 0) {
        cout << "There is already a number there!" << endl;
    } else {
        cout << "Enter value:" << endl;
        cin >> n;
        
        if (correct(b, r - 1, c - 1, n) == true) {
            cout << "You got it!" << endl;
            b.puzzle[r - 1][c - 1] = n;
        } else {
            cout << "Incorrect!" << endl;
        }
    }

}

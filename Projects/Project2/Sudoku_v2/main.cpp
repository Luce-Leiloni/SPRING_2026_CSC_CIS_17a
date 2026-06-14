/*
Author: Lucy Blanks
Date: 6/12/2026
Purpose: Sudoku 9x9

//v.2 ~ Class implimentation
        change all instances of 6 to 9                                 - DONE!
        transfer structures and function so sudoku.h file              - DONE!
        create new function setBoard                                   - DONE!
        impliment sudoku.cpp file                                      - DONE!
*/

//system libraries
#include <iostream> //input/output library
#include <iomanip> //formatting library
#include <cstdlib> //random library
#include <vector> //vector library
#include <fstream> //file library
#include <ctime> //time library
#include <cstring> //string library
using namespace std; //using namepace standard

//user libraries
#include "sudoku.h"

//execution begins here at main
int main(int argc, char **argv ) {
    //set random number seed
    srand(time(0));

    //declare variables
    int rowIn;
    int colIn;
    int numIn;

    //introduce program
    cout << endl;
    cout << "SUDOKU" << endl;

    Player p;

    //play game
    p.getFile();
    p.menu(rowIn, colIn, numIn);

    //exit the program
    return 0;
}

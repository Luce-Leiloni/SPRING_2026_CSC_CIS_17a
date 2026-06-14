/*
Author: Lucy Blanks
Date: 6/14/2026
Purpose: Sudoku 9x9

//v.3 ~ difficulty implimentation
        change all instances of 6 to 9                                 - DONE!                                          
        create protected class members                                 - DONE!
        create difficulty function and amtZeroes int                   - DONE!
        impliment throwing in save and load                            - DONE!
        implimented difficulty into setBoard                           - DONE!
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

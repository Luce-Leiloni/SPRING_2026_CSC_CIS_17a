/*
Author: Lucy Blanks
Date: 6/14/2026
Purpose: Sudoku 9x9

//v.5 ~ Bug fixes                                      
        BUG: when save.txt is not present, program terminates          - FIXED!
        BUG: Difficulty is prompted before game begins                 - FIXED!
        adjust menu so 6 is exit                                       - DONE!
        BUG: reset strikes upon losing once                            - FIXED!
        load and save wins, losses, and og puzzle board                - DONE!
        
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

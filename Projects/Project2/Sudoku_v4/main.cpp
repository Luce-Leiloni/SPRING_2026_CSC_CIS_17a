/*
Author: Lucy Blanks
Date: 6/14/2026
Purpose: Sudoku 9x9

//v.4 ~ Win/loss track                                      
        added class members wins, loss, strike                         - DONE!
        added new vector to keep original puzzle                       - DONE!
        add 1 to losses for every incorrect answer                     - DONE!
        print how many mistakes out of 3 the player has made           - DONE!
        turn play void into bool                                       - DONE!
        catch loss if player makes 3 incorrect answers                 - DONE!
        add a "how to play" page                                       - DONE!
        
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

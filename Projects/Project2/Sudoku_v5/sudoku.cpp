//implementation file for sudoku and player class
#include "sudoku.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

//sudoku class implimentation --------------------------
SudokuBoard::SudokuBoard() {
    solved.assign(9, vector<int>(9,0));
    puzzle.assign(9, vector<int>(9,0));
}

bool SudokuBoard::isInRow(int r, int n) const {
    for (int i = 0; i < 9; i++) {
        if (solved[r][i] == n) {
            return true;
        }
    }

  return false;
}

bool SudokuBoard::isInCol(int c, int n) const {
    for (int i = 0; i < 9; i++) {
        if (solved[i][c] == n) {
            return true;
        }
    }

  return false;
}

bool SudokuBoard::isInBox(int r, int c, int n) const {
    //declare variables
    int rBox = r - (r % 3);
    int cBox = c - (c % 3);

    //verify 3x3 box
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (solved[rBox + i][cBox + j] == n) {
                return true;
            }
        }
    }
    
  return false;
}

void SudokuBoard::genBoard() {
    //reset board
    solved.assign(9, vector<int>(9,0));

    //declare variables
    int digit;

    //fill vector, validate rows are unique numbers
     for (int i = 0; i < 9; i++){ 
        for (int j = 0; j < 9; j++) {
            //declare variables
            bool failed = false;
            int tries = 0;

            do {
                //generate random number
                digit = rand() % 9 + 1;
                tries++;

                //backtrack
                if (tries > 1000) {
                    for (int k = 0; k < 9; k++) {
                             solved[i][k] = 0;
                    }
                    j = -1;
                    tries = 0;
                    failed = true;
                    break;
                }

           } while (isInRow(i, digit) || isInCol(j, digit) || isInBox (i, j, digit));
                if (!failed) {
                  solved[i][j] = digit;
           }
         }
    }
}

void SudokuBoard::setDifficulty() {
    //declare variables
    int userIn;

    //let user choose difficulty
    do {
        //display menu
        cout << "Choose difficulty:" << endl;
        cout << " 1. Easy  2. Medium  3. Hard" << endl;
        cin >> userIn;

        switch (userIn) {
            case 1 : zeroAmt = 15;
                     break;
            case 2 : zeroAmt = 30;
                     break;
            case 3 : zeroAmt = 45;
                     break;
            default : cout << endl;
                      cout << "Invalid input." << endl;
        }
    } while (userIn < 1 || userIn > 3);
}

void SudokuBoard::fillZero() {
    //declare variables
    int count = 0;

    while (count < zeroAmt) {
        //geneate random row and column to pick from
        int r = rand() % 9;
        int c = rand() % 9;

        //fill chosen element to be zero
        if (puzzle[r][c] != 0) {
            puzzle[r][c] = 0;
            count++;
        }
    }
}

void SudokuBoard::setBoard() {
    //reset board
    solved.assign(9, vector<int>(9,0));
    puzzle.assign(9, vector<int>(9,0));
    ogPuzle.assign(9, vector<int>(9,0));

    //create and print board
    genBoard();
    puzzle = solved;
    setDifficulty();
    fillZero();
    ogPuzle = puzzle;
}

void SudokuBoard::printBoard() const {
    //top of board
    cout << endl;
    cout << "Mistakes: " << strikes << "/3" << endl;
    cout << "  1  2  3   4  5  6   7  8  9" << endl;
    cout << "-------------------------------" << endl;
    
    for (int i = 0; i < 9; i++) {
        
            //horizontal divider
            if (i % 3 == 0 && i > 0) {
                cout << "|---------|---------|---------|" << endl;
            }

        for (int j = 0; j < 9; j++) {

            //vertical divider
            if (j % 3 == 0) {
                cout << "|";
            }

            //display sign if there is an empty space
            if (puzzle[i][j] == 0) {
                cout << " - ";
            } else {
                cout << " " << puzzle[i][j] << " ";
            }

        }
        //separate rows and skip lines
        cout << "|" << endl;
    }
  
  //bottom of board
  cout << "-------------------------------" << endl;
}

bool SudokuBoard::correct(int r, int c, int n) const {
    if (solved[r][c] == n) {
        return true;
    } else {
        return false;
    }
}

void SudokuBoard::solve(int &r, int &c, int &n) {
    //collect values from user
    //collect rows
    do {
        cout << "Enter row (horizontal):" << endl;
        cin >> r;
    } while (r > 9 || r <= 0);

    //collect columns
    do {
        cout << "Enter column (vertical):" << endl;
        cin >> c;
    } while (c > 9 || c <= 0);

    //verify numbers
    if (puzzle[r - 1][c - 1] != 0) {
        cout << endl;
        cout << "There is already a number there!" << endl;
        cout << endl;
    } else {
        cout << "Enter a number:" << endl;
        cin >> n;
        
        if (correct(r - 1, c - 1, n) == true) {
            cout << endl;
            cout << "You got it!" << endl;
            cout << endl;
            puzzle[r - 1][c - 1] = n;
        } else {
            cout << endl;
            cout << "Incorrect!" << endl;
            cout << endl;
            strikes++;
        }
    }
}


//player class implimentation --------------------------

Player::Player() {
    name = "";
    wins = 0;
    losses = 0;
}

void Player::getFile() {
    //declare variables
    char charIn;

    //determine if user is returning or new
    do {
    cout << "Is this your first time playing?" << endl;
    cout << "y = yes\nn = no" << endl;
    cin >> charIn;

    //validate input
    if (charIn != 'y' && charIn != 'Y' && charIn != 'n' && charIn != 'N') {
        cout << "Invalid input." << endl;
        cout << endl;
     }
    } while (charIn != 'y' && charIn != 'Y' && charIn != 'n' && charIn != 'N');

    //if user is new
    if (charIn == 'y' || charIn == 'Y') {
        //collect name from user
        cout << "Please enter your name: " << endl;
        cin >> name;
        save();
    }

    //if user is returning, load data
    if (charIn == 'n' || charIn == 'N') {
       try {
        load();
       } catch (bool isError) {
        //collect name from user
        cout << "Please enter your name: " << endl;
        cin >> name;
        save();
       }
    }

}

bool Player::save() {
    //declare variables
    fstream file;
    int nSize = name.size();

    //open file
    file.open ("save.txt", ios::out | ios::binary);

    //validate file
    if (!file) {
        cout << "File not found" << endl;
        return false;
    }
     else {
      //write values to .txt file
      //player name
      file.write(reinterpret_cast<char *>(&nSize),sizeof(nSize));
      if (nSize > 0) {
        file.write(reinterpret_cast<char *>(&name[0]),nSize);
      }
      
      //puzzle
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          file.write(reinterpret_cast<char *>(&game.getPuzzle()[i][j]),sizeof(int));
        }
      }
      
      //solved
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          file.write(reinterpret_cast<char *>(&game.getSolved()[i][j]),sizeof(int));
        }
      }

      //og puzzle
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          file.write(reinterpret_cast<char *>(&game.getOgPuzle()[i][j]),sizeof(int));
        }
      }

      //wins
      file.write(reinterpret_cast<char *>(&wins), sizeof(int));

      //losses
      file.write(reinterpret_cast<char *>(&losses), sizeof(int));
      
      //confirm save
      cout << endl;
      cout << "Saved to 'save.txt'" << endl;

      //close file
      file.close();
      return true;
     }
}

bool Player::load() {
    //declare variables
    fstream file;
    int nSize = 0;

    //open file
    file.open ("save.txt", ios::in | ios::binary);
        
    //validate file
    if (!file) {
     cout << "File not found" << endl;
     throw false;
    } 
     else {
      //read values to .txt file
      //player name
      file.read(reinterpret_cast<char *>(&nSize),sizeof(nSize));
      name.resize(nSize);
      if(nSize > 0) {
        file.read(reinterpret_cast<char *>(&name[0]),nSize);
      }
      
      //puzzle
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          file.read(reinterpret_cast<char *>(&game.getPuzzle()[i][j]),sizeof(int));
        }
      }
      
      //solved
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          file.read(reinterpret_cast<char *>(&game.getSolved()[i][j]),sizeof(int));
        }
      }

      //og puzzle
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          file.read(reinterpret_cast<char *>(&game.getOgPuzle()[i][j]),sizeof(int));
        }
      }

      //wins
      file.read(reinterpret_cast<char *>(&wins), sizeof(int));

      //losses
      file.read(reinterpret_cast<char *>(&losses), sizeof(int));
      
      //confirm load
      cout << endl;
      cout << "Welcome back, " << name << "." << endl;

      //close file
      file.close();
      return true;
     }
}

void Player::menu(int &r, int &c, int &n) {
    //declare variables
    int userIn;

    do {
    //display menu
    cout << endl;
    cout << "Player: " << name <<  " Wins: " << wins << " Losses: " << losses << endl;
    cout << "=================" << endl;
    cout << "Choose an option: " << endl;
    cout << "1. Play New Game" << endl;
    cout << "2. Continue Game" << endl;
    cout << "3. Save" << endl;
    cout << "4. Load" << endl;
    cout << "5. How To Play" << endl;
    cout << "6. Exit" << endl;
    cin >> userIn;

    //menu options based on input
    switch (userIn) {
        //new game
        case 1 : //generate new board
                 game.strikes = 0;
                 game.setBoard();
                 game.printBoard();

                 try {
                    play (r, c, n);
                 } catch (bool isError) {
                    cout << "Game Over!" << endl;
                    losses++;
                    game.getPuzzle() = game.getOgPuzle();
                    save();
                 }
                 break;

        //continuting game
        case 2 : //generate new board if there is only a blank board saved
                 if (game.getPuzzle() == game.getSolved()) {
                    cout << "You already won! Generating new board..." << endl;
                    game.setBoard();
                 } else {
                    game.strikes = 0;
                 }

                 //play game as normal
                 game.printBoard();
                 try {
                    play (r, c, n);
                 } catch (bool isError) {
                    cout << "Game Over!" << endl;
                    losses++;
                    game.getPuzzle() = game.getOgPuzle();
                    save();
                 }
                 break;

        case 3 : //save game
                 try {
                 save();
                 } catch (bool isError) {
                    cout << "Returning to menu.." << endl;
                 }
                 break;

        case 4 : //load game
                 try {
                    load();
                 } catch (bool isError) {
                    cout << "Returning to menu.." << endl;
                  }
                 break;

        case 5 : //tutorial
                 cout << endl;
                 cout << "HOW TO PLAY:" << endl;
                 cout << "============" << endl;
                 cout << "Sudoku is a classic puzzle game beloved by many!" << endl;
                 cout << "In a 9x9 grid, solve the puzzle.  " << endl;
                 cout << "Make sure that you make sure that " << endl;
                 cout << "the number you put can fit with the " << endl;
                 cout << "vertical row going 1-9, the horizontal " << endl;
                 cout << "row going 1-9, and the box contained in that" << endl;
                 cout << "spot. Enter either 1 or 2 when prompted to" << endl;
                 cout << "either play the game or go back to the menu." << endl;
                 cout << "by pressing 1, input your desired row, column," << endl;
                 cout << "and number in that order. Keep going until you" << endl;
                 cout << "fill the whole board! Make 3 mistakes and you"  << endl;
                 cout << "need to start from the beginning!" << endl;
                 cout << "Enjoy SUDOKU!!" << endl;
                 cout << endl;
                 break;

        case 6 : //quit game 
                 return;
                 break;
        
        default :  cout << endl;
                   cout << "Invalid input." << endl;
       }
    }while (userIn != 6);
}

bool Player::play(int &r, int &c, int &n) {
    //declare variables
    int userIn;

    do {
    //display menu
    cout << "Enter an option: " << endl;
    cout << "1. Play \n2. Quit" << endl;
    cin >> userIn;

    switch (userIn) {
        case 1 : game.solve(r, c, n);
                 game.printBoard();
                 break;
        case 2 : return false;
       default : cout << endl;
                 cout << "Invalid input." << endl;
                 cout << endl;
     }

    if (game.strikes >= 3) {
    throw false;
   }

   } while (game.getPuzzle() != game.getSolved());

   //save win to file
   cout << "You win!!" << endl;
   wins++;
   save();
   return true;
}

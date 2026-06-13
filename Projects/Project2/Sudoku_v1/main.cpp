/*
Author: Lucy Blanks
Date: 6/12/2026
Purpose: Sudoku 9x9

//v.6 ~ Expand to full board
        change all instances of 6 to 9                                 - DONE!             
        change all instances of "mini-sudoku" to "sudoku"              - DONE!
        extend the board to match 9x9                                  - DONE!
        bug board will not generate new board, only change 0 position  - FIXED!
        
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

//structures
struct board {
    vector<vector<int>> solved;
    vector<vector<int>> puzzle;
};

struct player {
    char name[50];
    struct board game;
};

//function prototypes
void getFile(player*);
bool save(player*);
bool load(player*);
void menu(player &, int &, int &, int &);
bool isInRow(vector<vector<int>>&, int, int);
bool isInCol(vector<vector<int>>&, int, int);
bool isInBox(vector<vector<int>>&, int, int, int);
bool correct(board &, int, int, int);
void genBrd(vector<vector<int>>&);
void filZero(vector<vector<int>> &vec);
void prtBrd(vector<vector<int>>&);
void solve(board &, int &, int &, int &);
void play(player &, int &, int &, int &);

//execution begins here at main
int main(int argc, char **argv ) {
    //set random number seed
    srand(time(0));

    //declare variables
    int rowIn;
    int colIn;
    int numIn;

    //initialize variables
    player *p = new player;
    p->game.solved.assign(9, vector<int>(9,0));
    p->game.puzzle.assign(9, vector<int>(9,0));

    //introduce program
    cout << endl;
    cout << "SUDOKU" << endl;

    //load or create new file
    getFile(p);
    menu(*p, rowIn, colIn, numIn);

    //clean up memory, close files
    delete p;
    p = nullptr;

    //exit the program
    return 0;
}

//functions
void getFile (struct player *p) {
    //declare variables
    char charIn;
    char nameIn[50];

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
        cin >> nameIn;
        strcpy(p->name, nameIn);

        //generate new board
        genBrd(p->game.solved);
        p->game.puzzle = p->game.solved;
        filZero(p->game.puzzle);
        save(p);
    }

    //if user is returning, load data
    if (charIn == 'n' || charIn == 'N') {
        load(p);
    }

}

bool save (struct player *p) {
    //declare variables
    fstream file;

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
      file.write(reinterpret_cast<char *>(&p->name),sizeof(p->name));
      
      //puzzle
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          file.write(reinterpret_cast<char *>(&p->game.puzzle[i][j]),sizeof(int));
        }
      }
      
      //solved
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          file.write(reinterpret_cast<char *>(&p->game.solved[i][j]),sizeof(int));
        }
      }
      
      //confirm save
      cout << endl;
      cout << "Saved to 'save.txt'" << endl;

      //close file
      file.close();
      return true;
     }
}

bool load (struct player *p) {
    //declare variables
    fstream file;

    //open file
    file.open ("save.txt", ios::in | ios::binary);
        
    //validate file
    if (!file) {
     cout << "File not found" << endl;
     return false;
    } 
     else {
      //read values to .txt file
      //player name
      file.read(reinterpret_cast<char *>(&p->name),sizeof(p->name));
      
      //puzzle
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          file.read(reinterpret_cast<char *>(&p->game.puzzle[i][j]),sizeof(int));
        }
      }
      
      //solved
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          file.read(reinterpret_cast<char *>(&p->game.solved[i][j]),sizeof(int));
        }
      }
      
      //confirm load
      cout << endl;
      cout << "Welcome back, " << p->name << "." << endl;

      //close file
      file.close();
      return true;
     }
}

void menu(struct player &p, int &r, int &c, int &num){
    //declare variables
    int userIn;

    do {
    //display menu
    cout << endl;
    cout << "Player: " << p.name << endl;
    cout << "Choose an option: " << endl;
    cout << "1. Play New Game" << endl;
    cout << "2. Continue Game" << endl;
    cout << "3. Save" << endl;
    cout << "4. Load" << endl;
    cout << "5. Exit" << endl;
    cin >> userIn;

    //menu options based on input
    switch (userIn) {
        //new game
        case 1 : //generate new board
                 genBrd(p.game.solved);

                 //match boards
                 p.game.puzzle = p.game.solved;

                 //create and print puzzle based on complete board
                 filZero(p.game.puzzle);
                 prtBrd(p.game.puzzle);
                 play (p, r, c, num);
                 break;

        //continuting game
        case 2 : //generate new board if there is only a blank board saved
                 if (p.game.puzzle == p.game.solved) {
                    cout << "You already won! Generating new board..." << endl;
                    genBrd (p.game.solved);
                    p.game.puzzle = p.game.solved;
                    filZero (p.game.puzzle);
                 }

                 //play game as normal
                 prtBrd (p.game.puzzle);
                 play (p,r,c,num);
                 break;

        case 3 : //save game
                 save(&p);
                 break;

        case 4 : //load game
                 load(&p);
                 break;

        case 5 : //quit game 
                 return;
                 break;
        
        default :  cout << endl;
                   cout << "Invalid input." << endl;
       }
    }while (userIn != 5);
}


bool isInRow(vector<vector<int>> &vec, int row, int n) {
    for (int i = 0; i < 9; i++) {
        if (vec[row][i] == n) {
            return true;
        }
    }

  return false;
}

bool isInCol(vector<vector<int>> &vec, int col, int n) {
    for (int i = 0; i < 9; i++) {
        if (vec[i][col] == n) {
            return true;
        }
    }

  return false;
}

bool isInBox(vector<vector<int>> &vec, int row, int col, int n) {
    //declare variables
    int rBox = row - (row % 3);
    int cBox = col - (col % 3);

    //verify 3x3 box
    for (int i = 0; i < 3; i++) {
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
    //reset board
    b.assign(9, vector<int>(9,0));

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
        int r = rand() % 9;
        int c = rand() % 9;

        //fill chosen element to be zero
        if (vec[r][c] != 0) {
            vec[r][c] = 0;
            count++;
        }

    }

}

void prtBrd(vector<vector<int>> &b){
    //top of board
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
  cout << "-------------------------------" << endl;
}

void solve (board &b, int &r, int &c, int &n) {
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
    if (b.puzzle[r - 1][c - 1] != 0) {
        cout << endl;
        cout << "There is already a number there!" << endl;
        cout << endl;
    } else {
        cout << "Enter a number:" << endl;
        cin >> n;
        
        if (correct(b, r - 1, c - 1, n) == true) {
            cout << endl;
            cout << "You got it!" << endl;
            cout << endl;
            b.puzzle[r - 1][c - 1] = n;
        } else {
            cout << endl;
            cout << "Incorrect!" << endl;
            cout << endl;
        }
    }

}

void play (player &p, int &r, int &c, int &n) {
    //declare variables
    int userIn;
    board *boardPtr = &p.game;

    do {
    //display menu
    cout << "Enter an option: " << endl;
    cout << "1. Play \n2. Quit" << endl;
    cin >> userIn;

    switch (userIn) {
        case 1 : solve(*boardPtr, r, c, n);
                 prtBrd(boardPtr->puzzle);
                 break;
        case 2 : return;
       default : cout << endl;
                 cout << "Invalid input." << endl;
     }
   } while (boardPtr->puzzle != boardPtr->solved);

   //save win to file
   cout << "You win!!" << endl;
   save(&p);
}

/*
Author: Lucy Blanks
Date:5/16/2026
Purpose: Mini-Sudoku: 6x6

//v.5 ~ Player Files
        create file structure                                          - DONE!
        create bool functions to create, save and load files           - DONE!
        create menu                                                    - DONE!
        fix bug where player can continue game if vectors are all 0    - DONE!
        create function for playing the actual game                    - DONE!
        create menu so player can go back to menu from board           - DONE!
        add ctime                                                      - DONE!
        generate new board for user upon creating new file             - DONE!
        verify user already won and generate new board                 - DONE!    
        adjust UI                                                      - DONE!
        game is now fully functional!
        
*/

//system libraries
#include <iostream> //input/output library
#include <iomanip> //formatting library
#include <cstdlib> //random library
#include <vector> //vector library
#include <fstream> //file library
#include <ctime> //time library
using namespace std; //using namepace standard

//structures
struct board {
    vector<vector<int>> solved;
    vector<vector<int>> puzzle;
};

struct player {
    string name;
    struct board game;
};

//function prototypes
void getFile(player &);
bool save(player &);
bool load(player &);
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
int main( int argc, char **argv ) {
    //set random number seed
    srand(time(0));

    //declare variables
    int rowIn;
    int colIn;
    int numIn;

    //initialize variables
    player p;
    p.game.solved.assign(6, vector<int>(6,0));
    p.game.puzzle.assign(6, vector<int>(6,0));

    //introduce program
    cout << endl;
    cout << "MINI SUDOKU" << endl;

    //load or create new file
    getFile(p);
    menu(p, rowIn, colIn, numIn);

    //clean up memory, close files

    //exit the program
    return 0;
}

//functions
void getFile (struct player &p) {
    //declare variables
    char charIn;
    string nameIn;

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
        cout << "Please enter your name: " << endl;
        cin >> nameIn;
        p.name = nameIn;
        genBrd(p.game.solved);
        p.game.puzzle = p.game.solved;
        filZero(p.game.puzzle);
        save(p);
    }

    //if user is returning
    if (charIn == 'n' || charIn == 'N') {
        load(p);
        cin.ignore();
    }

}

bool save (struct player &p) {
    //declare variables
    fstream file;

    //open file
    file.open ("save.txt", ios::out);

    //validate file
    if (!file) {
        cout << "File not found" << endl;
        return false;
    }
     else {
      //save values to .txt file
      //player name
      file << p.name << endl;

      //puzzle
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            file << p.game.puzzle[i][j] << " ";
        }
      }

      file << endl;

      //solved
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            file << p.game.solved[i][j] << " ";
        }
      }
      cout << endl;
      cout << "Saved to 'save.txt'" << endl;

      //close file
      file.close();
      return true;
     }
}

bool load (struct player &p) {
    //declare variables
    fstream file;

    //open file
    file.open ("save.txt", ios::in);
        
    //validate file
    if (!file) {
     cout << "File not found" << endl;
     return false;
    } 
     else {
      //load values from .txt file
      //player name
      file >> p.name;
      
      //puzzle
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            file >> p.game.puzzle[i][j];
        }
      }

      //solved
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            file >> p.game.solved[i][j];
        }
      }
      
      //confirm load
      cout << endl;
      cout << "Welcome back, " << p.name << "." << endl;

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
                 save(p);
                 break;

        case 4 : //load game
                 load(p);
                 break;

        case 5 : //quit game 
                 return;
                 break;
        
        default :  cout << endl;
                   cout << "Invalid input." << endl;
       }
    } while (userIn != 5);  
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
    cout << "  1  2  3   4  5  6" << endl;
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

void solve (board &b, int &r, int &c, int &n) {
    //collect values from user
    //collect rows
    do {
        cout << "Enter row (horizontal):" << endl;
        cin >> r;
    } while (r > 6 || r <= 0);

    //collect columns
    do {
        cout << "Enter column (vertical):" << endl;
        cin >> c;
    } while (c > 6 || c <= 0);

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

    do {
    //display menu
    cout << "Enter an option: " << endl;
    cout << "1. Play \n2. Quit" << endl;
    cin >> userIn;

    switch (userIn) {
        case 1 : solve(p.game, r, c, n);
                 prtBrd(p.game.puzzle);
                 break;
        case 2 : return;
       default : cout << endl;
                 cout << "Invalid input." << endl;
     }
   } while (p.game.puzzle != p.game.solved);

   //save win to file
   cout << "You win!!" << endl;
   save(p);
}

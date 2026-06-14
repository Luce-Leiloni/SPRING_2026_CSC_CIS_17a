#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <string>
using namespace std;

class Sudoku {
    protected: 
        vector<vector<int>> solved;                 //initial board
        vector<vector<int>> puzzle;                 //board that player solves that must match with solved
        vector<vector<int>> ogPuzle;                  //original puzzle in case the player starts from the beginning
        int zeroAmt;                                //amount of zeroes to remove based on difficulty

    public:
        int strikes;                                //amount of mistakes player has made
};

class SudokuBoard : public Sudoku {
    private:
        bool isInRow(int r, int n) const;
        bool isInCol(int c, int n) const;
        bool isInBox(int r, int c, int n) const;     
        void genBoard();                            //generate board
        void fillZero();                            //fill board with zeroes
        void setDifficulty();


    public:
        SudokuBoard();                               //constructor
        void setBoard();
        void printBoard() const;   
        bool correct(int r, int c, int n) const;
        void solve(int &r, int &c, int &n);
        
        vector<vector<int>>& getSolved() {return solved;}
        vector<vector<int>>& getPuzzle() {return puzzle;}
        vector<vector<int>>& getOgPuzle() {return ogPuzle;}

        
};

class Player {
    private:
        string name;
        SudokuBoard game;
        
        int wins;
        int losses;

    public:
        Player();
        void getFile();
        bool save();
        bool load();
        void menu(int &r, int &c, int &n);
        bool play(int &r, int &c, int &n);

};
#endif

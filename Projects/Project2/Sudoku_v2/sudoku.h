#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <string>
using namespace std;

class SudokuGame {
    private: 
        vector<vector<int>> solved;                 //initial board
        vector<vector<int>> puzzle;                 //board that player solves that must match with solved
    
        bool isInRow(int r, int n) const;
        bool isInCol(int c, int n) const;
        bool isInBox(int r, int c, int n) const;     

        void genBoard();                        //generate board
        void fillZero();                        //fill board with zeroes 


    public:
        SudokuGame();                         //constructor
        void setBoard();
        void printBoard() const;   
        bool correct(int r, int c, int n) const;
        void solve(int &r, int &c, int &n);
        
        vector<vector<int>>& getSolved() {return solved;}
        vector<vector<int>>& getPuzzle() {return puzzle;}

        
};

class Player {
    private:
        string name;
        SudokuGame game;

    public:
        Player();
        void getFile();
        bool save();
        bool load();
        void menu(int &r, int &c, int &n);
        void play(int &r, int &c, int &n);

};
#endif

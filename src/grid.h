#ifndef GRID_H
#define GRID_H

#include <string>
#include <vector>

#include "dictionary.h"

// these allow the board to be constructed using variables.
extern std::vector<std::vector<char> > board;
extern int ROWS, COLUMNS;
extern char FILL_CHARACTER;


class Grid {

public:

	void setUpGrid();
	// Displays the current grid
	void displayGrid();
	// Returns true if board is full
	bool isFull();
	// Returns true if column is full
	bool isFull(int c);
	// Adds letter to the grid, removes it from the player's available letters vector
	int addToGrid(int c, char ltr);
	void findAllStrings(int r, int c);
	bool validateWord(std::string word);
	bool checkWholeBoard(std::string word);
	int decideBestMove(int& r, int& c, std::vector<char>& listOfLtrs);
	void undoLastMove(int c, char l);
    int scoreWord(std::string wd);
    int getRow(int c);
    char scoreAllMoves(std::vector<char> letters);
    Dictionary& getDictionary();
    std::string reverseString(std::string str);
    //For comparing one move v. another, returns true if an adjacent letter exists
    int hasNeighbors(int r, int c);

private:


    // strings for all combos in grid
    std::string forwardStr, backwardStr, downStr, upStr, seStr, swStr, nwStr, neStr;
    std::vector<std::string> allStrings;
    struct Move {
        bool isVowel;
        char ltr;
        int row;
        int col;
        int points;
        std::vector<std::string> wordMatches;
    } moves;
    std::vector<Move> allMoves;
    Dictionary gridWords;

};


#endif

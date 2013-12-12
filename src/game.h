#ifndef GAME_H
#define GAME_H

#include "grid.h"
#include "player.h"
#include "dictionary.h"


#include <string>
#include <iostream>

class Game {

public:

    void setUpGame();
    void playRound();
    void displayScore();
    // Gets longest string of letters from all directions
    void gatherAllStrings();
    Grid& getGrid();
    Player& getHumanPlayer();
	Player& getComputerPlayer();

private:

    // Objects for the game
	Grid gameGrid;
	Player humanPlayer;
	Player computerPlayer;

};

#endif






#include <iostream>
#include <string>

#include "game.h"

using namespace std;

int inc = 0;

void Game::setUpGame()
{

    gameGrid.setUpGrid();
    computerPlayer.setUpPlayer('c');
    humanPlayer.setUpPlayer('h');
}

Grid& Game::getGrid()
{
    return gameGrid;
}
/*
Dictionary& Game::getWords()
{
    return gameWords;
}
*/
Player& Game::getHumanPlayer()
{
    return humanPlayer;
}

Player& Game::getComputerPlayer()
{
    return computerPlayer;
}


void Game::playRound()
{
  cin.clear();
  string playedWord = "";
  int points = 0;
  gameGrid.displayGrid();
  char ltr = humanPlayer.promptForLetter();
  int col = humanPlayer.promptForColumn(ltr);
  while (gameGrid.isFull(col))
  {
      cout << "That column is full" << endl;
      col = humanPlayer.promptForColumn(ltr);
  }
  int row = gameGrid.addToGrid(col, ltr);
  gameGrid.findAllStrings(row, col);
  gameGrid.displayGrid();
  while (humanPlayer.promptForWord(playedWord))
  {
    //check that word is valid in the grid
    if (gameGrid.validateWord(playedWord))
    {
        if (gameGrid.getDictionary().isInDictionary(playedWord))
        {
            points += gameGrid.scoreWord(playedWord);
        }
    }
  }
  humanPlayer.updatePlayerPoints(points);
  gameGrid.displayGrid();
  computerPlayer.displayLettersRemaining();
  computerPlayer.updatePlayerPoints(gameGrid.decideBestMove(row, col, computerPlayer.getLettersRemaining()));
  cout << "Score so far: You=";
  humanPlayer.showPoints();
  cout << " Me=";
  computerPlayer.showPoints();
  cout << endl;

}

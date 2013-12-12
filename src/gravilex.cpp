#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

#include "game.h"
#include "vectorUtils.h"

using namespace std;

int main (int argc, char **argv)
{
  // Checks to be sure the program is run with a dictionary file
  if (argc < 2)
  {
    printf("Please supply a dictionary filename (e.g. %s words.txt)", argv[0]);
    cout << endl;
    exit(0);
  }

  // Sets up a game object to control the game
  Game game;
  game.setUpGame();
  // Read in words file and write them to the dictionary
  string word;
  ifstream wdsfile (argv[1], ios::in);
  while (wdsfile >> word)
  {
    game.getGrid().getDictionary().addToDictionary(word);
  }
  wdsfile.close();

  // Read in test data if file is supplied
  if ( argc == 3 )
  {
      vector<string> testFile;
      ifstream ifs(argv[2], ios::in);
      string temp;

     while( getline( ifs, temp ) ){
          testFile.push_back(temp);
      }
      // The first 6 lines of the test file is the grid
      for (int i=5; i >= 0; --i)
      {
          for (int j=0; j<7; ++j)
          {
            game.getGrid().addToGrid(j, testFile[i][j]);
          }
      }
      // The next 2 lines of the test file are the players' letters, human first
        vector<char> hLetters, cLetters;
        for (int i=0; i < testFile[6].size(); ++i)
        {
            if (isalpha(testFile[6][i]))
                addInOrder(hLetters,testFile[6][i]);
        }
        for (int i=0; i < testFile[7].size(); ++i)
        {
            if (isalpha(testFile[7][i]))
                addInOrder(cLetters,testFile[7][i]);
        }
        game.getHumanPlayer().updatePlayerLetters(hLetters);
        game.getComputerPlayer().updatePlayerLetters(cLetters);

      // The last line of the test file is the current score
       // search for space
       int sp = testFile[8].find(" ");
       string strScore = testFile[8].substr(0,sp);
       int intScore = atoi(strScore.c_str());
       game.getHumanPlayer().updatePlayerPoints(intScore);
       strScore = testFile[8].substr(sp+1, testFile[8].size());
       intScore = atoi(strScore.c_str());
       game.getComputerPlayer().updatePlayerPoints(intScore);

  }
  while (!game.getGrid().isFull())
  {
      game.playRound();
  }

  return 0;
}

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "player.h"
#include "vectorUtils.h"

using namespace std;

string convertToLowerCase(string str);
bool containsNonWhiteSpace(string str);
const std::string startingLetters = "aabcdeefghiijklmnoopqrstuuvwxyz";

// Sets up new player.  Takes 'c' for computer or 'h' for human.
void Player::setUpPlayer(char wp)
{
    whichPlayer = wp;
    for (int i=0; i < startingLetters.size(); ++i)
    {
        lettersRemaining.push_back (startingLetters[i]);
    }
    playerPoints = 0;

}

vector<char>& Player::getLettersRemaining()
{
    return lettersRemaining;
}

void Player::showPoints()
{
    cout << playerPoints;
}

void Player::displayLettersRemaining()
{
    cout << endl << "Letters remaining to";
    if (whichPlayer == 'c')
    {
        cout << " me:" << endl;
    }
    else
    {
        cout << " you:" << endl;
    }
    for (int i=0; i < lettersRemaining.size()-1; ++i)
    {
        if (lettersRemaining[i] == lettersRemaining[i-1])
        {
        cout << "(2) ";
        }
        else
        {
        cout << lettersRemaining[i] << " ";
        }
    }
    cout << lettersRemaining[lettersRemaining.size()-1] << endl;
}

char Player::promptForLetter()
{
    string input;
    char ltr;
    cin.clear();
    while (binarySearch(lettersRemaining, ltr) == -1)
    {
        displayLettersRemaining();
        cout << endl << "What letter would you like to drop? ";
        if (cin.eof()){ cout << endl << "End of Input Detected" << endl; exit(1);}
        cin >> input;

        ltr = input[0];
        if ( isupper ( ltr ) )
        {
            ltr = tolower ( ltr );
        }
    }
    // remove the letter from the vector, then return it
    int pos = binarySearch(lettersRemaining, ltr);
    lettersRemaining.erase (lettersRemaining.begin()+pos);

    return ltr;
}

int Player::promptForColumn(char ltr)
{
    string input;
    int c = 0;
    // ensure that the column is between 1 and 7
    while (c < 1 || c > 7)
    {
        cout << "What column would you like to drop that in? (1-7) ";
        if (cin.eof()){ cout << endl << "End of Input Detected" << endl; exit(1);}
        cin >> input;
        // just take the first character from input
        c = atoi(&input[0]);
    }
    return c-1;
}


bool Player::promptForWord(string& word)
{
    string input, str;
    cout << endl << "Enter a word that you would like to claim (empty line to end): ";
    getline (cin, input);
    if (cin.eof()){ cout << endl << "End of Input Detected" << endl; exit(1);}
    // If prior input operation was a >>, this starts fresh at the next line
    getline (cin, input);
    if (cin.eof()){ cout << endl << "End of Input Detected" << endl; exit(1);}
    // Thanks, Dr. Zeil

    if (input.size()>0)
    {

//        getline(cin,input);
        if (input.find(' '))
        {
            word = input.substr(0,input.find(' '));
        }
        else
        {
            word = input;

        }
            return true;
    }
    return false;
}

void Player::updatePlayerLetters(std::vector<char> ltrs)
{
    lettersRemaining = ltrs;
}
void Player::updatePlayerPoints(int p)
{
    cout << endl << "Points scored on this turn: " << p << endl;
    playerPoints += p;
}

string convertToLowerCase(string str)
{
    string temp;
    for (int i=0; i<str.size(); ++i)
    {
        temp[i] = tolower(str[i]);
    }
    return temp;
}

bool containsNonWhiteSpace(string str)
{
    for (int i=0; i<str.size(); ++i)
    {
        char c=str[i];
        if (!isspace(c))
        {cout << "returning true" << endl;
            return true;
        }
    }
    return false;
}

#include <iostream>
#include <vector>
#include <string>

#include "grid.h"
#include "vectorUtils.h"

using namespace std;

char FILL_CHARACTER = '.';
int ROWS = 6;
int COLUMNS = 7;
std::vector<std::vector<char> > board(ROWS, vector<char>(COLUMNS));
const std::string vowels ("aeiou");

void Grid::setUpGrid()
{

    for (int i = 0;i < board.size();  ++i)
    {
        for(int j = 0;j < board[i].size(); ++j)
        {
            board[i][j] = FILL_CHARACTER;
        }
    }
}

int Grid::decideBestMove(int& r, int& c, vector<char>& listOfLtrs)
{
    // pass each letter to score letter to get back points
    vector<char> localLetters = listOfLtrs;
    int pts = scoreAllMoves(localLetters);
    c = allMoves[0].col;
    r = addToGrid(allMoves[0].col,allMoves[0].ltr);

    cout << "I will drop the letter " << allMoves[0].ltr << " in column " << allMoves[0].col+1 << "." << endl;
    for (int i=0; i<allMoves[0].wordMatches.size(); ++i)
    {
            cout << "I claim the word: " << allMoves[0].wordMatches[i] << endl;
    }
    // erase the letter from the computer's letter list
    listOfLtrs.clear();
    int found = 0;
    for (int i =0; i<localLetters.size();++i)
    {
        if ((localLetters[i] == allMoves[0].ltr) && (found == 0))
        {
            found = 1;
        }
        else if (isalpha(allMoves[0].ltr))
        {
            addInOrder(listOfLtrs,localLetters[i]);
        }
    }
    allMoves.clear();
    localLetters.clear();
    return allMoves[0].points;
}

void Grid::undoLastMove(int c, char l)
{
    addToGrid(c, l);
}

void Grid::displayGrid()
{
    cout << endl;

    for (int i = 0;i < board.size();  ++i)
    {
        for(int j = 0;j < board[i].size(); ++j)
        {
            cout << board[i][j];
        }
        cout << endl;
    }
    for (int i = 0;i < board.size()+1;  ++i)
    {
        cout << i+1;
    }
    cout << endl;
}

// Takes column, returns row.  Starts both rows and columns with 1.
int Grid::addToGrid(int c, char ltr)
{
    if (board[0][c] != FILL_CHARACTER)
    {
        //cout << "That column is full" << endl;
        return -1;
    }
    for (int i=5; i >= 0; --i)
    {
        if (board[i][c] == FILL_CHARACTER)
        {
            board[i][c] = ltr;

            return i;
        }
    }
}

bool Grid::isFull()
{
    // Returns true if entire grid is full
    for (int i = 0; i < board[i].size(); ++i)
    {
        if (board[0][i] == FILL_CHARACTER)
        {
            return false;
        }
    }
    return true;
}

bool Grid::isFull(int c)
{
    // Returns true if column is full
    if (board[0][c] == FILL_CHARACTER)
    {
       return false;
    }
    return true;
}

bool Grid::validateWord(std::string word)
{
    int found;
    // Game passes word with value of zero if no data was entered.  Just reject it and move on.
    if (word == "0")
    {
        return false;
    }
    for (int i = 0; i < allStrings.size(); ++i)
    {
        if (allStrings[i].find(word) != string::npos)
        {
            //cout << "found " << word << " in " << allStrings[i] << endl;
            return true;
        }
    }
    if (checkWholeBoard(word))
    {
        cout << "Sorry, you cannot play that word." << endl;
        return false;
    }
    cout << "Sorry, I cannot find that word." << endl;
    return false;
}

void Grid::findAllStrings(int r, int c)
{
    allStrings.clear();
    int row = r;
    int col = c;
    string myString;
    char temp[7];
    //horizontal string
    int stringSize;
    //Horizontal First
   //give me all 3-character letters first
    int offset = -2;
    for (int i = 0; i<3; ++i)
    {
       if ((col+offset>=0) && (col+offset<=4))
       {
        for (int j=0; j<3; ++j)
        {
            temp[j] = board[row][col+offset+j];
        }
        myString.assign(temp,3);
        if (myString.find(".") == string::npos)
        {
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }
        }
        ++offset;
    }
    // 4-character strings across
    offset = -3;
    for (int i = 0; i<4; ++i)
    {
       if ((col+offset>=0) && (col+offset<=3))
       {
        for (int j=0; j<4; ++j)
        {
            temp[j] = board[row][col+offset+j];
        }
        myString.assign(temp,4);
        if (myString.find(".") == string::npos)
        {
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }
        }
        ++offset;
    }
    // 5-character strings across
    offset = -4;
    for (int i = 0; i<5; ++i)
    {
       if ((col+offset>=0) && (col+offset<=2))
       {
        for (int j=0; j<5; ++j)
        {
            temp[j] = board[row][col+offset+j];
        }
        myString.assign(temp,5);
        if (myString.find(".") == string::npos)
        {
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }
        }
        ++offset;
    }
    // 6-character strings across
    offset = -5;
    for (int i = 0; i<6; ++i)
    {
       if ((col+offset>=0) && (col+offset<=1))
       {
        for (int j=0; j<6; ++j)
        {
            temp[j] = board[row][col+offset+j];
        }
        myString.assign(temp,6);
        if (myString.find(".") == string::npos)
        {
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }
        }
        ++offset;
    }
    // 7-character strings across
    offset = -6;
    for (int i = 0; i<7; ++i)
    {
       if ((col+offset>=0) && (col+offset<=0))
       {
        for (int j=0; j<7; ++j)
        {
            temp[j] = board[row][col+offset+j];
        }
        myString.assign(temp,7);
        if (myString.find(".") == string::npos)
        {
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }
        }
        ++offset;
    }
    //Vertical
   //give me all 3-character letters first
    if (row<4)
    {
    for (int i = 0; i<3; ++i)
    {
         temp[i] = board[row+i][col];
    }
        myString.assign(temp,3);
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }

   //give me all 4-character letters first
    if (row<3)
    {
    for (int i = 0; i<4; ++i)
    {
         temp[i] = board[row+i][col];
    }
            myString.assign(temp,4);
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }
   //give me all 5-character letters
    if (row<2)
    {
    for (int i = 0; i<5; ++i)
    {
         temp[i] = board[row+i][col];
    }
        myString.assign(temp,5);
        allStrings.push_back(myString);
        allStrings.push_back(reverseString(myString));
    }
   //give me all 6-character letters
    if (row<1)
    {
    for (int i = 0; i<6; ++i)
    {
         temp[i] = board[row+i][col];
    }
        myString.assign(temp,6);
        allStrings.push_back(myString);
        allStrings.push_back(reverseString(myString));
    }
    //SE
    //give me all 3-character letters first
    offset = -2;
    for (int i = 0; i<3; ++i)
    {
       if ((row+offset>=0) && (col+offset>=0) && (col+offset<5) && (row+offset<4))
       {
        for (int j=0; j<3; ++j)
        {
            temp[j] = board[row+offset+j][col+offset+j];
        }
        myString.assign(temp,3);
        if (myString.find(".") == string::npos)
        {
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }
        }
        ++offset;
    }
    //give me all 4-character letters
    offset = -3;
    for (int i = 0; i<4; ++i)
    {
       if ((row+offset>=0) && (col+offset>=0) && (col+offset<4) && (row+offset<3))
              {
        for (int j=0; j<4; ++j)
        {
            temp[j] = board[row+offset+j][col+offset+j];
        }
        myString.assign(temp,4);
        if (myString.find(".") == string::npos)
        {
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }
        }
        ++offset;
    }
    //give me all 5-character letters first
    offset = -4;
    for (int i = 0; i<5; ++i)
    {
       if ((row+offset>=0) && (col+offset>=0) && (col+offset<3) && (row+offset<2))
       {
        for (int j=0; j<5; ++j)
        {
            temp[j] = board[row+offset+j][col+offset+j];
        }
        myString.assign(temp,5);
        if (myString.find(".") == string::npos)
        {
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }
        }
        ++offset;
    }
    //give me all 6-character letters
    offset = -5;
    for (int i = 0; i<6; ++i)
    {
       if ((row+offset>=0) && (col+offset>=0) && (col+offset<2) && (row+offset<1))
       {
        for (int j=0; j<6; ++j)
        {
            temp[j] = board[row+offset+j][col+offset+j];
        }
        myString.assign(temp,6);
        if (myString.find(".") == string::npos)
        {
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }
        }
        ++offset;
    }
    //there are no 7s
    //NE
    //give me all 3-character letters
    offset = -2;
    for (int i = 0; i<3; ++i)
    {
       if ((row-offset<=5) && (col+offset>=0) && (col+offset<5) && (row-offset>1))
       {
        for (int j=0; j<3; ++j)
        {
            temp[j] = board[row-offset-j][col+offset+j];
        }
        myString.assign(temp,3);
        if (myString.find(".") == string::npos)
        {
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }
        }
        ++offset;
    }
    //give me all 4-character letters
    offset = -3;
    for (int i = 0; i<4; ++i)
    {
       if ((row-offset<=5) && (col+offset>=0) && (col+offset<4) && (row-offset>2))
       {
        for (int j=0; j<4; ++j)
        {
            temp[j] = board[row-offset-j][col+offset+j];
        }
        myString.assign(temp,4);
        if (myString.find(".") == string::npos)
        {
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }
        }
        ++offset;
    }
    //give me all 5-character letters
    offset = -4;
    for (int i = 0; i<5; ++i)
    {
       if ((row-offset<=5) && (col+offset>=0) && (col+offset<3) && (row-offset>3))
       {
        for (int j=0; j<5; ++j)
        {
            temp[j] = board[row-offset-j][col+offset+j];
        }
        myString.assign(temp,5);
        if (myString.find(".") == string::npos)
        {
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }
        }
        ++offset;
    }
    //give me all 6-character letters
    offset = -5;
    for (int i = 0; i<6; ++i)
    {
       if ((row-offset<=5) && (col+offset>=0) && (col+offset<2) && (row-offset>4))
       {
        for (int j=0; j<6; ++j)
        {
            temp[j] = board[row-offset-j][col+offset+j];
        }
        myString.assign(temp,6);
        if (myString.find(".") == string::npos)
        {
            allStrings.push_back(myString);
            allStrings.push_back(reverseString(myString));
        }
        }
        ++offset;
    }
}

bool Grid::checkWholeBoard(string word)
{
    // Runs a check against entire grid to see if word claimed is there.
    string forward;
    //check each row first, forwards and backwards
    for (int i=0; i<6; ++i)
    {
        for (int j=0; j<7; ++j)
        {
            forward += board[i][j];
        }
        forward += ' ';

    }
    //cout << forward << endl;
    if (forward.find(word) != string::npos)
    {
        //cout << "found in board" << endl;
        return true;
    }
    // take the whole forward string and reverse it
    char temp[100];
    string backward;
    int j = 0;
    for (int i=forward.size()-1; i>=0; --i)
    {
        temp[j] = forward[i];
        ++j;
    }
    backward.assign(temp,forward.size());
    //cout << backward << endl;
    if (backward.find(word) != string::npos)
    {
        //cout << "found in board" << endl;
        return true;
    }
    // now check up and down
    string downward;
    for (int i=0; i<7; ++i)
    {
        for (int j=0; j<6; ++j)
        {
            downward += board[j][i];
        }
        downward += ' ';
    }

    //cout << downward << endl;
    if (downward.find(word) != string::npos)
    {
        //cout << "found in board" << endl;
        return true;
    }
    // reverse the downward string
    string upward;
    j = 0;
    for (int i=downward.size()-1; i>=0; --i)
    {
        temp[j] = downward[i];
        ++j;
    }
    upward.assign(temp,downward.size());
    //cout << upward << endl;
    if (upward.find(word) != string::npos)
    {
        //cout << "found in board" << endl;
        return true;
    }
    // now check diagnally, southeast
    string southeast;
    //spaces first
    int spaces[] = {1,4,8,13,19,26,33,39,44,48,51};
    for (int i=0; i<6; ++i)
    {
        temp[spaces[i]] = ' ';
    }
    int arraylength(int across[]);
    int across[] = {7,7,6,5,4,3};
    int next = 7;
    int down = 6;
    int origloc = 20;
    int origdec = 6;
    int loc = 20;
    for (int i=0; i<6; ++i)
    {
        for (int j=0; j<7; ++j)
        {
            //cout << loc << ' ';
            temp[loc] = board[i][j];
            loc += across[j];
        }
        origloc -= origdec;
        --origdec;
        loc = origloc;
        for (int i = 5; i>=0; --i)
        {
            across[i] = across[i-1];
        }
        across[0] = next;
        --next;

    }
    southeast.assign(temp,forward.size());
    //cout << southeast << endl;
    if (southeast.find(word) != string::npos)
    {
        return true;
    }
    // reverse the se string to make a nw string
    string northwest;
    j = 0;
    for (int i=southeast.size()-1; i>=0; --i)
    {
        temp[j] = southeast[i];
        ++j;
    }
    northwest.assign(temp,southeast.size());
    //cout << northwest << endl;
    if (northwest.find(word) != string::npos)
    {
        //cout << "found in board" << endl;
        return true;
    }
    // now check diagnally, southeast
    string southwest;
    //spaces first
    for (int i=0; i<6; ++i)
    {
        temp[spaces[i]] = ' ';
        across[i] = i+2;
    }
    next = 6;
    down = 3;
    origloc = 0;
    origdec = 3;
    loc = 0;
    for (int i=0; i<6; ++i)
    {
        for (int j=0; j<7; ++j)
        {
            //cout << loc << ' ';
            temp[loc] = board[i][j];
            loc += across[j];
        }
        origloc += origdec;
        ++origdec;
        loc = origloc;
        for (int i = 0; i<6; ++i)
        {
            across[i] = across[i+1];
        }
        across[5] = next;
        --next;

    }
    southwest.assign(temp,forward.size());
    //cout << southwest << endl;
    if (southwest.find(word) != string::npos)
    {
        return true;
    }
    // reverse the sw string to make a ne string
    string northeast;
    j = 0;
    for (int i=southwest.size()-1; i>=0; --i)
    {
        temp[j] = southwest[i];
        ++j;
    }
    northeast.assign(temp,southwest.size());
    //cout << northeast << endl;
    if (northeast.find(word) != string::npos)
    {
        //cout << "found in board" << endl;
        return true;
    }
    //
    return false;
}

char Grid::scoreAllMoves(vector<char> letters)
{
    // scores all possible moves for a vector of letters and writes them to a vector called all moves.  position 0 is the best.

    // For each letter in player's array, try each column in the board and determine score
    for (int i=0; i<letters.size(); ++i)
    {
        //cout << "Trying " << letters[i] << " from index " << i << endl;
        for (int j=0; j<7; ++j)
        {
            moves.wordMatches.clear();
            //cout << "Column "<< j << endl;
            if (!isFull(j))
            {
                //cout << "Row "<< moves.row << endl;
                moves.row = addToGrid(j, letters[i]);
                moves.col = j;
                moves.ltr = letters[i];
                moves.points = 0;
                if (vowels.find(moves.ltr) != string::npos)
                {
                    moves.isVowel = 1;
                } else {
                    moves.isVowel = 0;
                }
                //cout << moves.ltr << " " << moves.isVowel << endl;
                findAllStrings(moves.row,j);
                //cout << "All strings:" << endl;
                // Go through each of the strings to find out if they contain words
                for (int k=0; k<allStrings.size();++k)
                {
                     //cout << allStrings[k] << endl;
                     if (gridWords.lookUpWord(allStrings[k]))
                     {
                            moves.wordMatches.push_back(allStrings[k]);
                            moves.points +=scoreWord(allStrings[k]);
                     }
                }
            // after pushing all the words into the list, undo the move
            //undoLastMove(moves.col, moves.ltr);
            board[moves.row][moves.col] = '.';
            // put the best move in the front

            if (allMoves.size() == 0)
            {
                allMoves.push_back(moves);
            }
            else if (moves.points > allMoves[0].points)
            {
                // Select the play that earns the highest possible score on that turn.
                int toBeMoved = allMoves.size() - 1;
                allMoves.push_back(moves);
                while (toBeMoved >= 0)
                {
                    allMoves[toBeMoved+1] = allMoves[toBeMoved];
                    --toBeMoved;
                }
                allMoves[0] = moves;
            }
            else if ((moves.points == allMoves[0].points) && (moves.isVowel < allMoves[0].isVowel))
            {
                // If tied, give preference to plays that involve a consonant rather than a vowel.
                int toBeMoved = allMoves.size() - 1;
                allMoves.push_back(moves);
                while (toBeMoved >= 0)
                {
                    allMoves[toBeMoved+1] = allMoves[toBeMoved];
                    --toBeMoved;
                }
                allMoves[0] = moves;
            }
            else if (((moves.points == allMoves[0].points) && (moves.isVowel == allMoves[0].isVowel)) &&
                            (hasNeighbors(moves.row, moves.col) > hasNeighbors(allMoves[0].row, allMoves[0].col)))
            {
                // If still tied, give preference to plays where your dropped tile touch at least one existing tile, horizontally or vertically.
                int toBeMoved = allMoves.size() - 1;
                allMoves.push_back(moves);
                while (toBeMoved >= 0)
                {
                    allMoves[toBeMoved+1] = allMoves[toBeMoved];
                    --toBeMoved;
                }
                allMoves[0] = moves;
            }
            else if (((moves.points == allMoves[0].points) && (moves.isVowel == allMoves[0].isVowel) &&
                            (hasNeighbors(moves.row, moves.col) > hasNeighbors(allMoves[0].row, allMoves[0].col))) &&
                            (moves.ltr < allMoves[0].ltr))
            {
                // If there is still a tie, give preference to the play involving the earlier letter in alphabetic order.
                int toBeMoved = allMoves.size() - 1;
                allMoves.push_back(moves);
                while (toBeMoved >= 0)
                {
                    allMoves[toBeMoved+1] = allMoves[toBeMoved];
                    --toBeMoved;
                }
                allMoves[0] = moves;
            }
            else if (((moves.points == allMoves[0].points) && (moves.isVowel == allMoves[0].isVowel) &&
                            (hasNeighbors(moves.row, moves.col) > hasNeighbors(allMoves[0].row, allMoves[0].col)) &&
                            (moves.ltr < allMoves[0].ltr)) && (moves.col < allMoves[0].col))
            {
                // If there is still a tie, give preference to the play involving the earlier letter in alphabetic order.
                int toBeMoved = allMoves.size() - 1;
                allMoves.push_back(moves);
                while (toBeMoved >= 0)
                {
                    allMoves[toBeMoved+1] = allMoves[toBeMoved];
                    --toBeMoved;
                }
                allMoves[0] = moves;
            }
            else
            {
                //if all fails, throw it in back
                allMoves.push_back(moves);
            }
            }
        }
    }

//cout << "the best move is " << allMoves[0].col << " using " << allMoves[0].ltr << " for " << allMoves[0].points << " points." << endl;
}
int Grid::getRow(int c)
{
    for (int i=5; i>=0; --i)
    {
        if (board[i][c] == '.')
        {
            return i;
        }
    }
    return -1;
}
Dictionary& Grid::getDictionary()
{
    return gridWords;
}


int Grid::scoreWord(std::string wd)
{
    if (wd.size() == 3)
        return 1;
    else if (wd.size() == 4)
        return 2;
    else if (wd.size() == 5)
        return 4;
    else if (wd.size() == 6)
        return 8;
    else if (wd.size() == 7)
        return 16;
    else
        return 0;
}

int Grid::hasNeighbors(int r, int c)
{
    if (r < 5)
        return 1;
    else if ((c>0) && (board[r][c-1] != '.'))
        return 1;
    else if ((c<6) && (board[r][c+1] != '.'))
        return 1;
    return 0;
}


string Grid::reverseString(string str)
{
  char temp[str.size()];
  string tempString;
  int j = 0;
  for (int i=str.size()-1; i >=0; --i)
  {
    temp[j] = str[i];
    ++j;
  }
  tempString.assign(temp,str.size());
  return tempString;
}


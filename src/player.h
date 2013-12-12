#include <string>
#include <vector>

extern const std::string startingLetters;


class Player
{

public:

    void setUpPlayer(char wp);
    void displayLettersRemaining();
    char promptForLetter();
    int promptForColumn(char ltr);
    bool promptForWord(std::string& word);
    void updatePlayerLetters(std::vector<char> ltrs);
    void updatePlayerPoints(int p);
    void showPoints();
    std::vector<char>& getLettersRemaining();

private:

        std::vector<char> lettersRemaining;
        char whichPlayer; //stores a char to identify the different players internally.  Used in showPoints() function.
        int playerPoints;

};


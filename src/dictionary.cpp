#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "dictionary.h"
#include "vectorUtils.h"
#include "game.h"

using namespace std;

void Dictionary::addToDictionary(std::string wd)
{
    if (wd.size() > 2 && wd.size() < 7)
    {
        addInOrder(words, wd);
    }

}

void Dictionary::displayDictionary()
{
    for (int i=0; i < words.size(); ++i)
    {
        cout << words[i] << endl;
    }
}

bool Dictionary::isInDictionary(std::string word)
{
    char input;
    if (binarySearch(words, word) > 0)
    {
        return true;
    }
    cout << "I don't know that word. Are you sure you spelled it correctly? (y/n) " << endl;
    if (cin.eof()){ cout << endl << "End of Input Detected" << endl; exit(1);}
    cin >> input;
    if ((input == 'Y') || (input == 'y'))
    {
        return true;
    }
    return false;
}

bool Dictionary::lookUpWord(std::string word)
{
        if (binarySearch(words, word) > 0)
    {
        return true;
    }
    return false;
}





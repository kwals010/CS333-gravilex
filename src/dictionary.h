#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>

class Dictionary {

public:

    void addToDictionary(std::string wd);
    void displayDictionary();
	bool isInDictionary(std::string word);
	bool lookUpWord(std::string word);



private:

    std::vector<std::string> words;


};


#endif

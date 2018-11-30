// WordChecker.cpp
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"


WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    std::unordered_set<std::string> myset;
    
    for(int x = 0; x<word.length(); ++x)
    {
        std::string temp = word;
        for(char c = 'A'; c <= 'Z'; ++c)
        {
            temp[x] = c;
            if(wordExists(temp))
                myset.insert(temp);

            std::string temp1 = word.substr(0, x) + c + word.substr(x);
            if(wordExists(temp1))
                myset.insert(temp1);
        }

        std::string tempstr1 = word.substr(0, x);
        std::string tempstr2 = word.substr(x);
        if(wordExists(tempstr1) && wordExists(tempstr2))
        {
            std::string addspace = tempstr1 + " " + tempstr2;
            myset.insert(addspace);
        }    
    }    

    for(int x = 0; x<word.length()-1; ++x)
    {
        std::string temp2 = word.substr(0, x) + word[x+1] + word[x] + word.substr(x+2);
        transform(temp2.begin(), temp2.end(), temp2.begin(), toupper);
        if(wordExists(temp2))
            myset.insert(temp2);
        
        std::string temp3 = word.substr(0, x) + word.substr(x+1);
        transform(temp3.begin(), temp3.end(), temp3.begin(), toupper);
        if(wordExists(temp3))
            myset.insert(temp3); 
    }
    
    std::vector<std::string> result;
    for(const std::string& x: myset)
        result.push_back(x);
    
    return result;
}


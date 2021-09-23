#pragma once
#include <iostream>
class WordCounter
{
public:

    int numWords = 0;

    int wordCounter()
    {
        numWords++;
        return numWords;
    }
};


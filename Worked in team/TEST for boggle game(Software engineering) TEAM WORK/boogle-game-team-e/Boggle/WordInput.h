#pragma once
#include <string>
#include <iostream>

class WordInput
{
public:

    std::string wordInput()
    {
        std::string input;
     
        std::cin >> input;

        //input = "Mason"; //Uncomment for showcasing tests
        return input;
    }
};


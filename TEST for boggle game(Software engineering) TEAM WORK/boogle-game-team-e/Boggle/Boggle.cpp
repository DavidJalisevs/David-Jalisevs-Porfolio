#include "Boggle.h"
std::string Boggle::createWords()
{
    srand(time(nullptr));

    output += " | ";
    for (int i = 0; i < 4; i++)
    {
        output += letterArray[i];
        output += " | ";
    }
    output += "\n";
    output += " | ";
    for (int i = 4; i < 8; i++)
    {
        output += letterArray[i];
        output += " | ";
    }
    output += "\n";
    output += " | ";
    for (int i = 8; i < 12; i++)
    {
        output += letterArray[i];
        output += " | ";
    }
    output += "\n";
    output += " | ";
    for (int i = 12; i < 16; i++)
    {
        output += letterArray[i];
        output += " | ";
    }

    //output = "T"; //Uncomment if testing
    return output;

}


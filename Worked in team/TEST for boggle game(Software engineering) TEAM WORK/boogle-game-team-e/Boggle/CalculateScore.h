#pragma once
#include <iostream>
#include "HighScore.h"
class CalculateScore
{
   // HighScore playerScore;
public:
    int score = 0;
    int calculate(int letterNum)
    {
        score = score + letterNum;
        //playerScore.ScoreToFile(score);
        return score;
    }
};


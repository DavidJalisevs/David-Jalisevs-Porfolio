#include "ScoreCalculator.h"
#include <stack>

//this method should return a vector with the score for each frame of the game
//see ScoreCalculatorUnitTests.cpp for detail specification
 int addBall(vector<int> frames);
vector<int> ScoreCalculator::score(vector<int> frames)
{
	
	vector<int> scores;
	int totalScore = 0;
	int framesScore = 0;

	for (int i = 0; i < frames.size(); i += 2)
	{
		framesScore = frames[i];
		if (frames.size() > i + 1)
		
			framesScore += frames[i+1];
			totalScore += framesScore;
		
		
		scores.push_back(totalScore);
	}




	return  scores;

}


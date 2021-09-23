#include "HighScore.h"
#include <string>
#include <iostream>
#include <fstream>


//void HighScore::ScoreToFile(int t_score)
//{
//	std::string playerScore;
//	std::string aMessage = "";
//
//	std::to_string(t_score);
//
//	playerScore = t_score;
//
//	std::ofstream playerFile;
//
//	playerFile.open("playerInfo.txt");
//	if (playerFile.is_open())
//	{
//		
//		playerFile << playerScore;
//		while (playerFile.eof())
//		{
//			aMessage = "the players score is :" + playerScore;
//			playerFile << aMessage;
//		}
//		playerFile.close();
//	}
//	else
//	{
//		std::cout << "error occurred" << std::endl;
//	}
//	
//	
//
//	
//
//
//
//	
//}

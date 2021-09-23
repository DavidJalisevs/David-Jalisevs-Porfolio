// Boggle.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <string>
#include <ctime>
#include "Boggle.h"
#include "CalculateScore.h"
#include "DifficultyChange.h"
#include "Display.h"
#include "LetterCounter.h"
#include "WordCounter.h"
#include "WordInput.h"
#include "Timer.h"
#include "WordChecker.h"
#include "GamerTag.h"
#include "HighScore.h"
#include <Windows.h>


int main()
{
	GamerTag playerName;
	Boggle boggleGame;
	Display display;
	WordInput input;
	LetterCounter countLetters;
	CalculateScore calculator;
	DifficultyChange difficulty;
	WordCounter wordCount;
	//Timer gameTime;
	WordChecker checkWord;
	//HighScore playerScore;

	playerName.enterName();
	playerName.displayName(playerName.gamerTag);
	difficulty.askForDifficulty();


	boggleGame.createWords();
	bool gameOpen = true;
	int score = 0;
	std::string validWord = "";
	//gameTime.runTime(difficulty.time);

	
	for (boggleGame.index = 0; boggleGame.index < boggleGame.MAX; boggleGame.index++)
	{
		display.displayOutput(boggleGame.output);
		std::string out = input.wordInput();
		validWord = checkWord.wordCheck(out, boggleGame.letterArray);
		score = countLetters.letterCounter(validWord);
		boggleGame.numberOfWords = wordCount.wordCounter();
		system("CLS");
		std::cout << "                                                                 Score: " << calculator.calculate(score) << std::endl;

	}
	//bool gameOpen = true;
		//bool timerTest = true;
	//boggleGame.createWords();
		//int timeTest = 0;
		/*	while (timerTest == true)
		{

			Sleep(1000);
			system("cls");
			int displayTime = 180;
			timeTest += 1;
			displayTime = displayTime - timeTest;
			std::cout << displayTime;

		}*/

		//for (boggleGame.index = 0; boggleGame.index < boggleGame.MAX; boggleGame.index++)
		//while (score  < 30)
		//{
		//	display.displayOutput(boggleGame.output);
		//	std::string out = input.wordInput();
		//	int score = countLetters.letterCounter(out);
		//	boggleGame.numberOfWords = wordCount.wordCounter();
			//std::cout << "                                                                 time: "<<std::endl; << gameTime.timeLimit << std::endl;
		//	std::cout << "                                                                 Score: " << calculator.calculate(score) << std::endl;
		//}
		//gameOpen = false;
		//system("CLS");

	//if (gameOpen == false)
	//{
	//	system("cls");
			//
			//std::cout << "Your Score is: " << calculator.calculate(score) << std::endl;
	//}

	//if (score >= 30)
	//{
		std::cout << "Number of Words input: " << boggleGame.numberOfWords << std::endl;
		//playerScore.ScoreToFile(score);
	//}
	
}

// THINGS TO do
// authors: Sasa Kuzmanovic, Dawid Jerdonek, David Jalisevs, Donal Howe
// brief:
// 1:The Player, wants to see the letters offered to them, to be able to connect the letters.
// 2:The Player, wants to type in a word which they found in the game, so that the game can add to their score.
// 3:The Player, wants to see the timer displayed on the screen, so that they know how much time they have left.
// 4:The Player, wants to see his score at the end of the game , so that they wont have to do the math themself.
// 
// 


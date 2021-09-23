#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <time.h>

class Boggle
{
public:

	std::string output;
	int score = 0;
	const int MAX = 25;
	int index = 0;
	int numberOfWords = 0;

	char letterArray[16] = { char(rand() % 25 + 65) ,char(rand() % 25 + 65) , char(rand() % 25 + 65) , char(rand() % 25 + 65),
					char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,
					char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,
					char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,char(rand() % 25 + 65)
	};

	std::string createWords();
	//static std::string numbers(int num);

};

#include "DifficultyChange.h"


void DifficultyChange::askForDifficulty()
{
	std::cout << "Please select your difficulty:" << std::endl;
	std::cout << "(Type in the number representing difficulty)" << std::endl;
	std::cout << "1 - Easy(regular mode)" << std::endl;
	std::cout << "2 - Hard(decreased time)" << std::endl;
	std::cout << "3 - Expert" << std::endl;
	std::cin >> playerChoice;


	while (playerChoice >= 4|| playerChoice <=0)
	{
		std::cout << "(Type in the number representing difficulty)" << std::endl;
		std::cout << "1 - Easy(regular mode)" << std::endl;
		std::cout << "2 - Hard(decreased time)" << std::endl;
		std::cout << "3 - Expert" << std::endl;
		std::cin >> playerChoice;
	}

	// now need to pass variagle time to the timer class thru main
	if(playerChoice ==1)
	{
		// start regular game
		//set timer to regular time
		time = 90.0f;

	}
	else if (playerChoice == 2)
	{
		//start hard mode
		// set less time
		time = 60.0f;

	}
	else if(playerChoice == 3)
	{
		//start expert mode 
		time = 30.0f;
	}

}

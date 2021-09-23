#include <iostream>
#include <chrono>
#include <thread>
#include "Animation.h"
#include "State.h"
#include <stdlib.h>     /* srand, rand */



int main()
{
	Animation fsm; 
	int i = 0;
	int actionHolder = 0;
	int hazardAhed = 0;
	int first = 1;
	std::cout << "Please select one of the following actions to avoid hazard ahead" << std::endl;
	std::cout << "1- Idle" << std::endl;
	std::cout << "2- Jump" << std::endl;
	std::cout << "3- Climning " << std::endl;
	srand(time(NULL));

	while (true)
	{
		//1= Hole in the ground
		//2= climbing wall
		//3= hungry bear
		hazardAhed = rand() % 3 + 1;/// in the range 1 to 3
	
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		if (hazardAhed == 1)
		{
			std::cout << "Hole in the ground is ahead, you need to jump over it !" << std::endl;
			std::cin >> actionHolder;

			if (actionHolder == 2) // hole in the groundd
			{
				fsm.jumping();
				std::cout << "Jumped over succesfully" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				fsm.idle();

				actionHolder = 0;
			}
			else
			{
				std::cout << "you died" << std::endl;
				return 0;
			}
		}

		if (hazardAhed == 2)
		{
			std::cout << "Wall is ahead of you, climb over it !" << std::endl;
			std::cin >> actionHolder;

			if (actionHolder == 3) // wall
			{
				fsm.climbing();
				std::cout << "Climbed over the wall uccesfully" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				fsm.idle();
				actionHolder = 0;
			}
			else
			{
				std::cout << "you died" << std::endl;
				return 0;
			}
		}

		if (hazardAhed == 3) // bear
		{
			std::cout << "Hungry bear is ahead of you stay idle to survive" << std::endl;
			std::cin >> actionHolder;

			if (actionHolder == 1)
			{
				fsm.idle();
				std::cout << "You survived succesfully" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(300));
				actionHolder = 0;
			}
			else
			{
				std::cout << "you died" << std::endl;
				return 0;
			}
		}
	}
}

/// <summary>
/// Davids Jalisevs 
/// ID - C00239534
/// 13/10/2020
/// Approx time taken 
///  3 and a half hours on 13/10/2020
/// 
/// 
/// ---------------------------------------------------------------------------------------------------------------------------------
/// PLEASE READ THIS
/// There are some rules to this game or as I call it "features"
/// There is 3 types of warheads 
/// Nuclear - is the warhead that will hit the target depending on the original calculations as X+=1 and Y+=2
/// Radioactive - is the warhead that will maybe( kinda randomly ) hit the target as depends on calculation of Y as Y += number between 1 and 2; might hit might not
/// GODLIKE IS THE ABSOLUTE UNIT THAT WILL ALWAYS HIT THE TARGET DOESNT MATTER WHERE TARGET IS
/// 
/// 
/// Text based game 
/// </summary>
/// 

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include<time.h>  
#include "Globals.h"

/// <summary>
/// // this function asks player to select the warhead
/// </summary>
void selectWarHead(); 

/// <summary>
/// this fucntion asks if arm or disarm the warhead
/// </summary>
void armDisarm();

/// <summary>
/// this fucntion will ask for the input coords
/// </summary>
void inputCoord();

/// <summary>
/// this fucntion will ask to launch or not the missle
/// </summary>
void launchMissle();

/// <summary>
/// this function will output results of the missile
/// </summary>
void resultReport();



int main()
{
	std::string start;
	std::string name; // ask for the name to make an illusion like we care who it is. everyone knows that everyone can laucnh missles 


	/// <summary>
	/// Greeting the player
	/// </summary>
	/// <returns></returns>
	std::cout << "\t-Please enter your full name and the soldier ID for the Identity Verification " << std::endl;
	std::cin >> name;

	system("CLS");

	std::cout << "==================================================================================================== " << std::endl;
	std::cout << "\t-Welcome General, please follow the instruction below " << std::endl;
	std::cout << "\t-Please type 'Start' to begin " << std::endl;
	std::cout << "==================================================================================================== " << std::endl;

	std::cin >> start;

	/// <summary>
	/// Check for the input from player 
	/// </summary>
	/// <returns></returns>

	while (start != "start" && start != "Start" && start != "START")
	{
		std::cout << "-Please type 'Start' to begin " << std::endl;
		std::cin >> start;
		/*if (start == "start" || start == "Start" || start == "START")
		{
			break;
		}*/
	}


	if (start == "start" || start == "Start" || start == "START")
	{
		selectWarHead();
		//inputCoord();
		
	}
	
	system("pause");

	return 0;
}




void selectWarHead()
{
	system("CLS");

	int temp{ 0 };

	std::cout << "==================================================================================================== " << std::endl;
	std::cout << "\t-Please select one of the following options " << std::endl;
	std::cout << "\t: " << std::endl;
	std::cout << "\t1)Nuclear Warhead " << std::endl; // kinda random hit
	std::cout << "\t2)Radioactive Warhead " << std::endl;
	std::cout << "\t3)Godlike Warhead " << std::endl; // ALWAYS HIT SUCCESSFUL
	std::cout << "==================================================================================================== " << std::endl;

	std::cin >> temp;

	while (temp != 1 && temp != 2 && temp != 3)
	{
		std::cout << "-Please type the number appropriate to the Warhead " << std::endl;
		std::cin >> temp;
	}


	if(temp == 1 || temp == 2 || temp == 3) // check what warhead is selected
	{
		warHead = temp;
	}

	inputCoord(); //.move on to the next step

}


void inputCoord()
{
	system("CLS");
	std::cout << "==================================================================================================== " << std::endl;
	std::cout << "\t-Please enter the Coordinates of the target you want to attack " << std::endl;
	std::cout << "\tX coordinates - ";
	std::cin >> targetX;
	std::cout << "\tY coordinates - ";
	std::cin >> targetY;

	armDisarm();
}


void armDisarm()
{
	std::string condition{ "" };
	system("CLS");
	std::cout << "==================================================================================================== " << std::endl;
	std::cout << "\t-Coordinates are taken" << std::endl;

	if (warHead == 1)
	{
		std::cout << "\t-You chose NUCLEAR WARHEAD " << std::endl;
	}
	else if (warHead == 2)
	{
		std::cout << "\t-You chose RADIOACTIVE WARHEAD " << std::endl;
	}
	else 
	{
		std::cout << "\t-You chose GOLDIKE WARHEAD " << std::endl;
	}

	std::cout << "\t-Please confirm Arming of the warhead " << std::endl;
	std::cout << "\t-Please please type in 'Arm' to launch the missle or 'Disarm' to abandon the process" << std::endl;
	std::cin >> condition;
	
	while (condition != "arm" && condition != "Arm" && condition != "ARM" && condition != "Disarm" && condition != "DISARM" && condition != "disarm" )
	{
		std::cout << "\t-Please confirm Arming of the warhead " << std::endl;
		std::cout << "\t-Please please type in 'Arm' to arm the missle or 'Disarm' to abandon the process" << std::endl;
		std::cin >> condition;
	}


	if (condition == "arm" || condition == "Arm" || condition == "ARM")
	{
		launchMissle();
	}
	else if (condition == "Disarm" || condition == "DISARM" || condition == "disarm")
	{
		return;
	}
}




void launchMissle()
{
	srand(time(NULL)); // just in case for now

	int check{ 10 };
	long int i{ 99999 }; // local timer
	system("CLS");
	std::cout << "==================================================================================================== " << std::endl;
	std::cout << "\t-Missle has been armed and is ready to launch!" << std::endl;
	std::cout << "\t-Press 1 to launch the missle" << std::endl;
	std::cout << "\t-Press 0 to abandon the operation ( LAST CHANCE )" << std::endl;

	std::cin >> check;

	while (check != 1 && check != 0 )
	{
		std::cout << "\t-Missle has been armed and is ready to launch!" << std::endl;
		std::cout << "\t-Press 1 to launch the missle" << std::endl;
		std::cout << "\t-Press 0 to abandon the operation ( LAST CHANCE )" << std::endl;

		std::cin >> check;
	
	}

	if (warHead == 3) // if godlike missle check
	{
		hitX = true;
		hitY = true;
	}

	if (check == 0 )
	{
		return;
	}

	if (check == 1)
	{
		system("CLS");
		std::cout << "\t-Missle has been launched!" << std::endl;
		std::cout << "\t-Waiting for the result!" << std::endl;


		float tempX{ 0 };
		float tempY{ 0 };

		while (!hitX)
		{
			tempX += 1;

			if (tempX == targetX)
			{
				hitX = true;
			}
			
			if (tempX > targetX )
			{
				hitX = false;
				break;
			}
		}

		while (!hitY)
		{
			if (warHead == 2) // if radioactive missle 
			{
				tempY += rand() % 2 + 1; // uses random 1-2 to add to the Y axis to randomise hit or no
			}

			if (warHead == 1) // if Nuclear missle
			{
				tempY += 2;
			}


			if (tempY == targetY)
			{
				hitY = true;
			}

			if ( tempY > targetY)
			{
				hitY = false;
				break;
			}
		}

		std::cout << "\t-Please press ENTER to see the results!" << std::endl;

	}
	resultReport();
}



void resultReport()
{
	//1)Nuclear Warhead   // kinda random hit
	//2)Radioactive Warhead 
	//3)Godlike Warhead  ALWAYS HIT SUCCESSFUL

	

	std::string temp{ "" };
	system("CLS");
	if (hitY == false || hitX == false) // if any coord is false then its miss 
	{
		std::cout << "==================================================================================================== " << std::endl;
		std::cout << "\t-MISSED THE TARGET!" << std::endl;
		std::cout << "\t-Target managed to flee :( !" << std::endl;
		std::cout << "\t-Would you like to attack another target sir ? (Yes or No)!" << std::endl;
		std::cin >> temp;
		while (temp != "yes" && temp != "YES" && temp != "Yes " && temp != "no" && temp != "No" && temp != "NO")
		{
			std::cout << "-Please type Yes or No " << std::endl;
			std::cin >> temp;
		}


		if (temp == "Yes" || temp == "yes" || temp == "YES") // reset the warhead
		{
			selectWarHead();
		}

		if (temp == "no" || temp == "NO" || temp == "No") 
		{
			return;
		}

	}

	if (hitY == true && hitX == true) // if hit
	{
		std::cout << "==================================================================================================== " << std::endl;
		std::cout << "\t-TARGET WAS SUCCESSFULY DESTROYED!" << std::endl;
		std::cout << "\t-Target is no more :) " << std::endl;
		std::cout << "\t-Would you like to attack another target sir ? (Yes or No)!" << std::endl;
		std::cin >> temp;
		while (temp != "yes" && temp != "YES" && temp != "Yes " && temp != "no" && temp != "No" && temp != "NO")
		{
			std::cout << "-Please type Yes or No " << std::endl;
			std::cin >> temp;
		}


		if (temp == "Yes" || temp == "yes" || temp == "YES") // reset the warhead
		{
			selectWarHead();
		}

		if (temp == "no" || temp == "NO" || temp == "No")
		{
			return;
		}
	}
}
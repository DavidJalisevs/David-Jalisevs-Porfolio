#include "GamerTag.h"
using namespace std;
std::string GamerTag::enterName()
{
	cout << "welcome to our boogle game its the best version" << endl;
	cout << "please enter your gamertag here :";
	cin >> gamerTag;
	system("CLS");
	return gamerTag;
}

void GamerTag::checkName()
{
	gamerTag = "hello";
	if (gamerTag == "")
	{
		std::cout << "No Gamer tag" << std::endl;
		gamerTag == "noGamerTag";
	}
}

void GamerTag::displayName(std::string gamerTag)
{
	cout << "Thank you for entering your gamertag :" << gamerTag << ". That is a great name." << endl;
}

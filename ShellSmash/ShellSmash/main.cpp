/// <summary>
/// simple game loop for SFML[2.5.1]
/// 
/// @author - David Jalisevs
/// @date january 2020
/// Estimate time - 30 hours
/// Session 1 - was aorund 2 hours
/// session 2 - around 2 hours ( Cameron did help with the velocity for loop, had to re-do everything to the FOR LOPPS) 
/// session 3 - goes on for already maybe 2 hours trying to figure out how to make the shell laucnh/ andrew told me how to calculate unit vector and lenght to make it move but works only with 1st click
/// session 4 - 2 hours cant do the booleans right 
/// session 5 2 hours in class trying to add second ball.
/// session 6 maybe almost 2 hours got the balls different colors but now they not moving 
/// sessuin 7 same day as session 6 spent a lot on the color change. Donal Howe gave me a hint and I managed to make it change 
/// session 8 about 1 hours trying to understand PETES code for collisions and then trying to make it work/
/// session 9
/// </summary>

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 


#include "Game.h"
#include "MyVector3.h"

/// <summary>
/// main enrtry point
/// </summary>
/// <returns>success or failure</returns>
int main()
{
	Game game;
	game.run();

	return 1; // success
}
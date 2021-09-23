/// <summary>
/// simple game loop for SFML[2.5.1]
/// 
/// @author David Jalisevs
/// @date November 2019
/// 
/// Estimated time 12 hrs
/// Actual time around 15 hours 
///	When :	Duration(min)
/// session 1: 60 minds added rectangles and lines
/// session 2: 60 min spent on trying to make the lines move nothing achieved
/// session 3: 120 mins spent on trying to make the lines move. now they move but inncorectly
/// session 4: 60 min or so trying to make my laser shoot and then re start from the base
/// session 5: spet about 60 minutes on making circle extend on the explosion
/// session 6: spet a lot of time maybe 2 hours on how to make lines collide and then reset 
/// session 7: spend 2 hours on trying to laser stop when it hits meteor even if not reached its mouse click point. nothing achieved
/// session 8: continue trying to cancel the line still nothing moved further to power bar trying to sync with the line
/// session 9: no Idea how to sync them doing research spent about 80 mins
/// session 10: now laser properly stops if collides and cancels meteor without going further/ added graphics cant make them change with same keyboard around 40 mins spent
/// Session 11: another 60 minuts , mainly just smooting game trying to make it better. // still need to make my power bar to work better as it works incorrecly
/// same as the GRAPHICS explosions.
/// session 12: another 30 or so min here and there just making it a better place 
/// 
///
/// -------------------------------------------------------------------------------------------------------
/// KNOWS PROBLEM / BUGS = Explosion sprite only shows once and does not keep appearing unless re open the game .
/// Known problem - Background theme will play for few seconds after switching back to no graphics mode as track is certanin seconds long
/// Warnings with random numbers for meteor.
/// 
/// =======================================================================================================
/// Total Time: as of now approx spent time is 810 minutes which is 13.5 hours. maybe more maybe less but around that time, I would say around third of it spent on research and steaming my brains
/// + 30 min
/// 
/// New total time: is about 840 mins about 14 hours 
/// IPDATE max score; 222 record
/// </summary>
/// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// INSTRUCTIONS and RULES
/// 1 - More Meteors you destroy faster they travel, they start very slowly. There is a speed cap.
/// 2 - To change from potato graphics to fun and nice and cool and to get sounds PRESS " G "
/// 3 - One destroyed meteor is 3 Points.
/// 4 - every reached 50 points will grant you 3 EXTRA HP. 
/// 5 - Game might look easy at the beginning as the meteors travel slowly but it will get pretty hard after few destroyed .
/// 6 - Laser moves fast at the beginning to make player think this game is too easy. Power bar plays insignificant role as game is fast paced,
/// 
/// 
/// </summary>
/// 
/// 
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
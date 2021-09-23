// Game class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function
#include <SFML/Audio.hpp>


#include "Globals.h"   // include Global header file
#include "Player.h"   // include Player header file
#include "Enemy.h"
#include "smartEnemy.h"
#include "Bullet.h"


class Game
{
	// private data members

	// put your game objects here eg player object and 
	Player myPlayer;

	//smart enemy object
	SmartEnemy SmartEnemyOne;

	// array of enemy objects etc.
	Enemy regularEnemy;

	// bullet object
	Bullet myBullet;

	sf::RenderWindow window;

public:
	sf::Font m_font;  // font for writing text
	sf::Text m_message;  // text to write on the screen
	sf::Text m_healthMessage; // healt message 
	sf::Text m_scoreMessage; // score of the player
	sf::Text m_gameOverText; // game over text // lost
	sf::Texture m_backgrounds; // background texture
	sf::Sprite m_backsprite; // background sprtire
	static const int SMART_MAX{ 2 }; // max for smart enemye
	static const int MAX{ 3 }; // max for reg enemy

	int m_playerHealth{ 5 }; // player health points 
	int m_playerScore{ 0 }; // player score 
	bool bulletCollideControl = false; // so when the bullet hits regular enemy it resets bullet in Bullet.cpp
	bool smartEnemyControl = false; // so when the bullet hits regular enemy it respawns smart enemy in smartEnemy.cpp
	sf::Clock clock; // starts the clock
	
	bool isRegEnemyAlive = true; // reg control
	bool isPlayerAlive = true; // if player is alive 

	sf::SoundBuffer m_backGroundBuffer; // background sound
	sf::Sound m_backGroundSound;
	sf::SoundBuffer m_deadBuffer; // game over sound
	sf::Sound m_deadSound;
	sf::SoundBuffer m_regFloorBuffer; // when regular enemie touch the floor
	sf::Sound m_regFloorSound;

public:	  // declaration of member functions	
	Game(); // default constructor
	void	loadContent(); // loads content
	void	run(); // runs the game
	void	update(); // update the game
	void	draw(); // draws on the screen
	void	backGround(); // background 
	void    collisions(); // checkks for collisions
	void	setSound(); // sets the sound for te game

};

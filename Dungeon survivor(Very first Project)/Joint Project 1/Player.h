// Player class declaration
#pragma once
#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function
#include "Globals.h"

//#include 

	
class Player
{
	// private data members

	int m_playerHp{ 3 }; // player Healthpoints 
	float m_speed{ 5 }; // speed of the player 
	sf::Texture m_playerTexture; // plauyer texture not used for
	float m_velocityPlayer{ 20.0f }; // speed of the player
	float m_playerFrameIncrement{ 0.35f }; // how fast 
	float m_playerFrameCounter{ 0.0f };
	int m_playerFrame{ 0 };
	bool isPlayerMove = false; // if pplayer is moving 



public:

	sf::Sprite m_playerSprite; // player sprite not used yet

	void draw(sf::RenderWindow& t_window); // draws th eplayer
	void move();// moves plater
	void boundryCheck(); // checks for the walls
	void setBody(); // sets the body
};
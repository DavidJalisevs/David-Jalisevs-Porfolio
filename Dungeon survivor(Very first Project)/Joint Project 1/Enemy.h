#pragma once
#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function
#include "Globals.h"
class Enemy
{

	static const int MAX_ENEMY{ 3 }; // max enemies in the game
	int m_activeRegularEnemies{ 3 }; // curennly enemies in the game
	float m_enemySpeed{ 0.0f }; // speed of the enemies set up rando
	int m_enemyRadius{ 25 }; // radius of the enemy 
	float m_enemyFrameIncrement{ 0.10f }; // how fast 
	float m_enemyFrameCounter{ 0.0f }; // counter for animation
	int m_enemyFrame{ 0 }; // frame of the animation


	sf::Texture regEnemyTexture; // texture of the regularEnemy

	sf::Vector2f m_randomTank{ 0.0f,0.0f }; // random spawn postion of the enemy
	sf::Vector2f m_randomTank2{ 0.0f,0.0f }; // random spawn postion of the enemy
	sf::Vector2f m_randomTank3{ 0.0f,0.0f }; // random spawn postion of the enemy


	bool enemyAlive = false; // if enemy is alive or dead
	sf::Clock clock; // starts the clock



public:
	sf::Sprite squareEnemy[MAX_ENEMY]; // body of the enemy

	void enemyDraw(sf::RenderWindow& t_window); // draws enemy
	void enemyMove(); // moves eney
	void boundryCheckTank(); // checks for the walls
	void enemySetUp(); // sets up body of the enemy
	void animateEnemy(); // animates enemy 
	void regEnemyUpdate(); // updates here rather than in game.cpp
};


#pragma once
#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function
#include "Globals.h"

class SmartEnemy
{

	static const int MAX_ENEMY{ 2 }; // max enemies in the game
	int m_activeSmartEnemies{ 2 }; // curennly enemies in the game
	float m_enemySpeed{ 2.0f }; // speed of the enemies set up rando
	int m_enemyRadius{ 25 }; // radius of the enemy 
	float m_enemyFrameIncrement{ 0.10f }; // how fast 
	float m_enemyFrameCounter{ 0.0f }; // frame counter to animate
	int m_enemyFrame{ 0 }; // enemy frame 
	sf::Text m_healthMessage; // displays helth message 

	static const int SMART_MAX{ 2 };
	

	sf::Vector2f enemyStart[SMART_MAX];//{ 0.0f,0.0f }; // meteor start
	sf::Vector2f enemyActEnding[SMART_MAX];// { 0.0f, 0.0f }; // meteor end 
	sf::VertexArray m_enemyLine{ sf::Lines }; // meteor draw
	sf::VertexArray m_enemyLine2{ sf::Lines }; // meteor draw
	sf::Vector2f m_enemyHeading[SMART_MAX];//{ 0.0f,0.0f }; // heading but for meteor
	sf::Vector2f m_enemyVelocity[SMART_MAX];//{ 0.0f,0.0f }; // used for meteor velocity

	bool isEnemySetup = false; // to set up the smart enemy line

	sf::Texture smartEnemyTexture; // texture 

	bool enemyAlive = false; // if enemy is alive or dead

public:
	
	void enemyDraw(sf::RenderWindow& t_window); // draws enemy

	sf::Sprite smartEnemySprite[SMART_MAX]; // sprite for the smart enemy 

	void smartBody(); // sets up the body of the smart enemt
	void enemyVelocity(sf::Vector2f t_playerPos); // calculates velocity and heading of the enemy 
	void linesEnemy(); // draws the line 
	void smartCollision(sf::FloatRect t_bounds, int &t_playerHealth); //collisions that checks it for the walls  and player 
	void bulletCollision(sf::FloatRect t_bulletPos); // checks collision for the bullets 
	void smartAnimate(); // animates the enemy 
};


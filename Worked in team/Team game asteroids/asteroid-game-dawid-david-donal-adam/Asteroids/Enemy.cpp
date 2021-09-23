
#include "Enemy.h"
#include "Game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "MyVector2.h"

/// <summary>
/// author Dawid Jerdonek
/// date 03/04/2020
/// Time : 50 minutes
/// </summary>

Enemy::Enemy()
{
	loadContent();
	m_dead = false; //Enemy is alive
}

Enemy::~Enemy()
{
}

/// <summary>
/// Draw the enemy
/// </summary>
/// <param name="t_window"></param>
void Enemy::drawEnemy(sf::RenderWindow& t_window)
{
	if (m_health <= 0)
	{
		m_dead = true;
	}
	if (m_dead == false) //Render if alive
	{
		t_window.draw(m_enemySprite);
	}
}

/// <summary>
/// Load the sprite
/// </summary>
void Enemy::loadContent()
{
	if (!m_enemyTexture.loadFromFile("ASSETS\\IMAGES\\laser.png")) //Check if default sprite loads
	{
		//Error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_enemySprite.setTexture(m_enemyTexture);
}

/// <summary>
/// Determine randomised enemy movement
/// </summary>
void Enemy::determineMove()
{
	m_enemyPos = m_enemySprite.getPosition();
	m_time += m_moveClock.restart();

	//Change direction evry 0.6 seconds
	if (m_time.asSeconds() >= 0.6f)
	{
		enemyDirection = (rand() % 4) + 1; //Randomise direction
		m_time = sf::Time::Zero;
	}

	if (enemyDirection == 1)
	{
		enemyLeft();
		enemyBoundary();
	}
	else if (enemyDirection == 2)
	{
		enemyRight();
		enemyBoundary();
	}
	else if (enemyDirection == 3)
	{
		enemyUp();
		enemyBoundary();
	}
	else if (enemyDirection == 4)
	{
		enemyDown();
		enemyBoundary();
	}
}

/// <summary>
/// Move enemy Left
/// </summary>
void Enemy::enemyLeft()
{
	sf::Vector2f currentPos = m_enemySprite.getPosition(); //Get current position
	currentPos.x -= m_speed;
	m_enemySprite.setPosition(currentPos.x, currentPos.y); //Set a new position after moving
}

/// <summary>
/// Move enemy Right
/// </summary>
void Enemy::enemyRight()
{
	sf::Vector2f currentPos = m_enemySprite.getPosition(); //Get current position
	currentPos.x += m_speed;
	m_enemySprite.setPosition(currentPos.x, currentPos.y); //Set a new position after moving
}

/// <summary>
/// Move enemy Down
/// </summary>
void Enemy::enemyDown()
{
	sf::Vector2f currentPos = m_enemySprite.getPosition(); //Get current position
	currentPos.y += m_speed;
	m_enemySprite.setPosition(currentPos.x, currentPos.y); //Set a new position after moving
}

/// <summary>
/// Move enemy Up
/// </summary>
void Enemy::enemyUp()
{
	sf::Vector2f currentPos = m_enemySprite.getPosition(); //Get current position
	currentPos.y -= m_speed;
	m_enemySprite.setPosition(currentPos.x, currentPos.y); //Set a new position after moving
}

/// <summary>
/// Set enemy boundaries
/// </summary>
void Enemy::enemyBoundary()
{
	//Get the current position of the player sprite
	float posX = m_enemySprite.getPosition().x;
	float posY = m_enemySprite.getPosition().y;

	if (posX <= 0)
	{
		posX = 0; //Change x to zero
		m_enemySprite.setPosition(posX, posY);
	}

	if (posX >= WIDTH - SPRITE_SIZE)
	{
		posX = WIDTH - (SPRITE_SIZE); //Change x to the size of the screen and subtract the width of the enemy sprite
		m_enemySprite.setPosition(posX, posY);
	}

	if (posY <= 0)
	{
		posY = 0; //Change y to zero
		m_enemySprite.setPosition(posX, posY);
	}

	if (posY >= HEIGHT - SPRITE_SIZE)
	{
		posY = HEIGHT - SPRITE_SIZE; //Change y to the size of the screen and subtract the height of the enemy sprite
		m_enemySprite.setPosition(posX, posY);
	}
	
}

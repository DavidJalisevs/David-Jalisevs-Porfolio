
#include "Asteroid.h"
#include "Game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "MyVector2.h"


/// <summary>
/// author Dawid Jerdonek
/// date 02/04/2020, 03/04/2020
/// Time: 2 hours
/// </summary>

Asteroid::Asteroid()
{
	loadContent();
}

Asteroid::~Asteroid()
{
}

/// <summary>
/// Asteroid Sprite load
/// </summary>
void Asteroid::loadContent()
{

	if (!m_asteroidText.loadFromFile("ASSETS\\IMAGES\\Asteroid.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading background" << std::endl;
	}
	m_asteroidSprite.setTexture(m_asteroidText);
	srand(time(nullptr));
}

/// <summary>
/// Draw Asteroid
/// </summary>
/// <param name="t_window"></param>
void Asteroid::drawAsteroid(sf::RenderWindow& t_window)
{
	t_window.draw(m_asteroidSprite);
}

/// <summary>
/// Asteroid randomised movement
/// </summary>
void Asteroid::asteroidMovement()
{
	if (m_asteroidAlive == false)
	{
		asteroidRandom();
		m_asteroidStart = sf::Vector2f{ m_randomPos,-0.5f }; //Start asteroid off-screen
		m_asteroidEnd = sf::Vector2f{ m_randomPosTwo,500.0f }; //Mark a position at bottom of screen
		m_currentAsteroidEnd = m_asteroidStart;
		m_asteroidDirection = m_asteroidEnd - m_asteroidStart; //Get the direction
		m_asteroidDirection = vectorUnitVector(m_asteroidDirection);
		m_asteroidVelocity = m_asteroidDirection * m_asteroidSpeed; //Get Velocity
		m_asteroidAlive = true; //Asteroid is now active

	}
	if (m_asteroidAlive == true)
	{
		m_currentAsteroidEnd += m_asteroidVelocity; //Set next asteroid position
		sf::Vertex lineStart{ m_asteroidStart,sf::Color::Red };
		sf::Vertex lineEnd{ m_currentAsteroidEnd,sf::Color::Yellow };
		m_asteroid.clear();
		m_asteroid.append(lineStart);
		m_asteroid.append(lineEnd);
		m_asteroidSprite.setPosition(m_currentAsteroidEnd); //Move the asteroid
	}

	if (m_currentAsteroidEnd.y >= m_asteroidEnd.y + 100)
	{
		m_asteroidAlive = false; //If asteroid goes off-screen an new one is spawned
	}

}

/// <summary>
/// Random Number Generator
/// </summary>
void Asteroid::asteroidRandom() // Gets a random number for the asteroid to use as a Start and End
{
	m_randomPos = (rand() % 800) + 1;
	m_randomPosTwo = (rand() % 800) + 1;
}




/// <summary>
/// by David Jalisevs
/// </summary>
/// <param name="t_bulletPos"></param>
void Asteroid::asteroidCollisionBullet(sf::FloatRect t_bulletPos)
{
	if (t_bulletPos.intersects(m_asteroidSprite.getGlobalBounds()))
	{
		sf::Vector2f m_randomTank{ 0.0f,0.0f };
		m_randomTank.x = rand() % 600 + 1; // warning with possible loss of date
		m_randomTank.y = 600.0f;
		m_asteroidStart = sf::Vector2f{ m_randomTank };
		m_asteroidDirection = sf::Vector2f{ m_randomTank };
		m_currentAsteroidEnd = sf::Vector2f{ m_randomTank };
		m_asteroidSprite.setPosition(m_asteroidStart);
	}
}


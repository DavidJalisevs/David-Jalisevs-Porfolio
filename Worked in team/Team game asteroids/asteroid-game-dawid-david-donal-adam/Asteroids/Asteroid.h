#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML\Graphics.hpp>

/// <summary>
/// @author Dawid Jerdonek
/// @date 02/04/2020
/// 

class Asteroid
{
public:

	Asteroid();
	~Asteroid();

	sf::Texture m_asteroidText;

	void loadContent();  //Load asteroid texture
	void drawAsteroid(sf::RenderWindow& t_window); //Draw the asteroid
	void asteroidMovement(); //Movement of asteroid
	void asteroidRandom(); //Randomise Asteroid positions

	void asteroidCollisionBullet(sf::FloatRect t_bulletPos);

	sf::Vector2f enemyStart{ 0.0f,0.0f }; //Asteroid start
	sf::Vector2f enemyActEnding{ 0.0f, 0.0f }; //Asteroid End 
	sf::VertexArray m_enemyLine{ sf::Lines }; //Asteroid Array
	sf::Vector2f m_enemyHeading{ 0.0f,0.0f }; //Heading but for Asteroid
	sf::Vector2f m_enemyVelocity{ 0.0f,0.0f }; //Used for Asteroid velocity






	sf::Sprite m_asteroidSprite; //Sprite of the asteroids

private:

	bool m_asteroidAlive = false; //Is an asteroid drawn already
	float m_randomPos = 0.0f; //Random top of screen position
	float m_randomPosTwo = 0.0f; //Random bottom of screen position
	float m_asteroidSpeed = 4.0f; //Speed of the asteroids

	

	sf::VertexArray m_asteroid{ sf::Lines }; //Vertex Array used to set the path of the asteroid
	sf::Vector2f m_asteroidStart{0.0f, 0.0f};
	sf::Vector2f m_asteroidEnd{ 0.0f, 0.0f };
	sf::Vector2f m_asteroidDirection{ 0.0f, 0.0f };
	sf::Vector2f m_currentAsteroidEnd{ 0.0f, 0.0f };
	sf::Vector2f m_asteroidVelocity{ 0.0f, 0.0f };

};

#endif // !ASTEROID_H
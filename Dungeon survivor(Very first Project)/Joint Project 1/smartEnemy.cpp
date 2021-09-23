#include "smartEnemy.h"
#include "MyVector2.h" // vectors



void SmartEnemy::enemyDraw(sf::RenderWindow& t_window) // draws enemies 
{
	if (enemyAlive)
	{

		for (int i = 0; i < m_activeSmartEnemies ; i++)
		{
			t_window.draw(smartEnemySprite[i]);
			//t_window.draw(smartEnemySprite[1]);
		}

		t_window.draw(m_enemyLine);
		t_window.draw(m_enemyLine2);
	}
}


/// <summary>
/// body of the smart enemy 
/// </summary>
void SmartEnemy::smartBody()
{
	for (int i = 0; i < m_activeSmartEnemies; i++)
	{
		if (!smartEnemyTexture.loadFromFile("ASSETS\\IMAGES\\enemySmart.png"))
		{
			// simple error message if previous call fails
			std::cout << "problem loading logo" << std::endl;
		}

		smartEnemySprite[i].setTexture(smartEnemyTexture);
		smartEnemySprite[i].setOrigin(sf::Vector2f{ 60.0f,70.0f });
		smartEnemySprite[i].setScale(sf::Vector2f{ -.7f,-.7f });
		smartEnemySprite[i].setPosition(sf::Vector2f{ enemyActEnding[i] });
		//smartEnemySprite[i].setTextureRect(sf::IntRect{  0, 0, 138 , 138 });

		if (i > 0)
		{
			smartEnemySprite[i].setPosition(sf::Vector2f{ enemyActEnding[i] });

		}
		//smartEnemySprite[i].setRotation(180.0f);
	}
	enemyAlive = true;
}

/// <summary>
/// animates the player 
/// </summary>
void SmartEnemy::smartAnimate()
{
	m_enemyFrameCounter += m_enemyFrameIncrement;
	m_enemyFrame = static_cast<int>(m_enemyFrameCounter) % 3; // change valuues later to see the difference 
	smartEnemySprite[1].setTextureRect(sf::IntRect{ m_enemyFrame * 135, 0, 131 , 135 });

	m_enemyFrameCounter += m_enemyFrameIncrement;
	m_enemyFrame = static_cast<int>(m_enemyFrameCounter) % 3; // change valuues later to see the difference 
	smartEnemySprite[0].setTextureRect(sf::IntRect{ m_enemyFrame * 135, 0, 131 , 135 });
}



/// <summary>
/// checks if the player collides with the walls and or player 
/// </summary>
/// <param name="t_playerPos"></param>
/// <param name="t_playerHealth"></param>
void SmartEnemy::smartCollision(sf::FloatRect t_playerPos, int& t_playerHealth)
{
	if (t_playerPos.intersects(smartEnemySprite[0].getGlobalBounds()))
	{
		t_playerHealth--;
		std::cout << " HP DECREMENT DRAGON0 " << t_playerHealth << std::endl;

		sf::Vector2f m_randomTank{ 0.0f,0.0f };
		m_randomTank.x = rand() % 1500 + 1; // warning with possible loss of date
		m_randomTank.y = 800.0f;
		enemyStart[0] = sf::Vector2f{ m_randomTank };
		m_enemyHeading[0] = sf::Vector2f{ m_randomTank };
		enemyActEnding[0] = sf::Vector2f{ m_randomTank };
		smartEnemySprite[0].setPosition(enemyStart[0]);
	}

	if (  smartEnemySprite[0].getPosition().x >= SCREEN_WIDTH + 20 || smartEnemySprite[0].getPosition().x <= 10   || smartEnemySprite[0].getPosition().y <= 5  ) // bounds for walls
	{
		m_enemyLine.clear();
		std::cout << "colld2222222222222222" << std::endl;


		sf::Vector2f m_randomTank{ 0.0f,0.0f };
		m_randomTank.x = rand() % 1500 + 1; // warning with possible loss of date
		m_randomTank.y = 800.0f;
		enemyStart[0] = sf::Vector2f{ m_randomTank };
		m_enemyHeading[0] = sf::Vector2f{ m_randomTank };
		enemyActEnding[0] = sf::Vector2f{ m_randomTank };
		smartEnemySprite[0].setPosition(enemyStart[0]);
	}

	/// <summary>
	/// checks for the walls of the smartEnemyTwo
	/// </summary>
	
	if (t_playerPos.intersects(smartEnemySprite[1].getGlobalBounds()))
	{
		
		t_playerHealth--;
		std::cout << " HP DECREMENT DRAGON1 " << t_playerHealth << std::endl;

		sf::Vector2f m_randomTank{ 0.0f,0.0f };
		enemyStart[1].x = rand() % 1500 + 1; // warning with possible loss of date
		enemyStart[1].y = 0.0f;
		m_enemyHeading[1] = sf::Vector2f{ enemyStart[1] };
		enemyActEnding[1] = sf::Vector2f{ enemyStart[1] };
		smartEnemySprite[1].setPosition(enemyStart[1]);
	}
	
	if ( smartEnemySprite[1].getPosition().y >= SCREEN_HEIGHT + 5 || smartEnemySprite[1].getPosition().x <= 10  || smartEnemySprite[1].getPosition().x >= SCREEN_WIDTH + 20) // bounds for walls
	{

		m_enemyLine.clear();
		std::cout << "colld1111111111" << std::endl;


		sf::Vector2f m_randomTank{ 0.0f,0.0f };
		enemyStart[1].x = rand() % 1500 + 1; // warning with possible loss of date
		enemyStart[1].y = 0.0f;
		m_enemyHeading[1] = sf::Vector2f{ enemyStart[1] };
		enemyActEnding[1] = sf::Vector2f{ enemyStart[1] };
		smartEnemySprite[1].setPosition(enemyStart[1]);
	}
}

/// <summary>
/// checks collisions with the bullet 
/// </summary>
/// <param name="t_bulletPos"></param>
void SmartEnemy::bulletCollision(sf::FloatRect t_bulletPos)
{

	if (t_bulletPos.intersects(smartEnemySprite[1].getGlobalBounds()))
	{
		std::cout << " BULLET HIT DRAGON 1 " << std::endl;

		sf::Vector2f m_randomTank{ 0.0f,0.0f };
		enemyStart[1].x = rand() % 1500 + 1; // warning with possible loss of date
		enemyStart[1].y = 0.0f;
		m_enemyHeading[1] = sf::Vector2f{ enemyStart[1] };
		enemyActEnding[1] = sf::Vector2f{ enemyStart[1] };
		smartEnemySprite[1].setPosition(enemyStart[1]);
	}

	if (t_bulletPos.intersects(smartEnemySprite[0].getGlobalBounds()))
	{
		std::cout << " BULLET HIT DRAGON 0 " << std::endl;

		sf::Vector2f m_randomTank{ 0.0f,0.0f };
		m_randomTank.x = rand() % 1500 + 1; // warning with possible loss of date
		m_randomTank.y = 800.0f;
		enemyStart[0] = sf::Vector2f{ m_randomTank };
		m_enemyHeading[0] = sf::Vector2f{ m_randomTank };
		enemyActEnding[0] = sf::Vector2f{ m_randomTank };
		smartEnemySprite[0].setPosition(enemyStart[0]);
	}
}

/// <summary>
/// sets the line between enemy and player 
/// </summary>
void SmartEnemy::linesEnemy()
{
	m_enemyLine.clear();
	m_enemyLine2.clear();


	// ENEMY line set up
	sf::Vertex meteorStartVertex{ sf::Vector2f{enemyStart[0]},sf::Color::Transparent }; // laser lines
	sf::Vertex meteorEnd{ sf::Vector2f{enemyActEnding[0]},sf::Color::Transparent }; // laser lines 

	sf::Vertex meteorStartVertex2{ sf::Vector2f{enemyStart[1]}, sf::Color::Transparent }; // laser lines
	sf::Vertex meteorEnd2{ sf::Vector2f{enemyActEnding[1]},sf::Color::Transparent }; // laser lines 


	m_enemyLine.append(meteorStartVertex);
	m_enemyLine.append(meteorEnd);
	m_enemyLine2.append(meteorStartVertex2);
	m_enemyLine2.append(meteorEnd2);
}

/// <summary>
/// calculates the velocity of the enemy to the player 
/// </summary>
/// <param name="t_playerPos"></param>
void SmartEnemy::enemyVelocity(sf::Vector2f t_playerPos) // meteor velocity
{
	for (int i = 0; i < m_activeSmartEnemies; i++)
	{
		if (!isEnemySetup)
		{
			if (i == 0)
			{
				sf::Vector2f m_randomTank{ 0.0f,0.0f };
				m_randomTank.x = rand() % 1500 + 1; // warning with possible loss of date
				m_randomTank.y = 800.0f;
				enemyStart[0] = sf::Vector2f{ m_randomTank };
				m_enemyHeading[0] = sf::Vector2f{ m_randomTank };
				enemyActEnding[0] = sf::Vector2f{ m_randomTank };
				smartEnemySprite[0].setPosition(enemyStart[0]);
			}

			if (i == 1)
			{
				sf::Vector2f m_randomTank{ 0.0f,0.0f };
				m_randomTank.x = rand() % 1500 + 1; // warning with possible loss of date
				m_randomTank.y = 0.0f;
				enemyStart[1] = sf::Vector2f{ m_randomTank };
				m_enemyHeading[1] = sf::Vector2f{ m_randomTank };
				enemyActEnding[1] = sf::Vector2f{ m_randomTank };
				smartEnemySprite[1].setPosition(enemyStart[1]);
				isEnemySetup = true;
			}
		}

		m_enemyHeading[i] = t_playerPos - enemyActEnding[i];
		m_enemyHeading[i] = vectorUnitVector(m_enemyHeading[i]);
		m_enemyVelocity[i] = m_enemyHeading[i] * m_enemySpeed; // velocity
		enemyActEnding[i] = smartEnemySprite[i].getPosition();
		enemyActEnding[i] += m_enemyVelocity[i]; // goes
	}
}
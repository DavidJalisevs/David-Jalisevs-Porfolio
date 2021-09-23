#include "Enemy.h"

/// <summary>
/// draws 
/// </summary>
/// <param name="t_window"></param>
void Enemy::enemyDraw(sf::RenderWindow& t_window) // draws enemies 
{
	if (enemyAlive)
	{
		for (int i = 0; i < m_activeRegularEnemies; i++)
		{
			if (squareEnemy[i].getPosition().y > 50)
			{
				t_window.draw(squareEnemy[i]);
			}
		}
	}
}

void Enemy::regEnemyUpdate() // set up of the enemies
{
	enemyMove();
	boundryCheckTank();
	animateEnemy();
}

void Enemy::enemySetUp() // set up of the enemies
{
	sf::Time elapsed1 = clock.getElapsedTime();
	std::cout << "time" << elapsed1.asSeconds() << std::endl;
	clock.restart();

	m_randomTank.x = (rand() % static_cast<int>(SCREEN_WIDTH)) + 1; // warning with possible loss of date
	m_randomTank2.x = (rand() % static_cast<int>(SCREEN_WIDTH)) + 1; // warning with possible loss of date
	m_randomTank3.x = (rand() % static_cast<int>(SCREEN_WIDTH)) + 1; // warning with possible loss of date

	std::cout << m_randomTank.x << std::endl;

	for (int i = 0; i < m_activeRegularEnemies; i++)
	{
		if (!regEnemyTexture.loadFromFile("ASSETS\\IMAGES\\enemy2.png"))
		{
			// simple error message if previous call fails
			std::cout << "problem loading logo" << std::endl;
		}

		squareEnemy[i].setTexture(regEnemyTexture);
		squareEnemy[i].setOrigin(sf::Vector2f{ 50.0f, 70.0f });
		squareEnemy[i].setScale(sf::Vector2f{ 1.5f,1.5f });
		squareEnemy[0].setPosition(m_randomTank);
		squareEnemy[1].setPosition(m_randomTank2);
		squareEnemy[2].setPosition(m_randomTank3);

	}

	enemyAlive = true;
}

/// <summary>
/// animates regularEnemy
/// </summary>
void Enemy::animateEnemy()
{
	if (enemyAlive)
	{
		//for (int i = 0; i < MAX_ENEMY; i++)
		//{
			//// to animate sprite
		m_enemyFrameCounter += m_enemyFrameIncrement;
		m_enemyFrame = static_cast<int>(m_enemyFrameCounter) % 4; // change valuues later to see the difference 
		squareEnemy[0].setTextureRect(sf::IntRect{ m_enemyFrame * 71, 0, 55 , 60 });

		m_enemyFrameCounter += m_enemyFrameIncrement;
		m_enemyFrame = static_cast<int>(m_enemyFrameCounter) % 4; // change valuues later to see the difference 
		squareEnemy[1].setTextureRect(sf::IntRect{ m_enemyFrame * 71, 0, 55 , 60 });

		m_enemyFrameCounter += m_enemyFrameIncrement;
		m_enemyFrame = static_cast<int>(m_enemyFrameCounter) % 4; // change valuues later to see the difference 
		squareEnemy[2].setTextureRect(sf::IntRect{ m_enemyFrame * 71, 0, 55 , 60 });
		//}
	}
}

/// <summary>
/// makes regular enemy move
/// </summary>
void Enemy::enemyMove() // makes enemies move
{
	if (enemyAlive)
	{
		for (int i = 0; i < m_activeRegularEnemies; i++)
		{
			int f{ 2 };
			int g{ 0 };

			m_enemySpeed = 0.1;
			//std::cout <<"Enemy speed" << m_enemySpeed << std::endl;  // to check numbers 
			sf::Vector2f pos(squareEnemy[i].getPosition());
			pos.y += m_enemySpeed;
			squareEnemy[i].setPosition(pos);

			if (squareEnemy[i].getPosition().y > 50)
			{
				m_enemySpeed = (rand() % 4) + 0;
				//std::cout <<"Enemy speed" << m_enemySpeed << std::endl;  // to check numbers 
				sf::Vector2f pos(squareEnemy[i].getPosition());
				pos.y += m_enemySpeed;
				squareEnemy[i].setPosition(pos);
			}
		}
	}
}

/// <summary>
/// checks for the walls 
/// </summary>
void Enemy::boundryCheckTank() // checks for the walls
{
	if (enemyAlive)
	{
		for (int i = 0; i < m_activeRegularEnemies; i++)
		{
			if (squareEnemy[i].getPosition().x <= m_enemyRadius)
			{
				squareEnemy[i].setPosition(-3 + m_enemyRadius, squareEnemy[i].getPosition().y);
			}

			if (squareEnemy[i].getPosition().x >= SCREEN_WIDTH - m_enemyRadius)
			{
				squareEnemy[i].setPosition(SCREEN_WIDTH - m_enemyRadius + -3, squareEnemy[i].getPosition().y);
			}

			if (squareEnemy[i].getPosition().y <= m_enemyRadius)
			{
				squareEnemy[i].setPosition(squareEnemy[i].getPosition().x, m_enemyRadius);
			}

		}
	}
}

#ifndef ENEMY_H
#define ENEMY_H

#include <SFML\Graphics.hpp>

/// <summary>
/// @author Dawid Jerdonek
/// @date 03/04/2020
/// Enemy class
/// 
/// </summary>
class Enemy
{
public:

	Enemy();
	~Enemy();
	
	sf::Sprite m_enemySprite;

	void drawEnemy(sf::RenderWindow& t_window);

	sf::Vector2f m_enemyPos; //Position of enemy

	void loadContent(); //Load enemy 
	void determineMove(); //Determine when to move and where
	void enemyLeft(); //Move the enemy sprite left
	void enemyRight(); //Move the enemy sprite right
	void enemyDown(); //Move the enemy sprite down
	void enemyUp(); //Move the enemy sprite up
	void enemyBoundary(); //Boundaries for the enemy
	


private:

	const int WIDTH = 800;
	const int HEIGHT = 600;
	const int SPRITE_SIZE = 45;

	int m_health = 2;  //Health of Commander
	int m_speed = 3;
	float m_timer = 0; //Timer used for movement
	int enemyDirection = 0; //Direction of the enemy
	const float RADIUSf = 80.0f;

	bool m_dead; //Check if Commander is alive

	sf::Clock m_moveClock;
	sf::Time m_time;

	sf::Texture m_enemyTexture; //Commander texture default

};

#endif // !ENEMY_H

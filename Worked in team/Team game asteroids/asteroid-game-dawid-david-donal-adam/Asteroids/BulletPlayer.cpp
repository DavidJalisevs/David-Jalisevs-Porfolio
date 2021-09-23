#include "BulletPlayer.h"
#include "Game.h"
#include <iostream>


/// <summary>
/// Author DAVID JALISEVS
/// </summary>

Bullet::Bullet()
{
	if (!bulletTexture.loadFromFile("ASSETS\\IMAGES\\LaserPlayer.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	m_SpriteBullet.setTexture(bulletTexture);
	m_SpriteBullet.setOrigin(sf::Vector2f{ 20.0f,50.0f });
	m_SpriteBullet.setScale(sf::Vector2f{ 1.0f,1.0f });
	m_SpriteBullet.setPosition(100.0f, 100.0f);

}
//David was here

Bullet::~Bullet()
{
}



/// <summary>
/// draws
/// </summary>
/// <param name="t_window"></param>
void Bullet::drawBullet(sf::RenderWindow& t_window)
{

	t_window.draw(m_SpriteBullet);

}

/// <summary>
/// sets bullet body
/// </summary>
/// <param name="t_playerPos"></param>
void Bullet::setBulletBody(sf::Vector2f t_playerPos)
{
	if (!bulletTexture.loadFromFile("ASSETS\\IMAGES\\LaserPlayer.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	m_SpriteBullet.setTexture(bulletTexture);
	m_SpriteBullet.setOrigin(sf::Vector2f{ 20.0f,50.0f });
	m_SpriteBullet.setScale(sf::Vector2f{ 1.0f,1.0f });
	m_SpriteBullet.setPosition(100.0f, 100.0f);

}

/// <summary>
/// checks for the directions where player goes so it hits there 
/// </summary>
void Bullet::bulletDirection()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{

		m_rotaionValueBullet = m_SpriteBullet.getRotation();
		m_rotaionValueBullet -= 1.5;
		m_SpriteBullet.setRotation(m_rotaionValueBullet);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{

		m_rotaionValueBullet = m_SpriteBullet.getRotation();
		m_rotaionValueBullet += 1.5;
		m_SpriteBullet.setRotation(m_rotaionValueBullet);
	}

}




void Bullet::bulletFired(sf::Vector2f t_playerPos) // makes bullet move
{
	if (!m_bulletShot)
	{
		m_SpriteBullet.setPosition(-100.0f, -100.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_SpriteBullet.setPosition(t_playerPos);
		m_bulletShot = true;
		m_bulletCollided = false;

		//if (sf::Sound::Playing != m_shootSound.getStatus())  // to play sound
		//{
		m_shootSound.play();


	}


	if (m_bulletShot)
	{
		
			sf::Vector2f m_positionBullet(m_SpriteBullet.getPosition());

			m_angleBullet = m_rotaionValueBullet * 3.14f / 180;
			m_positionBullet.x += m_bulletSpeed * sin(m_angleBullet);
			m_positionBullet.y += m_bulletSpeed * (-cos(m_angleBullet));

			m_SpriteBullet.setPosition(m_positionBullet);
		

	}
}

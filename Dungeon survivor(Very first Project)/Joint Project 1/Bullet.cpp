#include "Bullet.h"
 // known bugs sometimes bullet goes only one direction unless you hit something, happens mostly after spaming control keys 


/// <summary>
/// draws
/// </summary>
/// <param name="t_window"></param>
void Bullet::drawBullet(sf::RenderWindow& t_window)
{
	
		t_window.draw(bulletSprite);
	
}

/// <summary>
/// sets the sound for the bullet 
/// </summary>
void Bullet::setSound()
{
	if (!m_shootBuffer.loadFromFile("ASSETS\\AUDIO\\shoot.wav")) // EXPLOSION SOUND
	{
		std::cout << "problem loading Explosion sound" << std::endl;
	}
	m_shootSound.setBuffer(m_shootBuffer);
	m_shootSound.setVolume(20.0f);
}

/// <summary>
/// sets bullet body
/// </summary>
/// <param name="t_playerPos"></param>
void Bullet::setBulletBody(sf::Vector2f t_playerPos)
{
	if (!bulletTexture.loadFromFile("ASSETS\\IMAGES\\fireball_up.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setOrigin(sf::Vector2f{ 20.0f,50.0f });
	bulletSprite.setScale(sf::Vector2f{ 1.0f,1.0f });
	bulletSprite.setPosition(-100.0f,-100.0f);
}

/// <summary>
/// checks for the directions where player goes so it hits there 
/// </summary>
void Bullet::bulletDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !m_bulletIsMoving )
	{
		m_bulletShotRight = true;
		m_bulletShotUp = false;
		m_bulletShotDown = false;
		m_bulletShotLeft = false;
	}

	else
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !m_bulletIsMoving)
	{
		m_bulletShotLeft = true;
		m_bulletShotUp = false;
		m_bulletShotDown = false;
		m_bulletShotRight = false;
	}

	else
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !m_bulletIsMoving)
	{
		m_bulletShotUp = false;
		m_bulletShotLeft = false;
		m_bulletShotRight = false;
		m_bulletShotDown = true;
	}

	else
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !m_bulletIsMoving)
	{
		m_bulletShotUp = true;
		m_bulletShotDown = false;
		m_bulletShotLeft = false;
		m_bulletShotRight = false;

	}
}




void Bullet::bulletFired(sf::Vector2f t_playerPos) // makes bullet move
{
	if (!m_bulletShot )
	{
		bulletSprite.setPosition(-100.0f,-100.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		bulletSprite.setPosition(t_playerPos);
		m_bulletShot = true;

		
		//if (sf::Sound::Playing != m_shootSound.getStatus())  // to play sound
		//{
			m_shootSound.play();
		
		
	}


	if (m_bulletShot)
	{
		if (m_bulletShotUp)
		{
			sf::Vector2f pos(bulletSprite.getPosition());
			pos.y -= m_bulletSpeed;
			bulletSprite.setPosition(pos);
			m_bulletIsMoving = true;

		}

		if (m_bulletShotDown)
		{
			sf::Vector2f pos(bulletSprite.getPosition());
			pos.y += m_bulletSpeed;
			bulletSprite.setPosition(pos);
			m_bulletIsMoving = true;
		
		}

		if (m_bulletShotRight)
		{
			sf::Vector2f pos(bulletSprite.getPosition());
			pos.x += m_bulletSpeed;
			bulletSprite.setPosition(pos);
			m_bulletIsMoving = true;
			
		}

		if (m_bulletShotLeft)
		{
			sf::Vector2f pos(bulletSprite.getPosition());
			pos.x -= m_bulletSpeed;
			bulletSprite.setPosition(pos);
			m_bulletIsMoving = true;
			

		}
	}
}


void Bullet::bulletBoundary(sf::Vector2f t_playerPos, bool& t_regControl, bool& t_smartControl) // check fof the bullet hit if
{
	if (bulletSprite.getPosition().y <= 0 || bulletSprite.getPosition().y >= SCREEN_HEIGHT || bulletSprite.getPosition().x >= SCREEN_WIDTH || bulletSprite.getPosition().x <= 0 || t_regControl == true || t_smartControl == true) // checks up 
	{
		m_bulletShot = false;
		m_bulletIsMoving = false;


		t_regControl = false;  // controls bullet from reg enemty
		t_smartControl = false; // controls bullet from smart enemy
	}
}


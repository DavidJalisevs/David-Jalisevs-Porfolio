
#include "Player.h"   // include Player header file
// Player function definitions here

/// <summary>
/// draws
/// </summary>
/// <param name="t_window"></param>
void Player::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_playerSprite);
}

/// <summary>
/// moves the player
/// </summary>
void Player::move()
{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			sf::Vector2f pos(m_playerSprite.getPosition());
			pos.x+=m_speed;
			// to animate sprite
			m_playerFrameCounter += m_playerFrameIncrement;
			m_playerFrame = static_cast<int>(m_playerFrameCounter) % 3; // change valuues later to see the difference 
			m_playerSprite.setTextureRect(sf::IntRect{ m_playerFrame * 50, 70, 40 , 55 });
			m_playerSprite.setPosition(pos);
			isPlayerMove = true;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			sf::Vector2f pos(m_playerSprite.getPosition());
			pos.x-=m_speed;
			// to animate sprite
			m_playerFrameCounter += m_playerFrameIncrement;
			m_playerFrame = static_cast<int>(m_playerFrameCounter) % 3; // change valuues later to see the difference 
			m_playerSprite.setTextureRect(sf::IntRect{ m_playerFrame * 50, 200, 40 , 55 });
			m_playerSprite.setPosition(pos);
			isPlayerMove = true;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			sf::Vector2f pos(m_playerSprite.getPosition());
			pos.y+=m_speed;
			// to animate sprite
			m_playerFrameCounter += m_playerFrameIncrement;
			m_playerFrame = static_cast<int>(m_playerFrameCounter) % 3; // change valuues later to see the difference 
			m_playerSprite.setTextureRect(sf::IntRect{ m_playerFrame * 50, 140, 40 , 50 });
			m_playerSprite.setPosition(pos);
			isPlayerMove = true;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			sf::Vector2f pos(m_playerSprite.getPosition());
			pos.y-=m_speed;
			// to animate sprite
			m_playerFrameCounter += m_playerFrameIncrement;
			m_playerFrame = static_cast<int>(m_playerFrameCounter) % 3; // change valuues later to see the difference 
			m_playerSprite.setTextureRect(sf::IntRect{ m_playerFrame * 50, 0, 40 , 60 });
			m_playerSprite.setPosition(pos);
			isPlayerMove = true;
		}

		
}

/// <summary>
/// checks for the walls 
/// </summary>
void Player::boundryCheck()
{
	if (isPlayerMove)
	{
		if (m_playerSprite.getPosition().x <= 0) // left side 
		{
			m_playerSprite.setPosition(SCREEN_WIDTH, m_playerSprite.getPosition().y);
		}

		if (m_playerSprite.getPosition().x >= SCREEN_WIDTH + 20) // checks right side
		{
			m_playerSprite.setPosition(0, m_playerSprite.getPosition().y);
		}

		if (m_playerSprite.getPosition().y <= 0) // checks up 
		{
			m_playerSprite.setPosition(m_playerSprite.getPosition().x, SCREEN_HEIGHT);// +m_playerRadius);
		}

		if (m_playerSprite.getPosition().y >= SCREEN_HEIGHT) // checks bottom
		{
			m_playerSprite.setPosition(m_playerSprite.getPosition().x, SCREEN_HEIGHT);//- m_playerRadius);
		}
	}
}


/// <summary>
/// sets the body of the player 
/// </summary>
void Player::setBody()
{
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\character.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setOrigin(sf::Vector2f{ 20.0f,50.0f });
	m_playerSprite.setScale(sf::Vector2f{ 1.5f,1.5f });
	m_playerSprite.setPosition(700.0f, 400.0f);
	m_playerSprite.setTextureRect(sf::IntRect{ 55,130,40,65 });

}



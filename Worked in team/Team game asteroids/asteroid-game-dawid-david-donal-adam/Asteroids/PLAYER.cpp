#include <iostream>
#include "Player.h"
#include "Game.h"


///@author donal howe
/// 
/// </summary>

Player::Player()
{
	m_fuel = 200.0f;
	loadContent();
}
//pete was hgere

Player::~Player()
{
}

void Player::movement(sf::Font& t_font)
{
	m_font = t_font;
	//sf::Vector2f pos;
	//if (thrustValue > 0.5)
	//{
	//	pos = m_playerSprite.getPosition();
	//	//pos.y--;
	//	//pos.
	//	pos.x = speedValue * cos(m_rotaionValue);
	//	pos.y = speedValue *sin(m_rotaionValue);
	//	m_playerSprite.setPosition(pos);
	//	thrustValue -= 0.05;
	//}
	//if (thrustValue < -0.5)
	//{
	//	pos = m_playerSprite.getPosition();
	//	//pos.y++;
	//	pos.x = speedValue * cos(m_rotaionValue);
	//	pos.y = speedValue * sin(m_rotaionValue);
	//	m_playerSprite.setPosition(pos);
	//	thrustValue += 0.1f;
	//}
	speedValue = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{

			m_rotaionValue = m_playerSprite.getRotation();
			m_rotaionValue -= 1.5;
			m_playerSprite.setRotation(m_rotaionValue);
			playerMoving = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_rotaionValue = m_playerSprite.getRotation();
			m_rotaionValue+=1.5;
			m_playerSprite.setRotation(m_rotaionValue);
			// set value for trust and then while it is being held increase that value
			playerMoving = true;
		}

if (m_fuel > 0)
{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			//thrustValue += 0.1f;
			//sm_position = m_playerSprite.getPosition();
				//pos.y--;
			//	//pos.
			playerMoving = true;
			speedValue = 4.0f;
			m_fuel--;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			//thrustValue += 0.1f;
			//sm_position = m_playerSprite.getPosition();
				//pos.y--;
			//	//pos.
			playerMoving = true;
			speedValue = -4.0f;
			m_fuel--;

		}
		else
		{
			if (speedValue > 0)
			{
				speedValue - 0.1f;
			}
		}
}
		m_angle = m_rotaionValue * 3.14f / 180;
		m_position.x += speedValue * sin(m_angle);
		m_position.y += speedValue * (-cos(m_angle));
		m_playerSprite.setPosition(m_position);
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		//{
		//	thrustValue -= 0.2f;
		//	
		//}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_escape = true;
	}
	if (m_escape == true)
	{
		Game::myGameState = GameState::MainMenu;
	}

	m_fuelText.setFont(m_font);
	m_fuelText.setCharacterSize(30);
	m_fuelText.setString("Fuel : " + std::to_string(m_fuel));
	m_fuelText.setFillColor(sf::Color::White);
	m_fuelText.setPosition(600.0f, 10.0f);

	m_escape = false;
}

void Player::loadContent()
{

	if (!m_playerTexture.loadFromFile("ASSETS/IMAGES/PlayerShip.png"))
	{
		std::cout << "COULD NOT LOAD PLAYER TEXTURE" << std::endl;
	}
	m_playerSprite.setTexture(m_playerTexture);
	m_position = sf::Vector2f(300, 400);
	m_playerSprite.setOrigin(m_radius, m_radius);
	m_playerSprite.setPosition(300, 400);
	m_rotaionValue = 0;

	
}

void Player::checkBounds()
{
	if (playerMoving == true)
	{
		////left wall
		//if (m_playerSprite.getPosition().x < m_radius)
		//{
		//	m_playerSprite.setPosition(800, m_playerSprite.getPosition().y);
		//}
		////right wall
		//if (m_playerSprite.getPosition().x > 800-m_radius)
		//{
		//	m_playerSprite.setPosition(m_radius , m_playerSprite.getPosition().y);
		//}
		////top wall
		//if (m_playerSprite.getPosition().y < m_radius)
		//{
		//	m_playerSprite.setPosition(m_playerSprite.getPosition().x, 600);
		//}
		////bottom wall
		//if (m_playerSprite.getPosition().y >600-m_radius)
		//{
		//	m_playerSprite.setPosition(m_playerSprite.getPosition().x, m_radius);
		//}

	}
}

void Player::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_playerSprite);
	t_window.draw(m_fuelText);
}
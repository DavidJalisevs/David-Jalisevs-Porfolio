
#include "Upgrades.h"
#include "Game.h"
#include <iostream>


/// <summary>
/// Author Dawid Jerdonek
/// Date 29/04/2020
/// 
/// </summary>

Upgrades::Upgrades()
{
}

Upgrades::~Upgrades()
{
}

/// <summary>
/// Load the sprites and text for the Upgrades
/// </summary>
/// <param name="t_font"></param>
void Upgrades::displayUpgrades(sf::Font& t_font)
{
	m_buttonWidth = 50;
	m_betweenText = 100;
	m_betweenPluses = 200;
	m_topOffset = 50;
	m_topLeft = (WIDTH - m_buttonWidth) / 2;
	m_top = (WIDTH - m_buttonWidth) / 1.5;

	int textDropOffset = 10;

	sf::String m_menuTexts[] = { "Laser flight speed", "Current Level : " + std::to_string(m_laserLevel),"Ship speed", "Current Level : " + std::to_string(m_speedLevel),"Fuel Capacity", "Current Level : " + std::to_string(m_fuelLevel) };

	m_font = t_font;

	if (!m_buttonTexture.loadFromFile("ASSETS/IMAGES/WhitePlus.png"))
	{
		std::cout << "error with button file";
	}

	
	for (int i = 0; i < m_lineCount; i++)
	{
		m_upgradeText[i].setFont(m_font);
		m_upgradeText[i].setString(m_menuTexts[i]); //Set an array of strings
		m_upgradeText[i].setFillColor(sf::Color::White);
		m_upgradeText[i].setCharacterSize(24);
		sf::FloatRect textSize = m_upgradeText[i].getGlobalBounds();
		float textOffset = (m_buttonWidth - textSize.width) / 2;
		m_upgradeText[i].setPosition(m_topLeft + textOffset, m_betweenText * i + m_topOffset + textDropOffset);

	}

	for (int i = 0; i < m_upgradeCount; i++)
	{
		m_plusSprites[i].setTexture(m_buttonTexture);
		sf::Vector2u textureSize = m_buttonTexture.getSize();
		m_plusSprites[i].setScale(m_buttonWidth / textureSize.x, m_buttonWidth / textureSize.y);
		m_plusSprites[i].setPosition(m_top, m_betweenPluses * i + m_topOffset);
	}


	m_cost.setFont(m_font);
	m_cost.setCharacterSize(24);
	m_cost.setString("Each level \nOf each upgrade \nCosts 10 Crystals");
	m_cost.setFillColor(sf::Color::Red);
	m_cost.setPosition(10.0f , 10.0f);

	m_current.setFont(m_font);
	m_current.setCharacterSize(24);
	m_current.setString("You Currently have \n" + std::to_string(m_speedLevel) + " Crystals");
	m_current.setFillColor(sf::Color::Blue);
	m_current.setPosition(10.0f, 150.0f);
}

/// <summary>
/// Render the text and sprites
/// </summary>
/// <param name="t_window"></param>
void Upgrades::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_lineCount; i++)
	{
		t_window.draw(m_upgradeText[i]);
	}

	for (int i = 0; i < m_upgradeCount; i++)
	{
		t_window.draw(m_plusSprites[i]);
	}
	
	t_window.draw(m_cost); 
	t_window.draw(m_current);
}

/// <summary>
/// If the player clicks Escape go back
/// </summary>
/// <param name="t_deltaTime"></param>
void Upgrades::update(sf::Time t_deltaTime)
{
	if (m_escape == true)
	{
		Game::myGameState = GameState::PlayMenu;
	}
	m_escape = false;
}

/// <summary>
/// Process if player clicks Escape
/// </summary>
/// <param name="t_event"></param>
void Upgrades::processInput(sf::Event t_event)
{
	if (sf::Event::KeyPressed == t_event.type)
	{
		if (sf::Keyboard::Escape == t_event.key.code)
		{
			m_escape = true;
		}
	}
}

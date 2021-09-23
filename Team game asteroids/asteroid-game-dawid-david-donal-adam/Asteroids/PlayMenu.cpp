
#include "PlayMenu.h"
#include "Game.h"
#include <iostream>

/// <summary>
/// Author Dawid Jerdonek
/// Date 29/04/2020
/// 2 hours
/// </summary>
 
PlayMenu::PlayMenu()
{
}

PlayMenu::~PlayMenu()
{
}

/// <summary>
/// Load the menus text and buttons
/// </summary>
/// <param name="t_font"></param>
void PlayMenu::displayPlayMenu(sf::Font& t_font)
{
	m_buttonWidth = 50;
	m_buttonLength = 200;
	m_betweenButtons = 200;
	m_topOffset = 50;
	m_topLeft = (WIDTH - m_buttonWidth) / 2; 
	m_top = ((WIDTH - m_buttonWidth) / 2) - 75;

	int textDropOffset = 10;

	sf::String m_menuTexts[] = { "Map","Upgrades","Return" };

	m_font = t_font;
	if (!m_buttonTexture.loadFromFile("ASSETS/IMAGES/button.png"))
	{
		std::cout << "error with button file";
	}

	for (int i = 0; i < m_buttonCount; i++)
	{
		m_buttonSprites[i].setTexture(m_buttonTexture);
		sf::Vector2u textureSize = m_buttonTexture.getSize();
		m_buttonSprites[i].setScale(m_buttonLength / textureSize.x, m_buttonWidth / textureSize.y);
		m_buttonSprites[i].setPosition(m_top, m_betweenButtons * i + m_topOffset);

		m_buttonText[i].setFont(m_font);
		m_buttonText[i].setString(m_menuTexts[i]);//Set an array of strings
		m_buttonText[i].setFillColor(sf::Color::White);
		m_buttonText[i].setCharacterSize(24);
		sf::FloatRect textSize = m_buttonText[i].getGlobalBounds();
		float textOffset = (m_buttonWidth - textSize.width) / 2;
		m_buttonText[i].setPosition(m_topLeft + textOffset, m_betweenButtons * i + m_topOffset + textDropOffset);
	}

}

/// <summary>
/// Render text and buttons
/// </summary>
/// <param name="t_window"></param>
void PlayMenu::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_buttonCount; i++)
	{
		t_window.draw(m_buttonSprites[i]);
		t_window.draw(m_buttonText[i]);
	}
}

/// <summary>
/// Do actions depending on what the plaer does
/// </summary>
/// <param name="t_deltaTime"></param>
void PlayMenu::update(sf::Time t_deltaTime)
{
	if (m_escape == true)
	{
		Game::myGameState = GameState::MainMenu;
	}
	if (m_map == true)
	{
		Game::myGameState = GameState::Map;
	}
	if (m_upgrades == true)
	{
		Game::myGameState = GameState::Upgrades;
	}
	m_escape = false;
	m_map = false;
	m_upgrades = false;

}

/// <summary>
/// Process if player clicks mouse or presses escape
/// </summary>
/// <param name="t_event"></param>
/// <param name="t_window"></param>
void PlayMenu::processInput(sf::Event t_event, sf::Window& t_window)
{
	if (sf::Event::KeyPressed == t_event.type)
	{
		if (sf::Keyboard::Escape == t_event.key.code)
		{
			m_escape = true;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mouseLocation;
		mouseLocation = sf::Mouse::getPosition(t_window);

		if (mouseLocation.x > m_top&& mouseLocation.x < m_top + m_buttonLength)
		{
			if (mouseLocation.y > m_topOffset&& mouseLocation.y&& mouseLocation.y < m_topOffset + m_buttonWidth)
			{
				Game::myGameState = GameState::Map;
			}

			if (mouseLocation.y > m_topOffset + m_betweenButtons && mouseLocation.y < m_topOffset + m_betweenButtons + m_buttonWidth)
			{
				Game::myGameState = GameState::Upgrades;

			}

			if (mouseLocation.y > m_topOffset + m_betweenButtons * 2 && mouseLocation.y < m_topOffset + m_betweenButtons * 2 + m_buttonWidth)
			{
				Game::myGameState = GameState::MainMenu;
			}
		}
	}
}


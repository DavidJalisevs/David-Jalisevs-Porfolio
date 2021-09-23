
#include "HelpPage.h"
#include "Game.h"
#include <iostream>

/// <summary>
/// author David Jalisevs
/// date 01/04/2020
/// took me about 1 hour
/// Dawid Jerdonek - Fixed problem with exiting to menu 03/04/2020
/// </summary>
HelpPage::HelpPage() 
{
}


HelpPage::~HelpPage()
{
}

void HelpPage::displayHelp(sf::Font& t_font)
{
	m_font = t_font;

	m_help.setFont(m_font);
	m_help.setCharacterSize(30);
	m_help.setString("In map press 1 to play game \nUse Space Bar to shoot \nUse the arrow keys to move the ship \nLeft = Left arrow key \nRight = Right arrow key \nUp = Up arrow key \nDown = Down arrow key");
	m_help.setFillColor(sf::Color::Red);
	m_help.setPosition(200.0f, HEIGHT - 400.0f);

}

void HelpPage::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_help);
}

void HelpPage::update(sf::Time t_deltaTime)
{
	if (m_escape == true)
	{
		Game::myGameState = GameState::MainMenu;
	}
	m_escape = false;
}

void HelpPage::processInput(sf::Event t_event)
{
	if (sf::Event::KeyPressed == t_event.type)
	{
		if (sf::Keyboard::Escape == t_event.key.code)
		{
			m_escape = true;
		}
	}
}





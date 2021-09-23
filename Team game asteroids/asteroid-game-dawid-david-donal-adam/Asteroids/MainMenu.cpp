
#include <iostream> 
#include "MainMenu.h"
#include "Game.h"


/// <summary>
/// @author David Jalisevs
/// date 01/04/2020
/// took me 2 hours to make it work
/// 
/// </summary>

MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}


void MainMenu::render(sf::RenderWindow& t_window) // draw menu text buttons 
{
	for (int i = 0; i < m_menuOptions; i++)
	{
		t_window.draw(m_buttonSprites[i]);
		t_window.draw(m_buttonText[i]);
	}
}

void MainMenu::initialise(sf::Font& t_font) // initialising variables 
{
	m_topOffset = 50;
	m_verticalSpacing = 100;
	m_buttonWidth = 200;
	m_leftTopOffset = (800 - m_buttonWidth) / 2;      //(Game::s_screenWidth - m_buttonWidth)/2; after game is merged as its not here yet
	m_buttonHeigth = 50;
	int textDropOffset = 10;
	sf::String m_menuTexts[] = { "Play","Help","Exit" };

	m_font = t_font;
	if (!m_buttonTexture.loadFromFile("ASSETS/IMAGES/button.png"))
	{
		std::cout << "error with button file";
	}

	for (int i = 0; i < m_menuOptions; i++)
	{
		m_buttonSprites[i].setTexture(m_buttonTexture);
		m_buttonSprites[i].setPosition(m_leftTopOffset, m_verticalSpacing * i + m_topOffset);
		sf::Vector2u textureSize = m_buttonTexture.getSize();
		m_buttonSprites[i].setScale(m_buttonWidth / textureSize.x, m_buttonHeigth / textureSize.y);

		m_buttonText[i].setFont(m_font);
		m_buttonText[i].setString(m_menuTexts[i]);
		m_buttonText[i].setFillColor(sf::Color::White);
		m_buttonText[i].setCharacterSize(24);
		sf::FloatRect textSize = m_buttonText[i].getGlobalBounds();
		float textOffset = (m_buttonWidth - textSize.width) / 2;
		m_buttonText[i].setPosition(m_leftTopOffset + textOffset, m_verticalSpacing* i + m_topOffset + textDropOffset);
	}
}


void MainMenu::update(sf::Time t_deltaTime, sf::Window& t_window) // updating 
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mouseLocation;
		mouseLocation = sf::Mouse::getPosition(t_window);
		
		if (mouseLocation.x > m_leftTopOffset && mouseLocation.x < m_leftTopOffset + m_buttonWidth)
		{
			if (mouseLocation.y > m_topOffset && mouseLocation.y && mouseLocation.y < m_topOffset + m_buttonHeigth)
			{
				Game::myGameState = GameState::PlayMenu;
			}

			if (mouseLocation.y > m_topOffset + m_verticalSpacing && mouseLocation.y < m_topOffset + m_verticalSpacing + m_buttonHeigth)
			{
				Game::myGameState = GameState::HelpScreen;

			}

			if (mouseLocation.y > m_topOffset + m_verticalSpacing * 2 && mouseLocation.y < m_topOffset + m_verticalSpacing * 2 + m_buttonHeigth)
			{
				t_window.close();
			}
		}
	}
}


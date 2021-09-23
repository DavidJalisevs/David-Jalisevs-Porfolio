#include "Map.h"
#include "Game.h"
#include <iostream>

/// <summary>
/// author Dawid Jerdonek
/// date 03/04/2020
/// Time : 1 hour
/// IMPORTANT USE 1 ON MAP SCREEN TO PLAY
/// </summary>
Map::Map()
{
}

Map::~Map()
{
}

/// <summary>
/// Load the map sprite
/// </summary>
/// <param name="t_window"></param>
void Map::displayMap(sf::RenderWindow& t_window)
{

	{
		if (!m_mapTexture.loadFromFile("ASSETS\\IMAGES\\Solar Map.jpg"))
		{
			// simple error message if previous call fails
			std::cout << "problem loading background" << std::endl;
		}
		m_mapSprite.setTexture(m_mapTexture);

	}
	t_window.draw(m_mapSprite);
}

/// <summary>
/// Render map
/// </summary>
/// <param name="t_window"></param>
void Map::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_mapSprite);
}

/// <summary>
/// Update based on enemy actions
/// </summary>
/// <param name="t_deltaTime"></param>
void Map::update(sf::Time t_deltaTime)
{
	
	if (m_escape == true)
	{
		Game::myGameState = GameState::PlayMenu;
	}
	if (m_gameplay == true)
	{
		Game::myGameState = GameState::GamePlay;
	}
	m_escape = false;
	m_gameplay = false;
}

/// <summary>
/// Process the enemy inputs
/// </summary>
/// <param name="t_event"></param>
void Map::processInput(sf::Event t_event)
{
	if (sf::Event::KeyPressed == t_event.type)
	{
		if (sf::Keyboard::Num1 == t_event.key.code)
		{
			m_gameplay = true;
		}
		if (sf::Keyboard::Escape == t_event.key.code)
		{
			m_escape = true;
		}
	}
}

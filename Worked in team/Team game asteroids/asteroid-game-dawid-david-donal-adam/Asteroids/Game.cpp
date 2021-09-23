
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-main-d.lib")
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-main.lib")
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "MyVector2.h"


/// <summary>
/// IMPORTANT!
/// WHILE ON MAP SCREEN PRESS number one ( 1 ) on keyboard to go into gameplay
/// </summary>



int main()
{ 
	Game game; 
	 
	game.run(); 
}


GameState Game::myGameState = GameState::MainMenu;

/// <summary>
/// 
/// </summary>

Game::Game() : m_window(sf::VideoMode{ 800U,600U,32U }, "Asteroids", sf::Style::Default)


{		
	LoadContent();
	m_playerOne.loadContent();
	m_TheCrystal.loadContent(m_arialFont);
	backGround();

}

/// <summary>
/// @brief main game loop.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{		
			timeSinceLastUpdate -= timePerFrame;

			processEvents();
			update(timePerFrame);		
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}

		switch (myGameState) 
		{
		case GameState::HelpScreen:
			m_helpScreen.processInput(event);
			break;
		case GameState::PlayMenu:
			m_secondMenu.processInput(event, m_window);
			break;
		case GameState::Upgrades:
			m_upgradeScreen.processInput(event);
			break;
		case GameState::Map:
			m_map.processInput(event);
		default:
			break;
		}
	}
}

void Game::update(sf::Time time)
{

	switch (myGameState)
	{
	
		case GameState::MainMenu:
			m_mainMenu.update(time, m_window);
			break;
		case GameState::HelpScreen:
			m_helpScreen.update(time);
			break;
		case GameState::PlayMenu:
			m_secondMenu.update(time);
			break;
		case GameState::Upgrades:
			m_upgradeScreen.update(time);
			break;
		case GameState::Map:
			m_map.update(time);
			break;
		case GameState::GamePlay:
			m_gameplay.update(time);
			m_playerOne.movement(m_arialFont);
			m_asteroid.asteroidMovement();
			m_enemy.determineMove();
			m_playerOne.checkBounds();
			collisionDetection();
			m_playerBullet.bulletFired(m_playerOne.m_playerSprite.getPosition());
			m_playerBullet.bulletDirection();
			m_asteroid.asteroidCollisionBullet(m_playerBullet.m_SpriteBullet.getGlobalBounds());
			m_TheCrystal.getCrystalPos(m_asteroid.m_asteroidSprite.getPosition(), crystalSpawn);
		

		default:
			break;
	}
	
}

void Game::render()
{
	m_window.clear();


	switch (myGameState)
	{
	case GameState::MainMenu:
		m_window.draw(m_menuBacksprite);

		m_mainMenu.render(m_window);
		break;
	case GameState::HelpScreen:
		m_helpScreen.render(m_window);
		break;
	case GameState::PlayMenu:
		m_window.draw(m_secMenuBacksprite);

		m_secondMenu.render(m_window);
		break;
	case GameState::Upgrades:
		m_upgradeScreen.render(m_window);
		break;
	case GameState::Map:
		m_map.render(m_window);
		break;
	case GameState::GamePlay:
		m_gameplay.render(m_window);
		/*gameplayLevel = true;*/
		if (playerAlive == true)
		{
			m_window.draw(m_backsprite);

			m_playerOne.draw(m_window);

			m_asteroid.drawAsteroid(m_window);
			
			if (m_playerBullet.m_bulletCollided == false)
			{
				m_playerBullet.drawBullet(m_window);
			}
			if (m_enemyDestroyed == false)
			{
				m_enemy.drawEnemy(m_window);
			}
			
				m_TheCrystal.render(m_window);
			

		}
		else
		{
			m_window.draw(m_lossText);
		}
		resetGame();
		
	default:
		break;
	}
	/*if (gameplayLevel==true)
	{
		
	}*/
	m_window.display();
}

/// <summary>
/// function for loading font and content for application
/// </summary>
void Game::LoadContent() 
{
	if (!m_arialFont.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "problem loading splashcreen font" << std::endl;
	}
	m_helpScreen.displayHelp(m_arialFont);
	m_map.displayMap(m_window);
	m_mainMenu.initialise(m_arialFont);
	m_secondMenu.displayPlayMenu(m_arialFont);

}

void Game::backGround()
{
	if (!m_backgrounds.loadFromFile("ASSETS\\IMAGES\\space.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading background" << std::endl;
	}
	m_backsprite.setTexture(m_backgrounds);
	m_backsprite.setOrigin(sf::Vector2f{ 1.0f,1.0f });
	//m_backsprite.setScale(sf::Vector2f{ -.22f, -.22f });


	if (!m_menuBackgrounds.loadFromFile("ASSETS\\IMAGES\\menuBack.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading background" << std::endl;
	}
	m_menuBacksprite.setTexture(m_menuBackgrounds);
	m_menuBacksprite.setOrigin(sf::Vector2f{ 1.0f,1.0f });
	m_menuBacksprite.setScale(sf::Vector2f{ 1.4f,1.4f });


	if (!m_secMenuBack.loadFromFile("ASSETS\\IMAGES\\spacewars.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading background" << std::endl;
	}
	m_secMenuBacksprite.setTexture(m_secMenuBack);
	m_secMenuBacksprite.setOrigin(sf::Vector2f{ 1.0f,1.0f });
	m_secMenuBacksprite.setScale(sf::Vector2f{ 0.8f,0.83f });

	m_upgradeScreen.displayUpgrades(m_arialFont);

}

void Game::collisionDetection()
{
	if (m_playerOne.m_playerSprite.getGlobalBounds().intersects(m_asteroid.m_asteroidSprite.getGlobalBounds()))
	{
		playerAlive = false;
		losingText();
	}
	if (m_playerOne.m_playerSprite.getGlobalBounds().intersects(m_enemy.m_enemySprite.getGlobalBounds()))
	{
		playerAlive = false;
		losingText();
	}

	if (m_playerBullet.m_SpriteBullet.getGlobalBounds().intersects(m_asteroid.m_asteroidSprite.getGlobalBounds()))
	{
		asteroidEnemyControl = true;
		m_playerBullet.m_bulletCollided = true;
		m_TheCrystal.asteroidDestroyed = true;
		crystalSpawn=m_asteroid.m_asteroidSprite.getPosition();


	}
	if (m_playerBullet.m_SpriteBullet.getGlobalBounds().intersects(m_enemy.m_enemySprite.getGlobalBounds()))
	{
	
		m_playerBullet.m_bulletCollided = true;
		m_enemyDestroyed = true;
	}
	if (m_playerOne.m_playerSprite.getGlobalBounds().intersects(m_TheCrystal.m_CrystalSprite.getGlobalBounds()))
	{
		m_TheCrystal.crystalHasBeenCollected = true;
		
		m_playerOne.m_fuel = 200;
	}


}

void Game::losingText()
{
		m_lossText.setFont(m_arialFont);
		m_lossText.setCharacterSize(40);
		m_lossText.setString("YOU HAVE LOST TRY AGAIN PRESS R TO RESTART");
		m_lossText.setPosition(100.0f, 200.0f);
	
}

void Game::resetGame()
{
	if (playerAlive == false && sf::Keyboard::isKeyPressed(sf::Keyboard::R))// to reset the game and bools
	{
		playerAlive = true;
		m_enemyDestroyed = false;
		m_playerOne.m_fuel = 200;

	}
}


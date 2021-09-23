#ifndef GAME_H
#define GAME_H


#include <iostream>
#include "HelpPage.h"
#include"MainMenu.h"
#include "GAMEPLAY.h"
#include "PLAYER.h"
#include "Asteroid.h"
#include "Map.h"
#include "Enemy.h"
#include "PlayMenu.h"
#include "Upgrades.h"
#include "BulletPlayer.h"
#include "CRYSTALS.h"


enum class GameState
{
	None,
	MainMenu,
	HelpScreen,
	GamePlay,
	Map,
	Upgrades,
	PlayMenu
};


/// <summary>
/// @author David Jalisevs, Dawid Jerdonek,Donal Howe
/// @date 01/04/2020, 02/04/2020, 03/04/2020
/// @brief main game class conatins main and run game loop.
/// </summary>
/// /// <summary>
/// IMPORTANT!
/// WHILE ON MAP SCREEN PRESS number one ( 1 ) on keyboard to go into gameplay
/// </summary>

class Game
{
public:
	Game();
	void run();
	
	static GameState myGameState;
	bool gameplayLevel = false;
	bool playerAlive = true;
	float bulletRot = 0.0f;
	sf::Vector2f crystalSpawn;
protected:
	bool m_crystalSpawned = false;
	void	processEvents();
	void	update(sf::Time);
	void	render();
	void LoadContent();
	void collisionDetection();
	void losingText();
	void resetGame();
	void backGround();

	bool asteroidEnemyControl = false; // so when the bullet hits regular enemy it respawns smart enemy in smartEnemy.cpp


	bool m_enemyDestroyed = false;

	
	sf::Font m_arialFont;
	sf::Font m_lossFont;
	sf::Text m_lossText;

	sf::Texture m_backgrounds; // background texture
	sf::Sprite m_backsprite; // background sprtire

	sf::Texture m_menuBackgrounds; // background texture
	sf::Sprite m_menuBacksprite; // background sprtire

	sf::Texture m_secMenuBack; // background texture
	sf::Sprite m_secMenuBacksprite; // background sprtire

	MainMenu m_mainMenu;
	HelpPage m_helpScreen;
	GamePlay m_gameplay;
	Map m_map;
	Player m_playerOne;
	Bullet m_playerBullet;
	Asteroid m_asteroid;
	Enemy m_enemy;
	PlayMenu m_secondMenu;
	Upgrades m_upgradeScreen;
	CRYSTALS m_TheCrystal;


	sf::RenderWindow m_window;
};
#endif // !GAME_H
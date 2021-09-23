#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Asteroid.h"
//@author Donal Howe
class CRYSTALS
{
	sf::Texture m_crystaltexture;
	sf::Font m_font;
	sf::Text CrystText;
;
public:
	bool crystalHasBeenCollected = false;
	sf::Sprite m_CrystalSprite;
	bool deleteCrystal = false;
	sf::Text m_CrystalText;
	bool asteroidDestroyed = false;
	void render(sf::RenderWindow &t_window);
	void  loadContent(sf::Font &t_font);
	void update();
	void getCrystalPos(sf::Vector2f t_asteroidPos, sf::Vector2f t_crystalSpawn);
	void setupText();
	int crystalsCollected = 0;
};


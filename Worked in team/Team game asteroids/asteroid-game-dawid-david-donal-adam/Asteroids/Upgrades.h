#ifndef UPGRADES_H
#define UPGRADES_H

#include <SFML\Graphics.hpp>

/// <summary>
/// @author Dawid Jerdonek
/// @date 29/04/2020
/// 
/// 
/// </summary>
class Upgrades
{
public:
	Upgrades();
	~Upgrades();

	void displayUpgrades(sf::Font& t_font); //Load the sprites and text for the Upgrades
	void render(sf::RenderWindow& t_window); //Render the text and sprites
	void update(sf::Time t_deltaTime); //If the player clicks Escape go back
	void processInput(sf::Event t_event); //Process if player clicks Escape



protected:

	static const int m_lineCount = 6; //Each upgrade counts as two lines to display current level
	static const int m_upgradeCount = 3; //Number of upgrades

	const int WIDTH = 800;
	const int HEIGHT = 600;

	int m_speedLevel = 1;
	int m_laserLevel = 1;
	int m_fuelLevel = 1;

	float m_buttonWidth = 0.0f;
	float m_betweenText = 0.0f;
	float m_topOffset = 0.0f;
	float m_topLeft = 0.0f;
	float m_top = 0.0f;
	float m_betweenPluses = 0.0f;

	bool m_escape = false;

	sf::Texture m_buttonTexture; //Texture for plus
	sf::Sprite m_plusSprites[m_upgradeCount]; //Array of plus sprites

	sf::Font m_font;
	sf::Text m_upgradeText[m_lineCount]; //Text to appear in the buttons
	sf::Text m_cost; //Cost of each crystal
	sf::Text m_current; //Current number of crystals
};

#endif // !UPGRADES_H



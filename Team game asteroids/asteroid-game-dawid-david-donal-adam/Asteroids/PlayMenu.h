#ifndef PLAYMENU_H
#define PLAYMENU_H

#include <SFML\Graphics.hpp>

/// <summary>
/// @author Dawid Jerdonek
/// @date 29/04/2020
/// 2 hours to complete fully
/// 
/// </summary>
class PlayMenu
{
public:
	PlayMenu();
	~PlayMenu();


	void displayPlayMenu(sf::Font& t_font); // Load the menus text and buttons
	void render(sf::RenderWindow& t_window); // Render text and buttons
	void update(sf::Time t_deltaTime); // Do actions depending on what the plaer does
	void processInput(sf::Event t_event, sf::Window& t_window); // Process if player clicks mouse or presses escape



private:

	static const int m_buttonCount = 3;

	const int WIDTH = 800;
	const int HEIGHT = 600;

	float m_buttonWidth = 0.0f;
	float m_buttonLength = 0.0f;
	float m_betweenButtons = 0.0f;
	float m_topOffset = 0.0f;
	float m_topLeft = 0.0f;
	float m_top = 0.0f;

	bool m_escape = false; //Change gamestate to previous
	bool m_map = false; //Change gamestate to the Map
	bool m_upgrades = false; //Change gamestate to Upgrades

	sf::Texture m_buttonTexture; //Texture for buttons
	sf::Sprite m_buttonSprites[m_buttonCount]; //Array of button sprites

	sf::Font m_font;
	sf::Text m_buttonText[m_buttonCount]; //Text to appear in the buttons

};

#endif // !PLAYMENU_H


#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML\Graphics.hpp>

/// <summary>
/// @author David Jalisevs
/// @date 01/04/2020
/// 
///  class to handle simple menu interaction
/// </summary>
class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void initialise(sf::Font& t_font);
	void render(sf::RenderWindow& t_window);
	void update(sf::Time t_deltaTime, sf::Window& t_window);
	

protected:
	
	static const int m_menuOptions{ 3 }; // number of buttons in the menu 
	sf::Texture m_buttonTexture; // texture backround for buttons
	sf::Sprite m_buttonSprites[m_menuOptions]; // array of the option buttons
	sf::Font m_font; // reference to the font usent in the whole project
	sf::Text m_buttonText[m_menuOptions]; // button texts

	float m_topOffset{ 0.0f }; // top area used for menu
	float m_leftTopOffset{ 0.0f }; // top left area used for menu
	float m_verticalSpacing{ 0.0f }; // gap in the pixels between tops 
	float m_buttonHeigth{ 0.0f }; // heigth of the buttons
	float m_buttonWidth{ 0.0f }; // width of the buttons 


	float m_screenWidth{ 600.0f }; // temp TO HOLD SCREEN WIDTH WHILE GAME IS NOT MERGED
	
};

#endif // !MAINMENU_H
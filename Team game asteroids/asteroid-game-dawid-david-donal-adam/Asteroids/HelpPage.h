#ifndef HELPPAGE_H
#define HELPPAGE_H

#include <SFML\Graphics.hpp>

/// <summary>
/// @author David Jalisevs
/// @date 01/04/2020
/// 
/// 
/// </summary>
class HelpPage
{
public:
	HelpPage();
	~HelpPage();


	void displayHelp(sf::Font& t_font);
	void render(sf::RenderWindow& t_window);
	void update(sf::Time t_deltaTime);
	void processInput(sf::Event t_event);


	
protected:
	
	const int WIDTH = 800;
	const int HEIGHT = 600;

	bool m_escape = false;


	sf::Font m_font;
	sf::Text m_help;
	

};

#endif // !HELPPAGE_H

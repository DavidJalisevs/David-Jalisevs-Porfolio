#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics.hpp>

/// <summary>
/// @author Dawid Jerdonek
/// @date 03/04/2020
/// 
/// 
/// </summary>
class Map
{
public:
	Map();
	~Map();


	void displayMap(sf::RenderWindow& t_window);
	void render(sf::RenderWindow& t_window);
	void update(sf::Time t_deltaTime);
	void processInput(sf::Event t_event);

	sf::Texture m_mapTexture;


private:

	const int WIDTH = 800;
	const int HEIGHT = 600;

	bool m_escape = false; //Go back
	bool m_gameplay = false; //Move to gameplay

	sf::Sprite m_mapSprite;

	sf::Font m_font;
	sf::Text m_help;
};

#endif // !HELPPAGE_H
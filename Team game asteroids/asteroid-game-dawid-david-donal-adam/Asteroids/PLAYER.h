#ifndef PLAYER_H
#define PLAYER_H

//author: donal Howe
#include <SFML\Graphics.hpp>

class Player
{
	sf::Texture m_playerTexture;
	int health = 0;

public:
	Player();
	~Player();
	sf::Sprite m_playerSprite;

	void draw(sf::RenderWindow& t_window);// draw the playersprite
	void movement(sf::Font& t_font);// to do the player movement
	void loadContent();//load the player texture
	void checkBounds();

	bool m_escape = false;
	float m_rotaionValue;
	int m_fuel = 0;
protected:
	float thrustValue = 0;
	bool playerMoving = false;
	int speedValue = 5;
	
	sf::Vector2f m_position;
	float m_angle;
	int m_radius = 25;
	

	//Dawid Jerdonek
	
	sf::Font m_font;
	sf::Text m_fuelText;

	

};
#endif // !PLAYER_H


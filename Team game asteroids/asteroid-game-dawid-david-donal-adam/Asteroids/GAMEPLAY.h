#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML\Graphics.hpp>
#include "Player.h"


class GamePlay
{
public:
	GamePlay();
	~GamePlay();	
	

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);
protected:
	
	void collisionDetetcion();
	
};

#endif // !GAMEPLAY_H

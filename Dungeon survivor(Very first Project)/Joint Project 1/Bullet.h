#pragma once
#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function
#include "Globals.h"
#include <SFML/Audio.hpp>


class Bullet
{
	sf::Texture bulletTexture;

	float m_bulletSpeed{ 15.0f }; // bullet speed
	bool m_bulletShot = false; // if bullet shot
	bool m_bulletShow = false; // to show bullet 
	sf::FloatRect bulletPos;

	bool m_bulletShotRight = false; // cheks for if when bullet goes right 
	bool m_bulletShotLeft = false; // checks when if bullet goes left
	bool m_bulletShotDown = true; // checks for when bullet goes down
	bool m_bulletShotUp = false; // checks when bullet goes up
	bool m_bulletIsMoving = false; // checks if bullet is moving 

	sf::SoundBuffer m_shootBuffer; // sound 
	sf::Sound m_shootSound;


public:
	sf::Sprite bulletSprite; // sprite of the bullet

	void drawBullet(sf::RenderWindow& t_window); // draws bullet 
	void setBulletBody(sf::Vector2f t_playerPos); // sets the body of the bulelt
	void bulletFired(sf::Vector2f t_playerPos); // makes bullet move
	void bulletBoundary(sf::Vector2f t_playerPos, bool &t_regControl, bool &t_smartControl); // checks bullets boundary
	void bulletDirection(); // checks either bullet goes right left up or down
	void setSound(); // sets the sound for the bullet shot 
};


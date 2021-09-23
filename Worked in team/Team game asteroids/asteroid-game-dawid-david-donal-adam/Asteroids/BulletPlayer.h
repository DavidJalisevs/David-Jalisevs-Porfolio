#pragma once
#pragma once
#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function
#include <SFML/Audio.hpp>

/// <summary>
/// Author DAVID JALISEVS
/// </summary>

class Bullet
{
	sf::Texture bulletTexture;


	float m_bulletSpeed{ 15.0f }; // bullet speed
	bool m_bulletShot = false; // if bullet shot
	bool m_bulletShow = false; // to show bullet 
	sf::FloatRect bulletPos;

	bool m_bulletShotUp = false; // checks when bullet goes up
	bool m_bulletIsMoving = false; // checks if bullet is moving 

	sf::SoundBuffer m_shootBuffer; // sound 
	sf::Sound m_shootSound;

	


	float m_rotaionValueBullet = 1.0f;
	sf::Vector2f m_positionBullet;
	float m_angleBullet;

public:


	Bullet();
	~Bullet();

	bool m_bulletCollided = false;
	//sf::Sprite m_bulletSprite; // sprite of the bullet
	sf::Sprite m_SpriteBullet; //sprite of the bullet

	void drawBullet(sf::RenderWindow& t_window); // draws bullet 
	void setBulletBody(sf::Vector2f t_playerPos); // sets the body of the bulelt
	void bulletFired(sf::Vector2f t_playerPos); // makes bullet move
	void bulletDirection(); // checks either bullet goes right left up or down
};
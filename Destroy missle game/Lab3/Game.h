/// <summary>
/// author David Jalisevs
/// ID - c00239534
/// Date November 2019
/// ALL INSTRUCTIONS IN main.cpp 
/// ALL SESSIONS int the main.cpp
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// 
/// project comment in main.cpp
/// </summary>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:


	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void processMouseReleaseEvents(sf::Event t_mouseEvent);

	void setUpGameTexts(); // texts for the game such as game over and score
	void background(); // background image
	void groundSprite(); // fun ground
	void groundBasicSprite(); // not fun ground
	void baseSprite(); // fun base
	void baseBasicSprite(); // BASIC sprite for the base
	void laserVelocity(); // calculations of the laser velocity
	void meteorVelocity(); // calculations of the meteor velocity same formula kinda
	void basicExplosion(); // basic explosion ( circle ) 
	void superExplosion(); // explosion with a proper sprite
	void setupSounds(); // sounds for the game. death sound and background sound etc.
	void linesLaser(); // lines of the laser
	void linesMeteor(); // lines of the meteor
	void lineBetween(); // invisible line between meteor and laser to detect collision
	void playerAlive(); // just a function that holds commands while player is still alive.


	 /// <summary>
	 /// Sound variables and functions
	 /// </summary>
	sf::SoundBuffer m_expBuffer;
	sf::Sound m_expSound;
	sf::SoundBuffer m_missleBuffer;
	sf::Sound m_missleSound;
	sf::SoundBuffer m_deathBuffer;
	sf::Sound m_deathSound;
	sf::SoundBuffer m_groundBuffer;
	sf::Sound m_groundSound;
	sf::SoundBuffer m_themeBuffer;
	sf::Sound m_themeSound;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_gameOverMsg; // text used for message on screen
	sf::Text m_powerBar; // text used for power bard
	sf::Text m_livesLeft; // text user for lives 
	sf::Text m_scoreCount; // score count

	sf::Texture m_backgrounds; // background texture
	sf::Sprite m_backsprite; // background sprite 

	sf::Texture m_groundTexture; // texture used for ground FUN
	sf::Sprite m_groundSprite; // sprite used for ground FUN
	sf::RectangleShape m_basicGround; // not fun ground 


	sf::Texture m_baseTexture; // teture for base fun 
	sf::Sprite m_baseSprite; // sprite for base fun
	sf::Vector2f m_baseOffSet{ 20.0f, 0.0f }; // offset if the base
	sf::RectangleShape m_basicBase; // nor for fun

	sf::CircleShape m_explosionBasicCircle; // circle expanding explosion
	sf::Texture m_funExpTexture; // texture used for ground FUN
	sf::Sprite m_funExpSprite; // sprite explosion
	sf::RectangleShape powerBar; // shape of the power bar


	sf::Vector2f m_laserVelocity; // used for laser velocity
	sf::Vector2f m_meteorVelocity; // used for meteor velocity
	sf::Vector2f laserEnd{ 0.0f,0.0f }; // laser end pont
	sf::Vector2f laserPosition{ 400.0f,560.0f }; // laser start position
	sf::Vector2f laserTempPosition{ 400.0f,560.0f }; // to hold coords of the collision point for the explosion
	sf::Vector2f laserKeepPosition; // same as laserTempPosition but for fun explosion. they need to be different as it wont work with same. 
	sf::VertexArray m_laserLine{ sf::Lines }; // laser draw
	sf::Vector2f meteorStart{ 0.0f,0.0f }; // meteor start
	sf::Vector2f meteorEnding{ 0.0f,0.0f }; // meteor end 
	sf::VertexArray m_meteorLine{ sf::Lines }; // meteor draw
	sf::Vector2f m_laserHeading{ 0.0f, 0.0f }; // heading f0r laser
	sf::Vector2f m_meteorHeading{ 0.0f,0.0f }; // heading but for meteor
	sf::Vector2f m_mouseClick{ 0.0f,0.0f }; // location of mouse click

	sf::Vector2f randomMeteorTop{ 0.0f,0.0f }; // randomg coord for the meteor top
	sf::Vector2f randomMeteorBottom{ 0.0f,600.0f }; // randomg coord for the meteor bottom

	sf::Vector2f distMeteorToLaser{ 0.0f,0.0f }; // distance for invisible line between meteor and laser
	float invisibleLine{ 0.0f };

	float m_lazerSpeed{ 10.0f }; // 10
	float m_meteorSpeed{ 1.0f }; // 2 or 1
	float powerLeft{ 1.0f }; // variable that adds on
	float power{ 50.0f }; // power
	float radiusIncrease{ 0.0f }; // incremetnt for radius
	int livesCount{ 3 }; // mayybe ill + to 5 as game gets harder after 30/ live count
	int scoreCount{ 0 }; // score of the player

	bool m_exitGame; // control exiting game
	bool b_mouseRelease = false; // mouser release check for the laser
	bool b_funTextures = false; // GRAPHICS after you press T
	bool b_laserGoes = false; // laser goes moves
	bool b_circleExpand = false; // circle basic expands
	bool b_meteorGoes = false; // meteor moves
	bool b_funExplosion = false; // GGRAPHICS explosion - still dangerous
	bool b_meteorSpeedIncrement = true; // wgile true it will add up on the speed of the meteor and eventually will stop addding speed to dont make this game impossible after certain speed 

	float m_expFrameIncrement{ 1.05f }; // how fast 
	float m_expFrameCounter{ 1.0f }; // expl
	int m_expFrameV{ 0 }; // explosuinbs frame
	int m_expFrameH{ 0 }; // explosuinbs frame


	int meteorCounter{ 1 }; // counts meteors 
	float meteorTreshold{ 3.0f }; // treshold of after how many it will increase the speed
	float scoreTreshold{ 50.0f }; // treshold for score 

};

#endif // !GAME_HPP
#ifndef GAME_H
#define GAME_H

#include <string>
#include <sstream>
#include <fstream>

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>

#include <Debug.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <GameObject.h>
#include <GameObjectPlayer.h>

using namespace std;
using namespace sf;
using namespace glm;

class Game
{
public:
	Game();
	Game(sf::ContextSettings settings);
	~Game();
	void run();
private:
	GameObject* game_object[40];
	GameObjectPlayer* game_object_player[1];
	sf::RectangleShape recShape;

	RenderWindow window;
	Clock clock;
	Time time;
	bool animate = false;
	vec3 animation = vec3(0.0f);
	float rotation = 0.0f;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();
	void playerMovement();
	void checkCollision();
	float m_playerScore = 0.0f;
	float m_playerBestScore = 0.0f;
	int m_lives = 3;
	int m_playerCurrentPosPositiveX;
	int m_playerCurrentPosNegativeX;
	int m_playerCurrentRealX;
	float m_randomNumber;
	float m_cubeSpeed = 0.01f;
	float m_playerSpeed = 0.014f;
	int m_scoreTreshold = 200;
	bool speedIncrement = true;
	float rotationXPlayer = 0.0f;
	bool pressed = false;
	float backgroundRotation = 0.0f;

	sf::SoundBuffer m_collideBuffer;
	sf::Sound m_collideSound;

	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;
	

	/*sf::SoundBuffer m_backSoundBuffer;
	sf::Sound m_backSound;*/

	sf::Music m_backSound;
	bool started = false;

};

#endif  // ! GAME_H
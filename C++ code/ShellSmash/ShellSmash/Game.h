/// <summary>
/// author - David Jalisevs
/// date - January 2020
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "MyVector3.h"

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


	const int WIDTH{ 800U };
	const int HIGHT{ 600U };
	const float RADIUS{ 16U };
	const float DIAMETERf = RADIUS + RADIUS;
	const float DIAMETER_SQUAREDf = DIAMETERf * DIAMETERf;

	int activeShells{ 7 };
	const static int MAX_SHELLS{ 11 };
	void processEvents();
	void processKeys(sf::Event t_event);
	void processMousePressEvents(sf::Event t_mouseEvent);
	void processMouseReleaseEvents(sf::Event t_mouseEvent);
	void vertexSystem();

	void update(sf::Time t_deltaTime);
	void render();
	

	void setupFontAndText();
	void setupSprite();
	void drawShell(); // draws shell
	void velocity(); // actually moves shell
	void wallCheck(); // checks for the wall bnounds 
	void shellMovement(); // moves shells 
	void changeColor(); // changes the color

	void collisions(); // function for collisions
	bool checkForCollisions(int t_A, int t_B); // checks for collisions
	void processCollision(int t_A, int t_B); // process collisions


	sf::CircleShape m_circle; //creates circle
	MyVector3 m_greenPosition{ 550.0f,290.0f,0.0f }; //postiotion of the ball
	MyVector3 m_shellPositionArray[MAX_SHELLS]; // shell positions 
	MyVector3 m_velocityArray[MAX_SHELLS]; // velocity array
	MyVector3 m_initialVelocity{ 0.0f,0.0f,0.0f }; // intial velocity
	MyVector3 m_mouseClick{ 0.0f,0.0f,0.0f }; // location of the mouse 
	sf::VertexArray m_line{ sf::Lines }; // line from mouse to shell
	MyVector3 m_lineEnd{ 0.0f,0.0f,0.0f }; // laser end pont
	MyVector3 m_lineStart{ 0.0f,0.0f,0.0f }; // laser start pont
	MyVector3 m_tempPositionRed{ 110.0f,290.0f,0.0f }; // TEMP position for RED SHELL FOR NOW   
	MyVector3 m_tempPositionRed1{ 200.0f,290.0f,0.0f }; // TEMP position for RED SHELL FOR NOW   
	MyVector3 m_tempPositionRed2{ 110.0f,350.0f,0.0f }; // TEMP position for RED SHELL FOR NOW   
	MyVector3 m_tempPositionRed3{ 110.0f,230.0f,0.0f }; // TEMP position for RED SHELL FOR NOW   
	MyVector3 m_tempPositionRed4{ 150.0f,320.0f,0.0f }; // TEMP position for RED SHELL FOR NOW   
	MyVector3 m_tempPositionRed5{ 150.0f,260.0f,0.0f }; // TEMP position for RED SHELL FOR NOW   


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo

	int i{ 0 };
	
	bool m_exitGame; // control exiting game

	bool clicked = false; // if mouse is clicked or not 
	bool hasStopped = true; // has the ball stopped or not
	bool mouseRelease = false; // when mouse release
	bool isInitalised = false; // ball is initialised
	bool readyToGo = true; // ready to go after it stopped everything is looped 

	bool shellColoursArray[MAX_SHELLS]; // it sets the array of green or not
	bool colourSetup = false;// checks at the beginning

};

#endif // !GAME_HPP


/// <summary>
/// @author  David Jalisevs
/// @date January 2020
///	INFORMATION ABOUT SESSIONS IN main.cpp
/// 
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	drawShell(); // run
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}

		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMousePressEvents(newEvent); // keep code tidy	
		}

		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseReleaseEvents(newEvent);
		}
	}
}

/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}


void Game::processMousePressEvents(sf::Event t_mouseEvent)
{
	if (isInitalised == false && readyToGo == true)
	{
		if (sf::Mouse::Left == t_mouseEvent.mouseButton.button)
		{
			m_mouseClick = sf::Mouse::getPosition(m_window);
			std::cout << m_mouseClick.toString() << std::endl;
			clicked = true;
			mouseRelease = false;
		}
	}
}

void Game::processMouseReleaseEvents(sf::Event t_mouseEvent)
{
	if (isInitalised == false && readyToGo == true)
	{
		if (sf::Mouse::Left == t_mouseEvent.mouseButton.button)
		{
			m_line.clear();
			std::cout << "Realesed" << std::endl;
			mouseRelease = true;
			hasStopped = false;
			clicked = false;
		}
	}
}


/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	velocity();
	wallCheck();
	vertexSystem();
	collisions();

	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Blue);

	for (i = 0; i < activeShells; i++)
	{


		for (i = 0; i < activeShells; i++)
		{

			changeColor();
			m_circle.setPosition(m_shellPositionArray[i]);
			m_window.draw(m_circle);

		}

		m_window.draw(m_line);
		m_window.display();
	}
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>


/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{

	
}


void Game::setupFontAndText()
{

}

/// <summary>
/// pete
/// </summary>
void Game::drawShell() // draws once 
{	
	m_circle.setRadius(RADIUS);
	m_circle.setOrigin(RADIUS, RADIUS);
	m_circle.setPosition(m_greenPosition);

	m_shellPositionArray[0] = m_greenPosition;
	m_shellPositionArray[1] = m_tempPositionRed;
	m_shellPositionArray[2] = m_tempPositionRed1;
	m_shellPositionArray[3] = m_tempPositionRed2;
	m_shellPositionArray[4] = m_tempPositionRed3;
	m_shellPositionArray[5] = m_tempPositionRed4;
	m_shellPositionArray[6] = m_tempPositionRed5;


	for ( i = 0; i <= MAX_SHELLS - 1; i++)
	{
		//m_shellPositionArray[i] = m_greenPosition * (i + 1);
		m_velocityArray[i] = m_greenPosition * (i) / 9999;
	}
}


/// <summary>
/// 
/// </summary>
void Game::velocity() // velocity of the shells
{
	if (mouseRelease == true && isInitalised == false&& hasStopped == false)
	{
		m_velocityArray[0] = m_mouseClick - m_shellPositionArray[0];
		m_velocityArray[0] = m_velocityArray[0] / 13;//unit() * (velocityArray[0].length() / 12.0f);

		std::cout << "MOVED" << std::endl;


		isInitalised = true;
		readyToGo = false;
	}

	shellMovement();
}


void Game::shellMovement() // moves the shell
{
	for ( i = 0; i <= activeShells; i++) // for loop that moves and stops the shells
	{

		m_velocityArray[i] = m_velocityArray[i] * 0.985f;
		m_shellPositionArray[i] = m_shellPositionArray[i] + m_velocityArray[i];

		if (isInitalised == true ) 
		{
			m_velocityArray[0] = m_velocityArray[0] * 0.997f;
			m_shellPositionArray[0] = m_shellPositionArray[0] + m_velocityArray[0];
		}

		if (m_velocityArray[i].x <= 1.0f && m_velocityArray[i].y <= 1.0f )
		{
			m_velocityArray[i] = m_velocityArray[i] * 0.998f;
		}

		if (m_velocityArray[i].x <= 0.2f && m_velocityArray[i].x >= -0.2f && m_velocityArray[i].y <= 0.2f && m_velocityArray[i].y >= -0.2f)
		{
			m_velocityArray[i] = { 0.0f,0.0f,0.0f };
			isInitalised = false;
			hasStopped = true;
			readyToGo = true;
			
			m_mouseClick = { 0.0f,0.0f,0.0f };
		}
	}
}

void Game::wallCheck() // checks for the walls																			//
{																														//
	for( i = 0; i < activeShells; i++) // for loop that checks for the wall bounds									//
	{																													//        
		if (m_shellPositionArray[i].x <= RADIUS || m_shellPositionArray[i].x >= WIDTH - RADIUS)								//
		{																												//
			m_velocityArray[i].reverseX();																				//
		}																												//
																														//
		if (m_shellPositionArray[i].y <= RADIUS || m_shellPositionArray[i].y >= HIGHT - RADIUS)								//
		{																												//
			m_velocityArray[i].reverseY();																				//
		}																												//
	}		
	//
}																														//


void Game::vertexSystem() // creates the line and allows it to move
{
	if (clicked==true && isInitalised == false && readyToGo == true)
	{
		m_line.clear();

		m_mouseClick = sf::Mouse::getPosition(m_window);

		sf::Vertex lineStart{ sf::Vector2f{m_shellPositionArray[0]}, sf::Color::Red };
		sf::Vertex lineEnd{ sf::Vector2f{m_mouseClick}, sf::Color::Red };

		m_line.append(lineStart);
		m_line.append(lineEnd);
	}
}



void Game::changeColor() // changes colours of the shells
{
	if (!colourSetup)
	{
		if (i == 0)
		{
			shellColoursArray[i] = true;
		} 

		else if (i < MAX_SHELLS && i > 0)
		{
			shellColoursArray[i] = false;
		}

		if (i > MAX_SHELLS - 1)
		{
			colourSetup = true;
		}
	}

	if (shellColoursArray[i] == true) 
	{
		m_circle.setFillColor(sf::Color::Green);
	}

	else if (shellColoursArray[i] == false)
	{
		m_circle.setFillColor(sf::Color::Red);
	}
}

void Game::collisions() // loop that checks for collisions
{
	for (int i = 0; i < activeShells - 1; i++)
	{
		for (int j = i + 1; j < activeShells; j++)
		{
			if (checkForCollisions(i, j))
			{
				processCollision(i, j);
			}
		}
	}
}


bool Game::checkForCollisions(int t_A, int t_B) // checks left and then right above and below, checks distance between centres against diameter if gets past intersecting states
{
	// param t_A is index of the first shell
	// param t_B is index of the first shell

	float distanceSqured{ 0.0f };
	MyVector3 gap{};

	if (m_shellPositionArray[t_A].x + DIAMETERf < m_shellPositionArray[t_B].x)
	{
		return false;
	}
	if (m_shellPositionArray[t_A].x - DIAMETERf > m_shellPositionArray[t_B].x)
	{
		return false;
	}
	if (m_shellPositionArray[t_A].y + DIAMETERf < m_shellPositionArray[t_B].y)
	{
		return false;
	}
	if (m_shellPositionArray[t_A].y - DIAMETERf > m_shellPositionArray[t_B].y)
	{
		return false;
	}
	gap = m_shellPositionArray[t_A] - m_shellPositionArray[t_B];
	distanceSqured = gap.lengthSquared();

	if (distanceSqured < DIAMETER_SQUAREDf)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}


void Game::processCollision(int t_A, int t_B) // proccess of the collisions and reverse the shell by 10
{
	MyVector3 lineofCentres{};
	MyVector3 swapFromA{};
	MyVector3 keepFromA{};
	MyVector3 swapFromB{};
	MyVector3 keepFromB{};
	int count = { 0 };

	while (checkForCollisions(t_A, t_B) && count < 10)
	{
		m_shellPositionArray[t_A]-= m_velocityArray[t_A] * 0.1f;
		m_shellPositionArray[t_B]-= m_velocityArray[t_B] * 0.1f;
		std::cout << "Collided" << std::endl;

		count++;
	}

	while (checkForCollisions(t_A, t_B))
	{
		m_shellPositionArray[t_A] += MyVector3{ 1.0f,1.0f,0.0f };
		m_shellPositionArray[t_B] += MyVector3{-1.0f,-1.0f,0.0f };
		std::cout << "CollidedDDDDDDDDDDD" << std::endl;
	}
	lineofCentres = m_shellPositionArray[t_A] - m_shellPositionArray[t_B];
	swapFromA = m_velocityArray[t_A].projection(lineofCentres);
	keepFromA = m_velocityArray[t_A].rejection(lineofCentres);
	swapFromB = m_velocityArray[t_B].projection(lineofCentres);
	keepFromB = m_velocityArray[t_B].rejection(lineofCentres);
	m_velocityArray[t_A] = swapFromB + keepFromA;
	m_velocityArray[t_B] = swapFromA + keepFromB;
}
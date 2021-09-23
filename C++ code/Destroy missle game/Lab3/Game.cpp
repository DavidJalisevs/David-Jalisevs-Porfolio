/// <summary>
/// @author David jalisevs
/// c00239534
/// @date November 2019
///  ALL INSTRUCTIONS IN main.cpp 
///  ALL SESSIONS int the main.cpp
/// 
/// </summary>

#include "Game.h"
#include <iostream>
#include "MyVector2.h"


/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Save the Planet" },
	m_exitGame{false} //when true game will exit
{
	background();
	setUpGameTexts(); // load font 
	groundSprite(); // load texture
	groundBasicSprite();// not fun textue
	baseSprite(); // fun base
	baseBasicSprite(); // not fun base
	setupSounds(); // get sound
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

		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseReleaseEvents(newEvent); // keep code tidy	
		
		}

	}

}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::G == t_event.key.code)
	{
		b_funTextures = !b_funTextures;

	}

	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	baseBasicSprite();
	groundBasicSprite();
	powerBar.setSize(sf::Vector2f{ powerLeft,20.0f });
	playerAlive();


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
	m_window.clear(sf::Color::Black);

	if (b_funTextures == true)
	{
		m_window.draw(m_backsprite);
	}
	m_window.draw(m_groundSprite);
	m_window.draw(m_baseSprite);

	if (livesCount == 0)
	{
		m_window.draw(m_gameOverMsg);
	}

	m_window.draw(m_basicGround);
	m_window.draw(m_basicBase);
	m_window.draw(m_powerBar);
	m_window.draw(m_livesLeft);
	m_window.draw(m_scoreCount);
	m_window.draw(m_laserLine);

	if (b_funExplosion == true)
	{
		m_window.draw(m_funExpSprite);
	}

	m_window.draw(m_explosionBasicCircle);
	m_window.draw(m_meteorLine);
	m_window.draw(powerBar);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setUpGameTexts() // set game over text and ever single other text
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_gameOverMsg.setFont(m_ArialBlackfont);
	m_gameOverMsg.setString("Game Over");
	m_gameOverMsg.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_gameOverMsg.setPosition(sf::Vector2f{ 300.0f, 250.0f });
	m_gameOverMsg.setCharacterSize(40U);
	m_gameOverMsg.setOutlineColor(sf::Color::Red);
	m_gameOverMsg.setFillColor(sf::Color::Black);
	m_gameOverMsg.setOutlineThickness(3.0f);

	m_powerBar.setFont(m_ArialBlackfont);
	m_powerBar.setString("Power:");
	m_powerBar.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_powerBar.setPosition(sf::Vector2f{ 0.0f, 570.0f });

	m_livesLeft.setFont(m_ArialBlackfont);
	m_livesLeft.setString("Lives:" + std::to_string(livesCount));
	m_livesLeft.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_livesLeft.setPosition(sf::Vector2f{ 630.0f, 0.0f });
	m_livesLeft.setCharacterSize(20U);

	m_scoreCount.setFont(m_ArialBlackfont);
	m_scoreCount.setString("Score:" + std::to_string(scoreCount));
	m_scoreCount.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_scoreCount.setPosition(sf::Vector2f{ 630.0f, 25.0f });
	m_scoreCount.setCharacterSize(20U);
}

/// <summary>
/// load the texture and setup the sprite for the ground
/// </summary>
/// 
/// 
/// 
/// 


void Game::background() // background function
{
	if (!m_backgrounds.loadFromFile("ASSETS\\IMAGES\\meteor.jpg"))
	{
		std::cout << "Problem with backgorund loading " << std::endl;
	}

	m_backsprite.setTexture(m_backgrounds);
	m_backsprite.setPosition(-100.0f, 0.0f);
}



void Game::groundBasicSprite() // basic grround sprite - rectangle 
{
	m_basicGround.setPosition(sf::Vector2f{ 0.0f,600.0f - m_basicGround.getSize().y });
	m_basicGround.setSize(sf::Vector2f{ 800.0f,30.0f });
	m_basicGround.setFillColor(sf::Color::Blue);

	if (b_funTextures == true)
	{
		m_basicGround.setFillColor(sf::Color::Transparent);
	}
}


void Game::groundSprite() // GRAPHICS ground + Power bar texture as it always there
{
	if (!m_groundTexture.loadFromFile("ASSETS\\IMAGES\\ground.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	m_groundSprite.setTexture(m_groundTexture);
	m_groundSprite.setPosition(sf::Vector2f{ 0.0f, 600.0f - m_groundTexture.getSize().y});

	powerBar.setFillColor(sf::Color::Red);
	powerBar.setSize(sf::Vector2f{ power, -5.0f });
	powerBar.setPosition(sf::Vector2f{ 125.0f, 585.0f });
	powerBar.setOrigin(sf::Vector2f{ 0.0f, powerBar.getSize().y / 2 });
}


void Game::baseSprite() // HRAPHICS base sprite 
{
	if (!m_baseTexture.loadFromFile("ASSETS\\IMAGES\\base.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_baseSprite.setTexture(m_baseTexture);
	m_baseSprite.setPosition((sf::Vector2f{ 380.0f, 550.0f }) + m_baseOffSet);
	m_baseSprite.setOrigin(sf::Vector2f{ 20.0f, 1.0f });
	//m_baseSprite.setScale(1.0f, 1.0f);
}

void Game::baseBasicSprite() // rectangle base 
{
	m_basicBase.setPosition(sf::Vector2f{ 380.0f,530.0f });
	m_basicBase.setSize(sf::Vector2f{ 40.0f,40.0f });
	m_basicBase.setFillColor(sf::Color::Red);

	if (b_funTextures == true)
	{
		m_basicBase.setFillColor(sf::Color::Transparent);
	}
}

void Game::basicExplosion() // circle explosion 
{
	m_explosionBasicCircle.setOrigin(sf::Vector2f{ radiusIncrease, radiusIncrease });
	m_explosionBasicCircle.setPosition(sf::Vector2f{ laserTempPosition });
	m_explosionBasicCircle.setRadius(radiusIncrease);
	m_explosionBasicCircle.setFillColor(sf::Color::Red);
	m_explosionBasicCircle.setOutlineColor(sf::Color::Red);
	m_explosionBasicCircle.setOutlineThickness(2.0f);
	
	if (b_funTextures == true) // if grapics are on it will make this potato graphics invisible 
	{
		m_explosionBasicCircle.setFillColor(sf::Color::Transparent);
		m_explosionBasicCircle.setOutlineColor(sf::Color::Red);
	}

	if (radiusIncrease <= 20.0f && b_circleExpand == true) // adds on radius
	{
		radiusIncrease += 1.0f;
	}
	
	if (radiusIncrease == 20.0f ) // stop
	{
		radiusIncrease = 0.0f;
		b_circleExpand = false;
		laserTempPosition = sf::Vector2f{ 400.0f,560.0f };
	}
}



void Game::superExplosion() // BOOM BOOM explosion WORKS ONLY WITH 1ST CLICK FOR SOME REASON even if you are in no graphics mode and pnce you swtich to graphics it will show it once on your last click
{

	if (b_funTextures == true)
	{

		if (b_funExplosion == true)
		{
			if (!m_funExpTexture.loadFromFile("ASSETS\\IMAGES\\explosion.png"))
			{
				// simple error message if previous call fails
				std::cout << "problem loading logo" << std::endl;
			}
			m_funExpSprite.setTexture(m_funExpTexture);
			m_funExpSprite.setOrigin(sf::Vector2f{ 34.0f, 34.0f });
			m_funExpSprite.setPosition(sf::Vector2f{ laserKeepPosition });

			m_expFrameCounter += m_expFrameIncrement;
			m_expFrameV = static_cast<int>(m_expFrameCounter) % 6;
			m_expFrameH = static_cast<int>(m_expFrameCounter) / 6;

			m_funExpSprite.setTextureRect(sf::IntRect{ -m_expFrameV,m_expFrameH * 66, 60 , 66 });

			//std::cout << "BOOOOOOOOOOM"  << std::endl;

				//if (b_circleExpand == false) // makes visible or invisible 
			//	{
					//b_funExplosion = false; 
					// create temp varibale tyo holdcoord for exlposion in the collision section

				//} // thought it will fix problem with explosion but it doesnt really

		}
	}
}


void Game::setupSounds() // sound funtions
{
	if (!m_expBuffer.loadFromFile("ASSETS\\AUDIO\\explosion.wav")) // EXPLOSION SOUND
	{
		std::cout << "problem loading Explosion sound" << std::endl;
	}
	m_expSound.setBuffer(m_expBuffer);

	if (!m_missleBuffer.loadFromFile("ASSETS\\AUDIO\\missleStart.wav")) // Missle starting sound
	{
		std::cout << "problem loading Missle sound" << std::endl;
	}
	m_missleSound.setBuffer(m_missleBuffer);

	if (!m_deathBuffer.loadFromFile("ASSETS\\AUDIO\\deathLaugh.wav")) // death sound 
	{
		std::cout << "problem loading Death sound" << std::endl;
	}
	m_deathSound.setBuffer(m_deathBuffer);

	if (!m_groundBuffer.loadFromFile("ASSETS\\AUDIO\\bruh.wav")) // once meteor hits the ground sound
	{
		std::cout << "problem loading lost health sound" << std::endl;
	}
	m_groundSound.setBuffer(m_groundBuffer);

	if (!m_themeBuffer.loadFromFile("ASSETS\\AUDIO\\assemble.wav")) // theme sound - after switching back to potato graphics it will run for a while as sound is about 5 seconds long
	{
		std::cout << "problem loading theme sound" << std::endl;
	}
	m_themeSound.setBuffer(m_themeBuffer);

	float themeVolume{ 20.0f }; // set volume for the theme a bit lower
	m_themeSound.setVolume(themeVolume);

	srand (time(NULL)); // just place to hold seed for now and maybe final place also warning 
}


void Game::linesLaser() // just a laser line set up
{
	m_laserLine.clear();
	// laser line set up 
	sf::Vertex laserStart{ sf::Vector2f{400.0f,560.0f},sf::Color::Transparent}; // laser lines
	sf::Vertex laserEnd{ laserPosition,sf::Color::Red }; // laser lines 

	m_laserLine.append(laserStart);
	m_laserLine.append(laserEnd);
}

void Game::linesMeteor() // meteor line set up
{
	m_laserLine.clear();
	// meteor line set up
	sf::Vertex meteorStartVertex{ sf::Vector2f{meteorStart},sf::Color::Transparent }; // laser lines
	sf::Vertex meteorEnd{ sf::Vector2f{meteorEnding},sf::Color::Green }; // laser lines 
	
	m_meteorLine.append(meteorStartVertex);
	m_meteorLine.append(meteorEnd);
}






void Game::processMouseReleaseEvents(sf::Event t_mouseEvent)
{
	//mouse detect
	if (sf::Mouse::Left == t_mouseEvent.mouseButton.button)
	{
		if(b_laserGoes == false)			

		m_mouseClick = sf::Vector2f{ static_cast<float>(t_mouseEvent.mouseButton.x),static_cast<float>(t_mouseEvent.mouseButton.y) };
		b_mouseRelease = true;
		
	}
}

void Game::laserVelocity() // calculating velocity of the laser and make it move
{

	if (b_laserGoes == false) 
	{
		m_laserHeading = m_mouseClick - laserPosition;
		m_laserHeading = vectorUnitVector(m_laserHeading);
		m_laserVelocity = m_laserHeading * m_lazerSpeed;
		b_laserGoes = true;
	}

	if (b_laserGoes == true) // moves laser
	{
		laserPosition += m_laserVelocity;
		powerLeft += m_laserVelocity.y;

		if (b_funTextures == true) // playing sound
		{
			if (sf::Sound::Playing != m_missleSound.getStatus())
			{
				m_missleSound.play();
			}
		}
	}

	laserTempPosition = laserPosition; // gets temp coords and holds them for the explosion
	laserKeepPosition = laserPosition;

	if (m_mouseClick.y >= laserPosition.y || powerLeft <= 0.0f) // laseer comes to its point
	{

		m_laserLine.clear();
		b_mouseRelease = false; // bool
		b_funExplosion = true;
		b_circleExpand = true;
		b_laserGoes = false;


		m_laserHeading = sf::Vector2f{ 0.0f, 0.0f };
		laserPosition = sf::Vector2f{ 400.0f,560.0f };


		if (b_funTextures == true) // sound added for the xplosion for the explode in the air
		{
			if (sf::Sound::Playing != m_expSound.getStatus())
			{
				m_expSound.play();
			}
		}
	}
}


void Game::meteorVelocity() // meteor velocity
{
	if (b_meteorGoes == false) // meteor velocity calculations
	{
		std::cout << "Lives" << livesCount << std::endl;


		randomMeteorTop.x = rand() % 800 + 1; // warning with possible loss of date
		randomMeteorBottom.x = rand() % 800 + 1; // warning with possible loss of date dont know how to fix 

		if (meteorCounter == meteorTreshold && b_meteorSpeedIncrement == true) // so if the counter is same as treshold it adds up speed by 0.5f
		{

			m_meteorSpeed += 0.5f;
			meteorTreshold += 5;

			if (m_meteorSpeed >= 10.0f)
			{
				b_meteorSpeedIncrement = false;
			}
		}

		meteorStart = randomMeteorTop;
		meteorEnding = meteorStart;
		m_meteorHeading = randomMeteorBottom - meteorStart;
		m_meteorHeading = vectorUnitVector(m_meteorHeading);
		m_meteorVelocity = m_meteorHeading * m_meteorSpeed; // velocity

		std::cout << std::to_string  (meteorStart.x) << " " << std::to_string(meteorStart.y) << std::endl; // coords to see
		b_meteorGoes = true;
	}


	if (b_meteorGoes == true) // makes meteor move
	{
			
			meteorEnding += m_meteorVelocity; // goes
			linesMeteor();
		
			
	}
	
	if (meteorEnding.y >= randomMeteorBottom.y) // meteor touches bottom
	{
		m_meteorLine.clear();
		m_meteorHeading = sf::Vector2f{ 0.0f, 0.0f };
		meteorEnding = sf::Vector2f{ 0.0f,0.0f };
		b_meteorGoes = false;
		livesCount-=1; // if it goes on the ground - 1 hp
		m_livesLeft.setString("Lives:" + std::to_string(livesCount));

		if (b_funTextures == true) // sound of the ground and - 1 hp 
		{
			if (sf::Sound::Playing != m_groundSound.getStatus())  // to play sound
			{
				m_groundSound.play();
			}
		}
	}
}



void Game::lineBetween() // line between the meteor and laser that detects collision
{
	distMeteorToLaser = meteorEnding - laserTempPosition;
	invisibleLine = vectorLength(distMeteorToLaser);

	if (invisibleLine < 20) // meteor interacts with laser
	{
		std::cout << "Meteors destroyed" << meteorCounter << std::endl;

		m_meteorLine.clear();
		m_meteorHeading = sf::Vector2f{ 0.0f, 0.0f };
		meteorEnding = sf::Vector2f{ 0.0f,0.0f };
		m_laserHeading = sf::Vector2f{ 0.0f, 0.0f };
		laserPosition = sf::Vector2f{ 400.0f,560.0f };
		b_meteorGoes = false;
		scoreCount += 3; // score
		meteorCounter += 1; // meteor add up for the incresing speed
		std::cout << "score " << scoreCount << std::endl; // check in the console if workds
		m_scoreCount.setString("Score:" + std::to_string(scoreCount)); // to update the numbers
		b_mouseRelease = false; // bool
		b_circleExpand = true;
		b_funExplosion = true;
		b_laserGoes = false;
\
		if (scoreCount >= scoreTreshold) // adds +3 HP if as you reach every 50 points 
		{
			livesCount += 3;
			scoreTreshold += 50;
		}

		m_livesLeft.setString("Lives:" + std::to_string(livesCount));

		if (b_funTextures == true) // if true explosuin sounds for the explode in the meteor
		{
			if (sf::Sound::Playing != m_expSound.getStatus())  // to play sound
			{
				m_expSound.play();
			}
		}
	}


	if (laserPosition.x > m_mouseClick.x) // change the position of the base not the position but side
	{
		m_baseSprite.setScale(sf::Vector2f{ -1.0f, 1.0f });
	}
	else
	{
		m_baseSprite.setScale(sf::Vector2f{ 1.0f, 1.0f });
	}

}



void Game::playerAlive() // while player is alive or died 
{

	if (livesCount != 0)
	{
		meteorVelocity();

		if (powerLeft <= 600.0f && b_laserGoes == false)
		{
			powerLeft += 5;
		}

		if (b_funTextures == true)
		{
			if (sf::Sound::Playing != m_themeSound.getStatus())  // to play sound
			{
				m_themeSound.play();
			}
		}
		basicExplosion();

		lineBetween();

		if (b_funTextures == true)
		{
			superExplosion();
		}

		if (b_mouseRelease == true)
		{
			laserVelocity();
			linesLaser();


		}
	}

	if (livesCount == 0)
	{

		if (b_funTextures == true)
		{
			if (sf::Sound::Playing != m_deathSound.getStatus())
			{
				m_deathSound.play();
			}

		}

	}

}
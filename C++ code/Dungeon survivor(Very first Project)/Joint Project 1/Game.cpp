// Name: David Jalisevs	
// Login: c00239534
// Date: 03/02/20
// Approximate time taken: 15 hours 
//---------------------------------------------------------------------------
// Project description: WW3 Tank offensive, player has to defend its land 
// from oncoming enemy tanks, if tanks will reach bottom player will lose hp.
// ---------------------------------------------------------------------------
// Known Bugs:
// sometimes bullets go throught SmartEnemy while still killing it but not adding to the score,after bullet hits they enemy it keeps going
// rather than reset, smart enemy gets reset.
// ?

//////////////////////////////////////////////////////////// 
// include correct library file for release and debug versions
//////////////////////////////////////////////////////////// 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 



#include "Game.h"   // include Game header file
#include "MyVector2.h" // vectors


int main()
{
	
	Game aGame;
	aGame.loadContent();
	aGame.run();
	
	return 0;
}

Game::Game() : window(sf::VideoMode(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT)), "WW3 TANK OFFENSIVE", sf::Style::Default)
// Default constructor
{
	backGround();
}

void Game::loadContent()
// Load the font file & setup the message string
{
	if (isPlayerAlive)
	{
		if (!m_font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
		{
			std::cout << "error with font file file";
		}

		srand(time(nullptr)); // set the seed once

		myPlayer.setBody();
		regularEnemy.enemySetUp();
		myBullet.setBulletBody(myPlayer.m_playerSprite.getPosition());
		myBullet.setSound();
		setSound();

		m_backGroundSound.play();


		//SmartEnemyOne.smartBody();

		// set up the message string 
		m_message.setFont(m_font);  // set the font for the text
		m_message.setCharacterSize(24); // set the text size
		m_message.setFillColor(sf::Color::White); // set the text colour
		m_message.setPosition(10, 10);  // its position on the screen

		// set up the health message string 
		m_healthMessage.setFont(m_font);  // set the font for the text
		m_healthMessage.setCharacterSize(36u); // set the text size
		m_healthMessage.setFillColor(sf::Color::Red); // set the text colour
		m_healthMessage.setPosition(1300, 10);  // its position on the screen
		m_healthMessage.setString("HP " + std::to_string(m_playerHealth));


		m_scoreMessage.setFont(m_font);  // set the font for the text
		m_scoreMessage.setCharacterSize(36u); // set the text size
		m_scoreMessage.setFillColor(sf::Color::Red); // set the text colour
		m_scoreMessage.setPosition(1300, 40);  // its position on the screen
		m_scoreMessage.setString("Score " + std::to_string(m_playerScore));


		m_gameOverText.setFont(m_font);  // set the font for the text
		m_gameOverText.setCharacterSize(200u); // set the text size
		m_gameOverText.setFillColor(sf::Color::Red); // set the text colour
		m_gameOverText.setPosition(400, 300);  // its position on the screen
		m_gameOverText.setString("Game Over");
	}
}


void Game::run()
// This function contains the main game loop which controls the game. 
{
	if (isPlayerAlive)
	{
		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
		sf::Time timeSinceLastUpdate = sf::Time::Zero;

		// the clock object keeps the time.
		sf::Clock clock;


		clock.restart();

		while (window.isOpen())
		{
			// check if the close window button is clicked on
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			//get the time since last update and restart the clock
			timeSinceLastUpdate += clock.restart();

			//update every 60th of a second
			//only when the time since last update is greater than 1/60 update the world.
			if (timeSinceLastUpdate > timePerFrame)
			{
				update();
				draw();

				// reset the timeSinceLastUpdate to 0 
				timeSinceLastUpdate = sf::Time::Zero;
			}
		}  // end while loop
	} // end if player is alive
}

void Game::update()
// This function takes the keyboard input and updates the game world
{	
	if (isPlayerAlive)
	{

		if (m_playerHealth <= 0)
		{
			isPlayerAlive = false;
		}
		m_healthMessage.setString("HP " + std::to_string(m_playerHealth));
		m_scoreMessage.setString("Score " + std::to_string(m_playerScore));

		// update any game variables here ...
		myPlayer.move();
		myPlayer.boundryCheck();

		regularEnemy.regEnemyUpdate();

		collisions();

		SmartEnemyOne.smartBody();
		SmartEnemyOne.enemyVelocity(myPlayer.m_playerSprite.getPosition());
		SmartEnemyOne.smartCollision(myPlayer.m_playerSprite.getGlobalBounds(), m_playerHealth);
		SmartEnemyOne.bulletCollision(myBullet.bulletSprite.getGlobalBounds());
		SmartEnemyOne.smartAnimate();
		SmartEnemyOne.linesEnemy();
		myBullet.bulletFired(myPlayer.m_playerSprite.getPosition());
		myBullet.bulletDirection();
		
		myBullet.bulletBoundary(myPlayer.m_playerSprite.getPosition(), bulletCollideControl, smartEnemyControl);

	}

	if (!isPlayerAlive)
	{
		m_backGroundSound.stop();

		if (sf::Sound::Playing != m_deadSound.getStatus())
		{
			m_deadSound.play();
		}
	}
}

void Game::draw()
// This function draws the game world
{
	// Clear the screen and draw your game sprites
	if (isPlayerAlive)
	{
		window.clear();
		window.draw(m_backsprite);

		m_message.setString("WW3 Tank Offensive");
		window.draw(m_healthMessage);
		window.draw(m_scoreMessage);
		window.draw(m_message);  // write message to the screen

		myBullet.drawBullet(window);
		myPlayer.draw(window);
		SmartEnemyOne.enemyDraw(window);
		regularEnemy.enemyDraw(window);
		window.display();
	}
	if (!isPlayerAlive)
	{
		window.clear();
		window.draw(m_gameOverText);
		window.display();
	}
}


void Game::setSound()
{
	if (!m_backGroundBuffer.loadFromFile("ASSETS\\AUDIO\\background.wav")) // EXPLOSION SOUND
	{
		std::cout << "problem loading Explosion sound" << std::endl;
	}
	m_backGroundSound.setBuffer(m_backGroundBuffer);
	m_backGroundSound.setVolume(70.0f);

	if (!m_deadBuffer.loadFromFile("ASSETS\\AUDIO\\dead.wav")) // EXPLOSION SOUND
	{
		std::cout << "problem loading Explosion sound" << std::endl;
	}
	m_deadSound.setBuffer(m_deadBuffer);

	if (!m_regFloorBuffer.loadFromFile("ASSETS\\AUDIO\\quack.wav")) // EXPLOSION SOUND
	{
		std::cout << "problem loading Explosion sound" << std::endl;
	}
	m_regFloorSound.setBuffer(m_regFloorBuffer);

}

void Game::backGround()
{
	if (!m_backgrounds.loadFromFile("ASSETS\\IMAGES\\floor.png"))
	{
		std::cout << "Problem with backgorund loading " << std::endl;
	}

	m_backsprite.setTexture(m_backgrounds);
	m_backsprite.setOrigin(sf::Vector2f{ 40.0f,40.0f });
	m_backsprite.setScale(sf::Vector2f{ 2.1f, 2.1f });
}



/// <summary>
/// checks for collisions 
/// </summary>
void Game::collisions()
{
	for (int i = 0; i < SMART_MAX; i++) // smart enemies with player
	{
		if (myBullet.bulletSprite.getGlobalBounds().intersects(SmartEnemyOne.smartEnemySprite[i].getGlobalBounds()))
		{
			smartEnemyControl = true;
			m_playerScore+=5;

		}
	}


	for (int i = 0; i <= 2; i++)
	{

		if (myBullet.bulletSprite.getGlobalBounds().intersects(regularEnemy.squareEnemy[i].getGlobalBounds()))
		{

			sf::Vector2f m_randomTank{ 0.0f,0.0f };
			m_randomTank.x = rand() % 1500 + 2; // warning with possible loss of date
			regularEnemy.squareEnemy[i].setPosition(m_randomTank);
			m_playerScore+=2;
			bulletCollideControl = true;
		}

		if (regularEnemy.squareEnemy[i].getPosition().y >= SCREEN_HEIGHT - 25)
		{
			if (sf::Sound::Playing != m_regFloorSound.getStatus())
			{
				m_regFloorSound.play();
			}
		}

		if (myPlayer.m_playerSprite.getGlobalBounds().intersects(regularEnemy.squareEnemy[i].getGlobalBounds()) || regularEnemy.squareEnemy[i].getPosition().y >= SCREEN_HEIGHT - 25) // regular enemues with player collision
		{
			sf::Vector2f m_randomTank{ 0.0f,0.0f };
			std::cout << "collided" << std::endl;
			m_randomTank.x = rand() % 1500 + 2; // warning with possible loss of date
			m_playerHealth--;
			std::cout << m_playerHealth << std::endl;
			regularEnemy.squareEnemy[i].setPosition(m_randomTank);
		}
	}
}


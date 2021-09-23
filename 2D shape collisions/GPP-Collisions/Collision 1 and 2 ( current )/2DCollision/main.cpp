#include <iostream>
#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include <tinyc2.h>
#include <AnimatedSprite.h>
#include <GameObject.h>
#include <Player.h>
#include <NPC.h>
#include <Input.h>
#include <Debug.h>

using namespace std;
/// <summary>
/// Name - Davids jalisevs
/// ID - C00239534
/// INFO--------------------------
/// When circle Collided it will display proper text in the console, also change the color to random color
/// Move Circle with W,A,S,D
/// </summary>

int main()
{

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(1440, 900), "SFML window");
	srand(time(NULL));

	/// <summary>
	/// create cirle sfml
	/// </summary>
	/// <returns></returns>

	sf::CircleShape playerCircShape;
	sf::CircleShape npcCircShape;

	int playerRadius = 30;
	playerCircShape.setRadius(playerRadius);
	playerCircShape.setPosition(500, 500);
	playerCircShape.setOrigin(sf::Vector2f(playerRadius, playerRadius));
	playerCircShape.setFillColor(sf::Color::Green);


	int randRadius = rand() % 40 + 25;
	npcCircShape.setRadius(randRadius);
	npcCircShape.setPosition(80, 700);
	npcCircShape.setOrigin(sf::Vector2f(randRadius, randRadius));
	npcCircShape.setFillColor(sf::Color::Red);


	//capsule
	
	sf::RectangleShape capsuleBigJonesToe;
	capsuleBigJonesToe.setPosition(325, 399);
	capsuleBigJonesToe.setFillColor(sf::Color::Blue);
	capsuleBigJonesToe.setSize(sf::Vector2f(50,100));
	capsuleBigJonesToe.setOrigin(25, 100);
	sf::CircleShape circShapeCapsule1;
	circShapeCapsule1.setRadius(25);
	circShapeCapsule1.setOrigin(25,25);
	circShapeCapsule1.setPosition(325, 296.3);
	circShapeCapsule1.setFillColor(sf::Color::Blue);

	sf::CircleShape circShapeCapsule2;
	circShapeCapsule2.setRadius(25);
	circShapeCapsule2.setOrigin(25, 25);
	circShapeCapsule2.setPosition(325, 400.7);
	circShapeCapsule2.setFillColor(sf::Color::Blue);


	//Create Triangle to circle collision
	sf::ConvexShape playerTrianShape;
	sf::Vector2f pointA{ 700, 700 };
	sf::Vector2f pointB{ 790, 650 };
	sf::Vector2f pointC{ 810, 840 };

	playerTrianShape.setPointCount(3);
	playerTrianShape.setPoint(0, pointA);
	playerTrianShape.setPoint(1, pointB);
	playerTrianShape.setPoint(2, pointC);
	playerTrianShape.setFillColor(sf::Color::Magenta);

	// Circle to point(circle is small point)
	sf::CircleShape pointCircle;
	pointCircle.setRadius(1);
	pointCircle.setPosition(100, 100);
	pointCircle.setFillColor(sf::Color::Yellow);


	//Circle to ray



	// Load a NPC's sprites to display
	sf::Texture npc_texture;
	if (!npc_texture.loadFromFile("assets\\grid.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Load a mouse texture to display
	sf::Texture player_texture;
	if (!player_texture.loadFromFile("assets\\player.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Setup NPC's Default Animated Sprite
	AnimatedSprite npc_animated_sprite(npc_texture);
	npc_animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));

	// Setup Players Default Animated Sprite
	AnimatedSprite player_animated_sprite(player_texture);
	player_animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));

	// Setup the NPC
	GameObject &npc = NPC(npc_animated_sprite);

	// Setup the Player
	GameObject &player = Player(player_animated_sprite);

	//Setup NPC AABB
	c2AABB aabb_npc;
	aabb_npc.min = c2V(npc.getAnimatedSprite().getPosition().x, npc.getAnimatedSprite().getPosition().y);
	aabb_npc.max = c2V(
		npc.getAnimatedSprite().getPosition().x +
		npc.getAnimatedSprite().getGlobalBounds().width, 
		npc.getAnimatedSprite().getPosition().y +
		npc.getAnimatedSprite().getGlobalBounds().height);

	//Setup Player AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);
	aabb_player.max = c2V(player.getAnimatedSprite().getGlobalBounds().width / 6, player.getAnimatedSprite().getGlobalBounds().width / 6);


	// setup circle
	c2Circle c2PlayerCircle;
	c2Circle c2NpcCircle;
	// setup triangle 
	c2Poly c2NpcTriangle;
	
	//setup capsule
	c2Capsule capsule;
	
	//setup a a box
	c2AABB circlePoint;
	circlePoint.min = c2V(100, 100);
	circlePoint.max = c2V(101, 101);

	//setup a ray
	c2Ray ray;
	int rayX = 900;
	int rayY = 500;
	float normX = 1;
	float normY = -4;
	float time = 200;
	ray.p = c2V(rayX, rayY);
	ray.d = c2Norm(c2V(normX, normY));
	ray.t = time;
	sf::Vertex rayLine[] =
	{
		sf::Vertex(sf::Vector2f(ray.p.x, ray.p.y), sf::Color::Red),
		sf::Vertex(sf::Vector2f(ray.p.x + (ray.d.x * ray.t), ray.p.y + (ray.d.y * ray.t)), sf::Color::Red)
	};


	// Initialize Input
	Input input;

	// Collision result
	int result = 0;
	int resultCircleToCircle;
	int resultCircleToPolygon;
	int resultCircleToCapsule;
	int resultCircleToBox;
	int resultcircleToRay;
	int resultAABBtoCapsule;
	int resultAABBtoPoly;
	int resultAABBtoRay;
	int resultAABBtoCircle;
	int resultRaytoPoly;


	// Direction of movement of NPC
	sf::Vector2f direction(0.1f, 0.2f);
	
	// Start the game loop
	while (window.isOpen())
	{
		/// <summary>
		/// Player movement 
		/// </summary>
		/// <returns></returns>
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){playerCircShape.move(-0.2, 0);}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){playerCircShape.move(0.2,0);}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){playerCircShape.move(0, -0.2);}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){playerCircShape.move(0, 0.2);}

		if (playerCircShape.getPosition().x <= 0)
		{
			playerCircShape.setPosition(1400, 700);
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { playerTrianShape.move(-0.2, 0); }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { playerTrianShape.move(0.2, 0); }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { playerTrianShape.move(0, -0.2); }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { playerTrianShape.move(0, 0.2); }





		// get circle points and radius to tiny2C
		c2PlayerCircle.p = c2V(playerCircShape.getPosition().x, playerCircShape.getPosition().y);
		c2PlayerCircle.r = playerCircShape.getRadius();

		c2NpcCircle.p = c2V(npcCircShape.getPosition().x, npcCircShape.getPosition().y);
		c2NpcCircle.r = npcCircShape.getRadius();

		//get Polygon to tiny2C
		c2NpcTriangle.count = 3;
		c2NpcTriangle.verts[0] = c2V(playerTrianShape.getPoint(0).x, playerTrianShape.getPoint(0).y); //c2V(700, 700);
		c2NpcTriangle.verts[1] = c2V(playerTrianShape.getPoint(1).x, playerTrianShape.getPoint(1).y);
		c2NpcTriangle.verts[2] = c2V(playerTrianShape.getPoint(2).x, playerTrianShape.getPoint(2).y);

		//capsule
		capsule.a = c2V(325, 296.3);
		capsule.b = c2V(325, 400.7);
		capsule.r = 25;

		//ray update
		ray.p = c2V(rayX, rayY);
		ray.d = c2Norm(c2V(normX, normY));
		ray.t = time;



		//c2NpcTriangle.verts = c2V(POLY_NORM, POLY_NORM);

		// Move Sprite Follow Mouse
		player.getAnimatedSprite().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		
		// Move The NPC
		sf::Vector2f move_to(npc.getAnimatedSprite().getPosition().x + direction.x, npc.getAnimatedSprite().getPosition().y + direction.y);

		if (move_to.x < 0) {
			direction.x *= -1;
			move_to.x = 0 + npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.x + npc.getAnimatedSprite().getGlobalBounds().width >= 800) { 
			direction.x *= -1;
			move_to.x = 800 - npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.y < 0) { 
			direction.y *= -1;
			move_to.y = 0 + npc.getAnimatedSprite().getGlobalBounds().height;
		}
		else if (move_to.y + npc.getAnimatedSprite().getGlobalBounds().height >= 600) {
			direction.y *= -1;
			move_to.y = 600 - npc.getAnimatedSprite().getGlobalBounds().height;
		}
		
		npc.getAnimatedSprite().setPosition(move_to);

		// Update NPC AABB set x and y
		aabb_npc.min = c2V(
			npc.getAnimatedSprite().getPosition().x, 
			npc.getAnimatedSprite().getPosition().y
		);

		aabb_npc.max = c2V(
			npc.getAnimatedSprite().getPosition().x +
			npc.getAnimatedSprite().getGlobalBounds().width,
			npc.getAnimatedSprite().getPosition().y +
			npc.getAnimatedSprite().getGlobalBounds().height
		);

		// Update Player AABB
		aabb_player.min = c2V(
			player.getAnimatedSprite().getPosition().x, 
			player.getAnimatedSprite().getPosition().y
		);
		aabb_player.max = c2V(
			player.getAnimatedSprite().getPosition().x +
			player.getAnimatedSprite().getGlobalBounds().width, 
			player.getAnimatedSprite().getPosition().y + 
			player.getAnimatedSprite().getGlobalBounds().height
		);


		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					input.setCurrent(Input::Action::LEFT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					input.setCurrent(Input::Action::RIGHT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					input.setCurrent(Input::Action::UP);
				}
				break;
			default:
				input.setCurrent(Input::Action::IDLE);
				break;
			}
		}

		
		// Handle input to Player
		player.handleInput(input);

		// Update the Player
		player.update();

		// Update the Player
		npc.update();

		// Check for collisions
		result = c2AABBtoAABB(aabb_player, aabb_npc);
		cout << ((result != 0) ? ("Collision") : "") << endl;
		if (result){
			player.getAnimatedSprite().setColor(sf::Color(255,0,0));
		}
		else {
			player.getAnimatedSprite().setColor(sf::Color(0, 255, 0));
		}

		//Check for the Circle to Cirlce collision
		resultCircleToCircle = c2CircletoCircle(c2PlayerCircle, c2NpcCircle);
		if (resultCircleToCircle)
		{
			cout << "Circle collided" << endl;
			int randomColor{ 0 };
			sf::Color colourArray[6]{ sf::Color::Red,sf::Color::Blue, sf::Color::Magenta,sf::Color::Cyan, sf::Color::Yellow };
			randomColor = rand() % 6 + 1;
			playerCircShape.setFillColor(colourArray[randomColor]);

		}

		//circle to poly
		resultCircleToPolygon = c2CircletoPoly(c2PlayerCircle, &c2NpcTriangle, NULL);
		if (resultCircleToPolygon)
		{
			int randomColor{ 0 };
			sf::Color colourArray[6]{ sf::Color::Red,sf::Color::Blue,sf::Color::Cyan, sf::Color::Yellow };
			randomColor = rand() % 6 + 1;
			playerTrianShape.setFillColor(colourArray[randomColor]);
			cout << "Triangle collided" << endl;
		}

		//circle to capsule
		resultCircleToCapsule = c2CircletoCapsule(c2PlayerCircle, capsule);
		if (resultCircleToCapsule)
		{
			int randomColor{ 0 };
			sf::Color colourArray[6]{ sf::Color::Red,sf::Color::Blue,sf::Color::Cyan, sf::Color::Yellow };
			randomColor = rand() % 6 + 1;
			playerCircShape.setFillColor(colourArray[randomColor]);
			circShapeCapsule1.setFillColor(colourArray[randomColor]);
			circShapeCapsule2.setFillColor(colourArray[randomColor]);
			capsuleBigJonesToe.setFillColor(colourArray[randomColor]);

			cout << "Capsule collided" << endl;
		}

		//circle to a box
		resultCircleToBox= c2CircletoAABB(c2PlayerCircle, circlePoint);
		if (resultCircleToBox)
		{
			cout << "Point collided" << endl;
		}


		// Raycast
		c2Raycast casting;
		resultcircleToRay = c2RaytoCircle(ray, c2PlayerCircle, &casting);
		if (resultcircleToRay)
		{
			cout << "Ray collided" << endl;
		}
		

		resultAABBtoCapsule = c2AABBtoCapsule(aabb_player, capsule);
		if (resultAABBtoCapsule)
		{
			cout << "Box to Capsule collided" << endl;
		}

		resultAABBtoPoly = c2AABBtoPoly(aabb_player, &c2NpcTriangle, NULL);
		if (resultAABBtoPoly)
		{
			cout << "Box to Poly collided" << endl;
		}

	
		resultAABBtoRay = c2RaytoAABB(ray, aabb_player, &casting);
		if (resultAABBtoRay)
		{
			cout << "Box collided to ray" << endl;
		}

		resultAABBtoCircle = c2CircletoAABB(c2PlayerCircle, aabb_player);
		if (resultAABBtoCircle)
		{
			cout << "Player circle with player Box collided" << endl;
		}

		resultRaytoPoly = c2RaytoPoly(ray, &c2NpcTriangle, NULL, &casting);
		if (resultRaytoPoly)
		{
			cout << "Poly with ray collided" << endl;
		}


		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprite
		window.draw(player.getAnimatedSprite());

		// Draw the NPC's Current Animated Sprite
		window.draw(npc.getAnimatedSprite());
		window.draw(playerTrianShape);
		window.draw(playerCircShape);
		window.draw(npcCircShape);
		window.draw(capsuleBigJonesToe);
		window.draw(circShapeCapsule1);
		window.draw(circShapeCapsule2);
		window.draw(pointCircle);
		window.draw(rayLine,2,sf::Lines);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};


#include <Game.h>
#include <Cube.h>
#include <Player.h>
#include <Easing.h>
/// <summary>
///							CUBEFIELD
/// Name: David Jalisevs
/// ID: C00239534
/// Time taken around 10 hours so far
/// </summary>

// Helper to convert Number to String for HUD
template <typename T>
string toString(T number)
{
	ostringstream oss;
	oss << number;
	return oss.str();
}

GLuint	vsid,		// Vertex Shader ID
		fsid,		// Fragment Shader ID
		progID,		// Program ID
		vao = 0,	// Vertex Array ID
		vbo,		// Vertex Buffer ID
		vib,		// Vertex Index Buffer
		to[1];		// Texture ID
GLint	positionID,	// Position ID
		colorID,	// Color ID
		textureID,	// Texture ID
		uvID,		// UV ID
		mvpID,		// Model View Projection ID
		x_offsetID, // X offset ID
		y_offsetID,	// Y offset ID
		z_offsetID;	// Z offset ID

GLenum	error;		// OpenGL Error Code


//Please see .//Assets//Textures// for more textures
const string filename = ".//Assets//Textures//texture_2.tga";

int width;						// Width of texture
int height;						// Height of texture
int comp_count;					// Component of texture
const int AMOUNT_OF_CUBES =40;
unsigned char* img_data;		// image data


float cameraX = 100000.0f;
float cameraY = 5.0f;
float cameraZ = 30.0f;
mat4 mvp, projection, 
		view, model;			// Model View Projection

Font font;						// Game font

float x_offset, y_offset, z_offset; // offset on screen (Vertex Shader)

Game::Game(sf::ContextSettings settings) : 
	window(VideoMode(1400, 900), 
	"Introduction to OpenGL Texturing", 
	sf::Style::Default, 
	settings)
{
	float xAxisRight = 100003.0f;
	float zAxis = -100.0f;

	for (int i = 0; i < 20;i++)
	{
		game_object[i] = new GameObject();
		game_object[i]->setPosition(vec3(xAxisRight, 0.0f, zAxis));
		xAxisRight = xAxisRight + 1.0f;
		zAxis = zAxis + 5.0f;
	}

	float xAxisLeft = 99997.0f;
	float zAxisLeft = -100.0f;
	for (int i = 20; i < 40;i++)
	{
		game_object[i] = new GameObject();
		game_object[i]->setPosition(vec3(xAxisLeft, 0.0f, zAxisLeft));
		xAxisLeft = xAxisLeft - 1.0f;
		zAxisLeft = zAxisLeft + 5.0f;
	}




	game_object_player[0] = new GameObjectPlayer();
	game_object_player[0]->setPosition(vec3(100000.0f, 0.0f, 22.0f));


}

Game::~Game()
{
}



void Game::run()
{

	initialize();

	Event event;

	float rotation = 0.01f;
	float start_value = 0.0f;
	float end_value = 1.0f;

	while (isRunning){

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

#if (DEBUG >= 2)
	DEBUG_MSG("Calling Cleanup...");
#endif
	unload();

}

void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;
	m_lives = 3;
	m_playerScore = 0.0f;
	speedIncrement = true;
	if (!(!glewInit())) { DEBUG_MSG("glewInit() failed"); }

	// Copy UV's to all faces
	for (int i = 1; i < 6; i++)
		memcpy(&uvs[i * 4 * 2], &uvs[0], 2 * 4 * sizeof(GLfloat));

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	// Vertex Array Buffer
	glGenBuffers(1, &vbo);		// Generate Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Vertices (3) x,y,z , Colors (4) RGBA, UV/ST (2)
	//===================================================================================================================================
	int countVERTICES = game_object[0]->getVertexCount();
	int countCOLORS = game_object[0]->getColorCount();
	int countUVS = game_object[0]->getUVCount();
	int countINDICES = game_object[0]->getIndexCount();


	int countVERTICESPlayer = game_object_player[0]->getVertexCount();
	int countCOLORSPlayer = game_object_player[0]->getColorCount();
	int countUVSPlayer = game_object_player[0]->getUVCount();
	int countINDICESPlayer = game_object_player[0]->getIndexCount();

	if (!m_backgroundTexture.loadFromFile("./backGround.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading background for the menu" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setPosition(0,0);
	//m_backgroundSprite.setScale(1.4, 1.4);

	if (!m_collideBuffer.loadFromFile("./mySoundPew.wav")) // EXPLOSION SOUND./resources/
	{
		std::cout << "problem loading gameplay sound " << std::endl;
	}
	m_collideSound.setBuffer(m_collideBuffer);
	m_collideSound.setVolume(35.0f);



	if (!m_backSound.openFromFile("./Euclid1.ogg")) // EXPLOSION SOUND./resources/
	{
		std::cout << "problem loading backgorund sound " << std::endl;
	}
	//m_backSound.setBuffer(m_backSoundBuffer);
	m_backSound.setVolume(43.0f);
	m_backSound.play();

	m_backSound.setLoop(true); // loop a sound


	glBufferData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS) + (2 * UVS)) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &vib); //Generate Vertex Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);


	/// <summary>
	/// RESTART THE GAME
	/// </summary>
	float xAxisRight = 100003.0f;
	float zAxis = -100.0f;
	m_scoreTreshold = 200;
	m_cubeSpeed = 0.01f;
	for (int i = 0; i < 20;i++)
	{
		game_object[i] = new GameObject();
		game_object[i]->setPosition(vec3(xAxisRight, 0.0f, zAxis));
		xAxisRight = xAxisRight + 1.0f;
		zAxis = zAxis + 5.0f;
	}

	float xAxisLeft = 99997.0f;
	float zAxisLeft = -100.0f;
	for (int i = 20; i < 40;i++)
	{
		game_object[i] = new GameObject();
		game_object[i]->setPosition(vec3(xAxisLeft, 0.0f, zAxisLeft));
		xAxisLeft = xAxisLeft - 1.0f;
		zAxisLeft = zAxisLeft + 5.0f;
	}


	 cameraX = 100000.0f;
	 cameraY = 5.0f;
	 cameraZ = 30.0f;

	game_object_player[0] = new GameObjectPlayer();
	game_object_player[0]->setPosition(vec3(100000.0f, 0.0f, 22.0f));



	//read best score from file
	fstream my_file;
	my_file.open("bestScore.txt", ios::in);
	if (!my_file) {
		cout << "No such file";
	}
	else {
		while (1) {
			my_file >> m_playerBestScore;
			if (my_file.eof())
				break;
		}

	}
	my_file.close();





	// Indices to be drawn
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);

	// NOTE: uniforms values must be used within Shader so that they 
	// can be retreived
	const char* vs_src =
		"#version 400\n\r"
		""
		"in vec3 sv_position;"
		"in vec4 sv_color;"
		"in vec2 sv_uv;"
		""
		"out vec4 color;"
		"out vec2 uv;"
		""
		"uniform mat4 sv_mvp;"
		"uniform float sv_x_offset;"
		"uniform float sv_y_offset;"
		"uniform float sv_z_offset;"
		""
		"void main() {"
		"	color = sv_color;"
		"	uv = sv_uv;"
		//"	gl_Position = vec4(sv_position, 1);"
		"	gl_Position = sv_mvp * vec4(sv_position.x + sv_x_offset, sv_position.y + sv_y_offset, sv_position.z + sv_z_offset, 1 );"
		"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL);
	glCompileShader(vsid);

	// Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	const char* fs_src =
		"#version 400\n\r"
		""
		"uniform sampler2D f_texture;"
		""
		"in vec4 color;"
		"in vec2 uv;"
		""
		"out vec4 fColor;"
		""
		"void main() {"
		"	fColor = color - texture2D(f_texture, uv);"
		""
		"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);

	// Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();
	glAttachShader(progID, vsid);
	glAttachShader(progID, fsid);
	glLinkProgram(progID);

	// Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Set image data
	// https://github.com/nothings/stb/blob/master/stb_image.h
	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to[0]);
	glBindTexture(GL_TEXTURE_2D, to[0]);

	// Wrap around
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Filtering
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Bind to OpenGL
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(
		GL_TEXTURE_2D,			// 2D Texture Image
		0,						// Mipmapping Level 
		GL_RGBA,				// GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width,					// Width
		height,					// Height
		0,						// Border
		GL_RGBA,				// Bitmap
		GL_UNSIGNED_BYTE,		// Specifies Data type of image data
		img_data				// Image Data
		);

	// Projection Matrix 
	projection = perspective(
		45.0f,					// Field of View 45 degrees
		4.0f / 3.0f,			// Aspect ratio
		5.0f,					// Display Range Min : 0.1f unit
		100.0f					// Display Range Max : 100.0f unit
		);

	// Camera Matrix
	view = lookAt(
		vec3(cameraX, cameraY, cameraZ),	// Camera (x,y,z), in World Space
		vec3(cameraX, 0.0f, 0.0f),		// Camera looking at origin
		vec3(0.0f, 1.0f, 0.0f)		// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
		);

	// Model matrix
	model = mat4(
		1.0f					// Identity Matrix
		);

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	// Load Font
	font.loadFromFile(".//Assets//Fonts//BBrick.ttf");
}

void Game::update()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Updating...");
#endif
	if (!started)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			started = true;
		}
	}
	if (started)
	{
		if (m_lives > 0)
		{
			// Update Model View Projection
			// For mutiple objects (cubes) create multiple models
			// To alter Camera modify view & projection
			mvp = projection * view * model;

			DEBUG_MSG(model[0].x);
			DEBUG_MSG(model[0].y);
			DEBUG_MSG(model[0].z);

			//std::cout << "player Z axis : " << game_object_player[0]->getPosition().z << std::endl;
			//std::cout << "cube  Z axis : " << game_object[0]->getPosition().z << std::endl;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			{
				std::cout << "playerX:" << m_playerCurrentRealX << std::endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			{
				std::cout << "Rand X:" << m_randomNumber << std::endl;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
			{
				std::cout << "Neg X:" << m_playerCurrentPosNegativeX << std::endl;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				std::cout << "Pos X:" << m_playerCurrentPosPositiveX << std::endl;
			}

			// MOVEMENT OF THE CUBES TOWARDS PLAYER
			for (int i = 0; i < AMOUNT_OF_CUBES;i++)
			{
				float movement = game_object[i]->getPosition().z + m_cubeSpeed;
				float currentX = game_object[i]->getPosition().x;
				game_object[i]->setPosition((vec3(currentX, 0.25f, movement)));
				if (m_playerScore > m_scoreTreshold && speedIncrement)
				{
					m_scoreTreshold = m_scoreTreshold + 150;
					m_cubeSpeed = m_cubeSpeed + 0.01f;
				}

				if (m_cubeSpeed > 0.053)
				{
					speedIncrement = false;
				}
			}
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
			{
				std::cout << "Cube Speed :" << m_cubeSpeed << std::endl;
			}*/
			m_playerScore = m_playerScore + 0.01f;


			// check bounds of the enemy boxes
			for (int i = 0; i < AMOUNT_OF_CUBES;i++)
			{
				m_playerCurrentRealX = game_object_player[0]->getPosition().x;
				m_playerCurrentPosNegativeX = m_playerCurrentRealX - 55;
				m_playerCurrentPosPositiveX = m_playerCurrentRealX + 55;
				m_randomNumber = rand() % (m_playerCurrentPosPositiveX - m_playerCurrentPosNegativeX + 1) + m_playerCurrentPosNegativeX;
				if (game_object[i]->getPosition().z > 35)
				{
					game_object[i]->setPosition((vec3(m_randomNumber, 0.25f, -80.0f)));

					//m_playerScore = m_playerScore + 1;

				}
			}
			//player movement update
			playerMovement();
			checkCollision();
		}
		if (m_lives < 1)
		{
			if (m_playerScore > m_playerBestScore)
			{
				m_playerBestScore = m_playerScore;


				fstream my_file;
				my_file.open("bestScore.txt", ios::out);
				if (!my_file) {
					cout << "File not created!";
				}
				else {
					cout << "File created successfully!";
					my_file << m_playerBestScore;
					my_file.close();
				}




			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{

				initialize();
			}
		}
	}
}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Render Loop...");
#endif

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Save current OpenGL render states
		// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7
		window.pushGLStates();

		string hudLives = "Lifes: " + string(toString(m_lives)) + "";
		string hudScore = "Score: " + string(toString(m_playerScore)) + "";
		string lostMessage = "You lost";
		string restartMessage = "Press 'R' to restart the game";
		string startMessage = "Press 'ENTER' to start the game ! ";

		string hudScorePrevious = "Best score: " + string(toString(m_playerBestScore)) + "";

		Text textScore(hudScore, font);
		Text textLifes(hudLives, font);
		Text textLost(lostMessage, font);
		Text textRestart(restartMessage, font);
		Text textBestScore(hudScorePrevious, font);
		Text testStartGame(startMessage, font);

		textScore.setFillColor(sf::Color::Red);
		textScore.setPosition(50.f, 50.f);
		textLifes.setFillColor(sf::Color::Green);
		textLifes.setPosition(1200.f, 50.f);
		textLost.setFillColor(sf::Color::Red);
		textLost.setPosition(530.f, 300.f);
		textLost.setCharacterSize(75);
		textRestart.setFillColor(sf::Color(255, 255, 255, 170));
		textRestart.setPosition(460.f, 400.f);
		textBestScore.setFillColor(sf::Color::Cyan);
		textBestScore.setPosition(580.f, 50.f);
		testStartGame.setFillColor(sf::Color::White);
		testStartGame.setPosition(450.f, 400.f);


		recShape.setSize(sf::Vector2f(3000.0f, 1550.0f));
		recShape.setFillColor(sf::Color(10, 10, 10, 235));
		recShape.setOrigin(1500.0f, 275.0f);

		recShape.setPosition(sf::Vector2f(700.0f, 625.0f));
		recShape.setRotation(backgroundRotation);

		if (!started)
		{
			window.draw(m_backgroundSprite);
			window.draw(testStartGame);
		}
		// PLAYER ALIVE====================================================================

		if (m_lives > 0 && started)
		{
			window.draw(m_backgroundSprite);
			window.draw(recShape);

			window.draw(textScore);
			window.draw(textLifes);
			window.draw(textBestScore);

		}
		//PLAYER DEAD====================================================================
		if (m_lives < 1 && started)
		{
			window.draw(textLost);
			window.draw(textRestart);

			textBestScore.setPosition(10.f, 800.f);
			window.draw(textBestScore);

			textScore.setPosition(10.f, 700.f);
			window.draw(textScore);
		}
		// Restore OpenGL render states
		// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7

		window.popGLStates();

		// Rebind Buffers and then set SubData
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

		// Use Progam on GPU
		glUseProgram(progID);

		// Find variables within the shader
		// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
		positionID = glGetAttribLocation(progID, "sv_position");
		if (positionID < 0) { DEBUG_MSG("positionID not found"); }

		colorID = glGetAttribLocation(progID, "sv_color");
		if (colorID < 0) { DEBUG_MSG("colorID not found"); }

		uvID = glGetAttribLocation(progID, "sv_uv");
		if (uvID < 0) { DEBUG_MSG("uvID not found"); }

		textureID = glGetUniformLocation(progID, "f_texture");
		if (textureID < 0) { DEBUG_MSG("textureID not found"); }

		mvpID = glGetUniformLocation(progID, "sv_mvp");
		if (mvpID < 0) { DEBUG_MSG("mvpID not found"); }

		x_offsetID = glGetUniformLocation(progID, "sv_x_offset");
		if (x_offsetID < 0) { DEBUG_MSG("x_offsetID not found"); }

		y_offsetID = glGetUniformLocation(progID, "sv_y_offset");
		if (y_offsetID < 0) { DEBUG_MSG("y_offsetID not found"); }

		z_offsetID = glGetUniformLocation(progID, "sv_z_offset");
		if (z_offsetID < 0) { DEBUG_MSG("z_offsetID not found"); };

		// VBO Data....vertices, colors and UV's appended
		// Add the Vertices for all your GameOjects, Colors and UVS

		glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), game_object_player[0]->getVertex());


		//glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), vertices);
		glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLORSPLAYER * sizeof(GLfloat), colorsPlayer);

		glBufferSubData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat), 2 * UVS * sizeof(GLfloat), uvs);

		// Send transformation to shader mvp uniform [0][0] is start of array
		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

		// Set Active Texture .... 32 GL_TEXTURE0 .... GL_TEXTURE31
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(textureID, 0); // 0 .... 31

		// Set the X, Y and Z offset (this allows for multiple cubes via different shaders)
		// Experiment with these values to change screen positions


		/*glUniform1f(x_offsetID, 0.00f);
		glUniform1f(y_offsetID, 0.00f);
		glUniform1f(z_offsetID, 0.00f);*/

		// Set pointers for each parameter (with appropriate starting positions)
		// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
		glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, (VOID*)(3 * VERTICESPLAYER * sizeof(GLfloat)));
		glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, (VOID*)(((3 * VERTICESPLAYER) + (4 * COLORSPLAYER)) * sizeof(GLfloat)));

		// Enable Arrays
		glEnableVertexAttribArray(positionID);
		glEnableVertexAttribArray(colorID);
		glEnableVertexAttribArray(uvID);


		if (m_lives > 0)
		{
			//player
			glUniform1f(x_offsetID, game_object_player[0]->getPosition().x);
			glUniform1f(y_offsetID, game_object_player[0]->getPosition().y);
			glUniform1f(z_offsetID, game_object_player[0]->getPosition().z);
			// Draw Element Arrays
			glDrawElements(GL_TRIANGLES, 3 * INDICESPLAYER, GL_UNSIGNED_INT, NULL);
		}

		glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, (VOID*)(3 * VERTICES * sizeof(GLfloat)));
		glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, (VOID*)(((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat)));
		glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLORS * sizeof(GLfloat), colors);
		glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), game_object[0]->getVertex());

		if (m_lives > 0)
		{
			for (int i = 0; i < AMOUNT_OF_CUBES;i++)
			{
				// vubes
				glUniform1f(x_offsetID, game_object[i]->getPosition().x);
				glUniform1f(y_offsetID, game_object[i]->getPosition().y);
				glUniform1f(z_offsetID, game_object[i]->getPosition().z);

				glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);
			}
		}

		window.display();

		// Disable Arrays
		glDisableVertexAttribArray(positionID);
		glDisableVertexAttribArray(colorID);
		glDisableVertexAttribArray(uvID);

		// Unbind Buffers with 0 (Resets OpenGL States...important step)
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Reset the Shader Program to Use
		glUseProgram(0);

		// Check for OpenGL Error code
		error = glGetError();
		if (error != GL_NO_ERROR) {
			DEBUG_MSG(error);
		}

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDetachShader(progID, vsid);	// Shader could be used with more than one progID
	glDetachShader(progID, fsid);	// ..
	glDeleteShader(vsid);			// Delete Vertex Shader
	glDeleteShader(fsid);			// Delete Fragment Shader
	glDeleteProgram(progID);		// Delete Shader
	glDeleteBuffers(1, &vbo);		// Delete Vertex Buffer
	glDeleteBuffers(1, &vib);		// Delete Vertex Index Buffer
	stbi_image_free(img_data);		// Free image stbi_image_free(..)
}


void Game::playerMovement()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		pressed = true;

	}
	else
	{
		pressed = false;

	}

	//movement for the player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		float movement = game_object_player[0]->getPosition().x - m_playerSpeed;
		float currentY = game_object_player[0]->getPosition().y;
		float currentZ = game_object_player[0]->getPosition().z;
		game_object_player[0]->setPosition((vec3(movement, currentY, currentZ)));
		cameraX = cameraX - m_playerSpeed;
		if (rotationXPlayer > -0.6000f)
		{
			rotationXPlayer = rotationXPlayer - 0.0005f;
		}

		if (backgroundRotation < 28.6000f)
		{
			backgroundRotation = backgroundRotation + 0.0250f;
			recShape.setRotation(backgroundRotation);
		}

	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		float movement = game_object_player[0]->getPosition().x + m_playerSpeed;
		float currentY = game_object_player[0]->getPosition().y;
		float currentZ = game_object_player[0]->getPosition().z;
		game_object_player[0]->setPosition((vec3(movement, currentY, currentZ)));
		cameraX = cameraX + m_playerSpeed;
		if (rotationXPlayer < 0.6000f)
		{
			rotationXPlayer = rotationXPlayer + 0.0005f;
		}

		if (backgroundRotation > -28.6000f)
		{
			backgroundRotation = backgroundRotation - 0.0250f;
			recShape.setRotation(backgroundRotation);
		}
	}	

	if (!pressed)
	{

		if (rotationXPlayer > 0.0f)
		{
			rotationXPlayer = rotationXPlayer - 0.0005f;
		}
		if (rotationXPlayer < 0.0f)
		{
			rotationXPlayer = rotationXPlayer + 0.0005f;
		}

		if (backgroundRotation > 0.0f)
		{
			backgroundRotation = backgroundRotation - 0.025f;
			recShape.setRotation(backgroundRotation);

		}

		if (backgroundRotation < 0.0f)
		{
			backgroundRotation = backgroundRotation + 0.025f;
			recShape.setRotation(backgroundRotation);

		}
	}

	view = lookAt(
		vec3(cameraX, cameraY, cameraZ),	// Camera (x,y,z), in World Space
		vec3(cameraX, 0.0f, 0.0f),		// Camera looking at origin
		vec3(rotationXPlayer, 1.0f, 0.0f)		// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
	);

}

void Game::checkCollision()
{
	bool subLife = false;
	for (int i = 0; i < AMOUNT_OF_CUBES;i++)
	{
		if (game_object[i]->getPosition().z > game_object_player[0]->getPosition().z - 1 && game_object[i]->getPosition().z < game_object_player[0]->getPosition().z + 1) // Use Z instead of Y
		{
			if (game_object[i]->getPosition().x > game_object_player[0]->getPosition().x - 1.7 && game_object[i]->getPosition().x < game_object_player[0]->getPosition().x + 1.7)
			{
				std::cout << "COLLISION DETECTED" << std::endl;
				m_collideSound.play();
				subLife = true;
				if (subLife)
				{
					float m_randomNumber = rand() % 50 + (-20);
					game_object[i]->setPosition((vec3(m_randomNumber, 0.25f, -80.0f)));
					m_lives = m_lives - 1;
					
					subLife = false;
				}

			}
		}
		
	}
}


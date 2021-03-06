#ifndef GAME_OBJECT_PLAYER_H
#define GAME_OBJECT_PLAYER_H

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

#include <stdio.h>
#include <string.h>
#include <Player.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class GameObjectPlayer
{
private:
	// Cube Elements
	GLfloat vertex[ARRAY_SIZE(verticesPlayer)];
	GLfloat color[ARRAY_SIZE(colorsPlayer)];
	GLfloat uv[ARRAY_SIZE(uvsPlayer)];
	GLfloat index[ARRAY_SIZE(indicesPlayer)];
	vec3 position;
public:
	GameObjectPlayer();
	~GameObjectPlayer();

	vec3 getPosition();
	void setPosition(vec3 position);

	// Returns the first element of the array
	GLfloat* getVertex();
	// 3 Vertices
	int getVertexCount();

	// Returns the first element of the array
	GLfloat* getColor();
	// 3 Colors RGB
	int getColorCount();

	// Returns the first element of the array
	GLfloat* getUV();
	// 3 Colors RGB
	int getUVCount();

	// Returns the first element of the array
	GLfloat* getIndex();
	// 3 Colors RGB
	int getIndexCount();
};

#endif // !GAME_OBJECT_H


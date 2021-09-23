#include <GameObjectPlayer.h>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
GameObjectPlayer::GameObjectPlayer()
{
	// Copy the Cube contents into GameObject
	memcpy(this->vertex, verticesPlayer, sizeof(this->vertex));
	memcpy(this->color, colorsPlayer, sizeof(this->color));
	memcpy(this->uv, uvsPlayer, sizeof(this->uv));

	// Copy UV's to all faces
	for (int i = 1; i < 6; i++)
		memcpy(&uv[i * 4 * 2], &uv[0], 2 * 4 * sizeof(GLfloat));
	memcpy(this->index, indicesPlayer, sizeof(this->index));

	this->position = vec3();
	srand(time(NULL));

}

GameObjectPlayer::~GameObjectPlayer()
{
}

vec3 GameObjectPlayer::getPosition() { return this->position; }
void GameObjectPlayer::setPosition(vec3 position) { this->position = position; }

// Returns the first element of the Vertex array
GLfloat* GameObjectPlayer::getVertex() { return this->vertex; }
// 3 Vertices
int GameObjectPlayer::getVertexCount() { return ARRAY_SIZE(vertex) / 3; }

// Returns the first element of the Color array
GLfloat* GameObjectPlayer::getColor() { return this->color; }
// 4 Colors RGBA
int GameObjectPlayer::getColorCount() { return ARRAY_SIZE(color) / 4; }

// Returns the first element of the UV array
GLfloat* GameObjectPlayer::getUV() { return this->uv; }
// 3 Colors RGB
int GameObjectPlayer::getUVCount() { return ARRAY_SIZE(uv); }

// Returns the first element of the Index array
GLfloat* GameObjectPlayer::getIndex() { return this->index; }
// 3 Colors RGB
int GameObjectPlayer::getIndexCount() { return ARRAY_SIZE(index) / 3; }
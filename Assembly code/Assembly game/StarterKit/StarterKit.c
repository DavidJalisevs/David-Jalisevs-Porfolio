#include <stdbool.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <uzebox.h>
#include <defines.h>

#include "StarterKit.h"
#include "data/font-6x12-full.inc"

#define FOLLOWER_TIME_INTERVAL 300

int rnd(int max);
void init();
void update();
void draw();
void MoveHero(int x, int y);
void drawRectangle(int x, int y, int width, int height, char c);
bool checkCollision(int x1, int y1, int width1, int height1, int x2, int y2,
int width2, int height2);

static int heroX = 0;
static int heroY = 0;
static int heroWidth = 2;
static int heroHeight = 2;

static int enemyX = 0;
static int enemyY = 0;
static int enemyWidth = 3;
static int enemyHeight = 2;

static int patrolX = 0;
static int patrolY = 0;
static int patrolWidth = 5;
static int patrolHeight = 1;

static int followerX = 0;
static int followerY = 0;
static int followerWidth = 3;
static int followerHeight = 2;

static int medicX = 0;
static int medicY = 0;
static int medicWidth = 1;
static int medicHeight = 1;

static int followerThinkInterval = 300;
static int followerThinkTime = 0;
static int score = 0;
static int health = 100;
static int hitByTrooper = 0;
static int fruitsCollected = 0;

//Controller Variables
static int buttonHeld = 0;
static int buttonPressed = 0;
static int buttonReleased = 0;
static int buttonPrevious = 0;

int main() {
	//Set font and tiles to be used, and call prior to ClearVram();
	SetFontTable(font);

	init(); // Initialise Game

	while (1) {
		WaitVsync(1);
		//Update the controller Variables
		buttonHeld = ReadJoypad(0);
		buttonPressed = buttonHeld & (buttonHeld ^ buttonPrevious);
		buttonReleased = buttonPrevious & (buttonHeld ^ buttonPrevious);
		update();
		draw();
	}
}

int rnd(int max) {
	int result = rand() % max;
	return result;
}

void init() {
	heroX = rnd(SCREEN_TILES_H);
	heroY = rnd(SCREEN_TILES_V);
	enemyY = 0;
	enemyX = rnd(SCREEN_TILES_V);

	followerY = rnd(SCREEN_TILES_V);
	followerX = rnd(SCREEN_TILES_H);

	patrolX = 0;
	patrolY = rnd(SCREEN_TILES_V);

	medicX = 15;
	medicY = 10;
	
}

void update() {

	if(health > 0)
	{
		switch(buttonPressed){
			case BTN_UP:{
				MoveHero(0, -1);
				break;
			}
			case BTN_DOWN:{
				MoveHero(0, 1);
				break;
			}
			case BTN_LEFT:{
				MoveHero(-1, 0);
				break;
			}
			case BTN_RIGHT:{
				MoveHero(1, 0);
				break;
			}
			case BTN_A:{
				MoveHero(0, -1);
				break;
			}
			case BTN_B:{
				MoveHero(0, 1);
				break;
			}
			case BTN_X:{
				MoveHero(-1, 0);
				break;
			}
			case BTN_Y:{
				MoveHero(1, 0);
				break;
			}
			default:
				break;
		}


		buttonPrevious = buttonHeld;
		buttonPrevious = buttonHeld;

		followerThinkTime++;
		if (followerThinkTime > followerThinkInterval) {
			if (followerX < heroX)
				followerX++;
			if (followerX > heroX)
				followerX--;
			if (followerY < heroY)
				followerY++;
			if (followerY > heroY)
				followerY--;
			followerThinkTime = 0;
		}
		if (score > 3 && followerThinkInterval > 0) {
			followerThinkInterval--;
		}

		if (score == 0 && followerThinkInterval <= 0){
			followerThinkInterval = FOLLOWER_TIME_INTERVAL;
		}

		//write code to move the enemy down screen
		enemyY++;
		patrolX++;

		// check if the enemy has reached the bottom of the screen
		if (enemyY >= SCREEN_TILES_V - enemyHeight) {
			// reset enemy here..
			// to top of screen and a random y
			enemyX = rnd(SCREEN_TILES_H - enemyWidth);
			enemyY = 0;
		}
		//check if patrol has reached end side of the scnreen
		if (patrolX >= SCREEN_TILES_H - patrolWidth) {
			// reset enemy here..
			// to top of screen and a random y
			patrolY = rnd(13 - patrolHeight);
			patrolX = 0;
		}
		if (checkCollision(heroX, heroY, heroWidth, heroHeight, patrolX, patrolY,
				patrolWidth, patrolHeight) == true) {
			// write code to add score and reset enemy
			health = getHealth(health, -1);
			hitByTrooper = getStormTrooperCount(hitByTrooper,1);
			patrolY = rnd(SCREEN_TILES_V - patrolHeight);;
			patrolX = 0;

		}



		if (checkCollision(heroX, heroY, heroWidth, heroHeight, enemyX, enemyY,
				enemyWidth, enemyHeight) == true) {
			// write code to add score and reset enemy
			score = getScore(score, 1);
			enemyX = rnd(SCREEN_TILES_H - enemyWidth);
			enemyY = 0;
		}
		// collision with fruit medic
		if (checkCollision(heroX, heroY, heroWidth, heroHeight, medicX, medicY,
				medicWidth, medicHeight) == true) {
			// write code to add score and reset enemy
			fruitsCollected = getFruitCount(fruitsCollected,1);
			health = getHealth(health, 1);

			medicY = rnd(SCREEN_TILES_V);
			medicX = rnd(SCREEN_TILES_H);

		}


		if (checkCollision(heroX, heroY, heroWidth, heroHeight, followerX,
				followerY, followerWidth, followerHeight) == true) {
			// write code to add score and reset enemy
			score = getScore(score, -1);
			health = getHealth(health, -1);
			if(score <= 0 )
			{
				score = 0;
			}
			followerX = rnd(SCREEN_TILES_H - followerWidth);
			followerY = 0;
		}
	}
}

void draw() {
	if(health >0)
	{
	//Clear the screen (fills Vram with tile zero)
	ClearVram();
	Print(1, 0, PSTR("Score"));
	PrintInt(10, 0, score, false);
	Print(15, 0, PSTR("Health"));
	PrintInt(26,0,health, false);
	Print(1, 17, PSTR("Hit by Stormtrooper"));
	PrintInt(24,17,hitByTrooper, false);
	Print(26, 17, PSTR("Fruits"));
	PrintInt(36,17,fruitsCollected, false);

	drawRectangle(heroX, heroY, heroWidth, heroHeight, '0');
	drawRectangle(enemyX, enemyY, enemyWidth, enemyHeight, '$');
	drawRectangle(followerX, followerY, followerWidth, followerHeight, 'X');
	drawRectangle(patrolX,patrolY,patrolWidth,patrolHeight,'-');
	drawRectangle(medicX,medicY,medicWidth,medicHeight,'U');

	}

	if(health <=0)
	{
		ClearVram();
		Print(14, 9, PSTR("YOU LOST HAHA"));

	}
}

bool checkCollision(int x1, int y1, int width1, int height1, int x2, int y2,
		int width2, int height2) {
	// write the code to return true if collided.
	if (x1 + width1 < x2 || y1 + height1 < y2 || x1 > x2 + width2
			|| y1 > y2 + height2) {
		return false;
	} else {
		return true;
	}
}

void MoveHero(int x, int y) {
	// write code to move hero
	heroX = heroX + x;
	heroY = heroY + y;

	// write code to check if the hero is inside the window
	if (heroX < 0 || heroX + (TILE_WIDTH / heroWidth) >= SCREEN_TILES_H || heroY < 0
			|| heroY >= 16 ) {
		heroX = heroX - x;
		heroY = heroY - y;
	}
}

void drawRectangle(int x, int y, int width, int height, char c) {
	if (x < SCREEN_TILES_H && y < SCREEN_TILES_V) {

		for (int i = 0; i < width; i++) {
			if (x + i < SCREEN_TILES_H && y < SCREEN_TILES_V) {
				PrintChar(x + i, y, c);
			}
			if (y + height - 1 < SCREEN_TILES_V) {
				PrintChar(x + i, y + height - 1, c);
			}
		}
		for (int i = 1; i < height; i++) {
			PrintChar(x, y + i, c);
			PrintChar(x + width - 1, y + i, c);
		}
	}
}

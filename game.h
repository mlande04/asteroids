 /*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "ship.h"
#include "bullet.h"
#include "rocks.h"
#include "flyingObject.h"

#define INITIAL_ROCK_COUNT 5

/**********************************
* GAME
* Main game class
**********************************/
class Game
{
public:
	// constructors
	Game(Point top, Point bottom) : topLeft(top), bottomRight(bottom)
	{
		score = 0;
	        ship = new Ship;

		for (int i = 0; i < INITIAL_ROCK_COUNT; i++){
			Rocks* pRock = new BigRock(getRandomPoint());
			rocks.push_back(pRock);
		}
		
	}
	~Game()
	{
	  if (ship != NULL)
	    delete ship;
	  cleanUpDebris();
	}

	// game moves
	void handleInput(const Interface &ui);
	void advance();
	void draw(const Interface &ui);

private:
	// screen coordinates
	Point topLeft;
	Point bottomRight;
	// score
	int score;
	// ship mechanisms
	Ship* ship;
	list<Rocks*> rocks;
	list<Bullet*> bullet;
	// game logic
	void start();
	bool isOnScreen(const Point &point);
	void advanceShip();
	void advanceBullets();
	void advanceAsteroids();
	void createRocks();
	void handleCollisions();
	float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2 ) const;
	bool isCollision(const FlyingObject &obj1, const FlyingObject &obj2) const;
	void cleanUpDebris();
	void displayMenu();
	Point getRandomPoint() const;

};

#endif /* GAME_H */

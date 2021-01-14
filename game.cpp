/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

#define OFF_SCREEN_BORDER_AMOUNT 5

#define xMin -200
#define xMax 200
#define yMin -200
#define yMax 200

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;


// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

// start game with ship object
void Game::start()
{
   //ship(0.0, 0.0);
}

/************************************************
* Game::isCollision
*	checks for collisions between flying objects
************************************************/
bool Game::isCollision(const FlyingObject &obj1, const FlyingObject &obj2) const
{
	bool collision = false;
	
	// check if alive
	if (obj1.isAlive() && obj2.isAlive())
	{
		float space = getClosestDistance(obj1, obj2);
		float tooClose = obj1.getSize() + obj2.getSize();
		
		// check amount of space between objects
		if (space < tooClose)
		{
			// have a hit
			collision = true;
		}
	}
	
	return collision;
}

// game moves
/**************************************
* Game::handleInput
*   handles user input on the keyboard
**************************************/
void Game :: handleInput(const Interface &ui)
{
	// check for ship
	if (ship->isAlive())
	{
		// handles left arrow
		if (ui.isLeft())
			ship->moveLeft();
      
		// handles right arrow
		if (ui.isRight())
			ship->moveRight();
      
		// handles up arrow
		if (ui.isUp())
			ship->addVelocity();
      
		// handles spacebar
		if (ui.isSpace())
		{
			Bullet* pBullet = new Bullet;
			if (ship->isAlive())
			{
				pBullet->fire(ship->getPoint(), ship->getRotation(), ship->getVelocity());
				bullet.push_back(pBullet);
			}
		}
	}
}

/**********************************
* Game::advance	
* Purpose: advances the positions 
*	of flying objects in the game
**********************************/
void Game ::advance()
{
   advanceAsteroids();	
   advanceShip();
   advanceBullets();
   
   handleCollisions();
   cleanUpDebris();

}

/**********************************
* Game::draw
* Purpose: draws game objects
**********************************/
void Game ::draw(const Interface &ui)
{
    // draw ship
    ship->draw();

    // draw rocks
    for (list<Rocks*>::iterator rockIt = rocks.begin(); rockIt != rocks.end(); rockIt++)
    {
      (*rockIt)->draw();
    }
	
	// draw bullets
	for (list<Bullet*>::iterator fireIt = bullet.begin(); fireIt != bullet.end(); fireIt++)
	{
		(*fireIt)->draw();
	}
}

// game logic
/**********************************
* Game::isOnScreen
* Purpose: checks to see if objects
*	are on screen
**********************************/
bool Game :: isOnScreen(const Point &point)
{
	//return true;
   return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT 
         && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
         && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT
         && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT);
}

/**********************************
* Game::advanceShip
* Purpose:
**********************************/
void Game :: advanceShip()
{
   if (ship == NULL)
      Ship* newShip;
   else
      if (ship->isAlive()) // && ship != NULL)
         ship->advance();
}

/**********************************
* Game::
* Purpose:
**********************************/
void Game :: advanceBullets()
{
	// set count variable for life of bullet
	int count = 0;
	
	// move bullet on screen
	for (list<Bullet*>::iterator fireIt = bullet.begin();
        fireIt != bullet.end();
        fireIt++)
	{
		count++;
		(*fireIt)->advance();
		
		// check for end of bullet life
		if (count == 40)
			(*fireIt)->kill();
	}	
}

/**********************************
* Game::
* Purpose:
**********************************/
void Game :: advanceAsteroids()
{
	for (list<Rocks*>::iterator rockIt = rocks.begin();
        rockIt != rocks.end();
        rockIt++)
	{
		(*rockIt)->advance();
	}	
}

/**********************************
* Game::
* Purpose:
**********************************/
void Game :: createRocks()
{
   // put rock objects into a vector 
  for (int i = 0; i < 5; i++)
    {
      Point newPoint(random(-200, 200), random(-200, 200));
      Rocks* newRock = new BigRock(newPoint);
      if (newRock->isAlive() && newRock != NULL)
         rocks.push_back(newRock);
    }
}

/************************************************
* Game::handleCollisions
* Purpose: says what to do in case of collisions
************************************************/
void Game :: handleCollisions()
{
	// check for ship hitting asteroids
	for (list<Rocks*>::iterator rockIt = rocks.begin();
        rockIt != rocks.end();
        rockIt++)
	{
		if (isCollision(*ship, **rockIt))
			{
				ship->kill();
				(*rockIt)->kill();
				(*rockIt)->splitAsteroid(rocks);
			}
	}
	
	// check for asteroids hit by bullets
	for (list<Rocks*>::iterator rockIt = rocks.begin();
        rockIt != rocks.end();
        rockIt++)
		{
			for (list<Bullet*>::iterator bIt = bullet.begin();
				bIt != bullet.end();
				bIt++)
			if (isCollision(**bIt, **rockIt))
			{
				(*bIt)->kill();
				(*rockIt)->kill();
				(*rockIt)->splitAsteroid(rocks);
			}
		}
}

/**********************************
* Game::
* Purpose:
**********************************/
void Game :: cleanUpDebris()
{
	// clean up dead asteroids
	/*list<Rocks*>::iterator rockIt = rocks.begin();
    while (rockIt != rocks.end())
	{
		Rocks* pRock = *rockIt;
		
		if (!pRock->isAlive())
		{
			// clear rocks
			delete pRock;
			
			// remove from list
			rockIt = rocks.erase(rockIt);
		}
		else
		{
			// advance through rocks
			rockIt++;
		}
	}
			
	// clean up dead bullets
	list<Bullet*>::iterator bulletIt = bullet.begin();
	while (bulletIt != bullet.end())
	{
		Bullet* pBullet = *bulletIt;
		if (!pBullet->isAlive())
		{
			// clear bullets
			delete pBullet;
			
			//remove from list
			bulletIt = bullet.erase(bulletIt);
		}
		else
		{
			// advance through bullets
			bulletIt++;
		}
	}*/
}

/**********************************
* Game::
* Purpose:
**********************************/
void Game :: displayMenu()
{

}

/**********************************
* Game::getRandomPoint
* Purpose:selects a random point 
*   for flying objects to appear at
**********************************/
Point Game :: getRandomPoint() const
{
	int x = random(topLeft.getX(), bottomRight.getX());
	int y = random(bottomRight.getY(), topLeft.getY());

	Point p(x, y);
	return p;

}

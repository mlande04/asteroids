/*******************************
* File: rocks.h
********************************/
#include <iostream>
using namespace std;

#include "rocks.h"

// Base Class::ROCK METHODS
/*****************
* Rocks::isHit
*****************/
bool Rocks::isHit()
{
	this->hit = true;
	
	return true;
}

/********************
* Rocks::draw
*********************/
void Rocks::draw()
{
	this->rotation += 10;
  drawLargeAsteroid(point, rotation);
}
/********************
* Rocks::rotate
*********************/
void Rocks::rotate()
{
	this->rotation = rotation;
}

// BIG ROCK METHODS
/********************
* BigRock::draw
*********************/
void BigRock::draw()
{
   drawLargeAsteroid(point, rotation);
}

/********************
* BigRock::rotate
*********************/
void BigRock::rotate()
{
	this->rotation = BIG_ROCK_SPIN;
}

/********************
* BigRock::splitAsteroid
*********************/
void BigRock::splitAsteroid(std::list<Rocks*> &rocks)
{
	// make list of smaller asteroids
	if (type == 1)
	{
		Point newPoint(getPoint());
		
		Rocks* newRock1 = new MediumRock(newPoint);
		velocity.addDy(1.0);
		rocks.push_back(newRock1);

		Rocks* newRock2 = new MediumRock(newPoint);
		velocity.addDy(-1.0);
		rocks.push_back(newRock2);

		Rocks* newRock3 = new SmallRock(newPoint);
		velocity.addDx(2.0);
		rocks.push_back(newRock3);
	}
}

// MEDIUM ROCK METHODS
/********************
* MediumRock::draw
*********************/
void MediumRock::draw()
{
	//cout << "MedRocks" << rotation;
	drawMediumAsteroid(point, rotation);
}

/********************
* MediumRock::rotate
*********************/
void MediumRock::rotate()
{
	this->rotation = MEDIUM_ROCK_SPIN;
}

/****************************
* MediumRock::splitAsteroid
****************************/
void MediumRock::splitAsteroid(std::list<Rocks*> &rocks)
{
	// make list of smaller asteroids
	if (type == 2)
	{
		Point newPoint(getPoint());
		
		Rocks* newRock1 = new SmallRock(newPoint);
		velocity.addDx(3.0);
		rocks.push_back(newRock1);

		Rocks* newRock2 = new SmallRock(newPoint);
		velocity.addDx(-3.0);
		rocks.push_back(newRock2);
	}
}

// SMALL ROCK METHODS
/********************
* SmallRock::draw
*********************/
void SmallRock::draw()
{
	//cout << "SmallRocks" << rotation;
	drawSmallAsteroid(point, rotation);
}

/********************
* SmallRock::rotate
*********************/
void SmallRock::rotate()
{
	this->rotation = SMALL_ROCK_SPIN;
}

/**************************
* SmallRock::splitAsteroid
**************************/
void SmallRock::splitAsteroid(std::list<Rocks*> &rocks)
{
	kill();
}


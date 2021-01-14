#ifndef bullet_h
#define bullet_h

#include <cmath>

#define BULLET_SPEED 5
#define BULLET_LIFE 40
//#define D2R M_PI / 180.0

#include <iostream>
using namespace std;

#include "flyingObject.h"
#include "ship.h"

// Put your Bullet class here
class Bullet : public FlyingObject
{
public:
	Bullet() : FlyingObject(), count(0) {}
	Bullet(float x, float y, float dX, float dY)
	{
		//float rX = cos(D2R(rotate)) * BULLET_SPEED;
		//float rY = sin(D2R(rotate)) * BULLET_SPEED;
	}

	~Bullet()
	{
		kill();
	}

	//void advance();
	void fire(const Point &pt, float rotation, const Velocity &velocity);
	void draw();
	void kill();
	void advance();

private:
	int count;
	int rotation;

};

#endif /* bullet_h */

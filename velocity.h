#ifndef VELOCITY_H
#define VELOCITY_H


// Put your velocity class here, or overwrite this file with your own
// velocity class from the previous project

#include "point.h"
#include <cmath>

#define d2r(angle) ((M_PI / 180) * angle)

class Velocity
{
private:
	float dX;
	float dY;
   int size;
   float angle;

public:
	Velocity()
	{
		dX = 0.0;
		dY = 0.0;
	}
	Velocity(float dX, float dY)
	{
		setDx(dX);
		setDy(dY);
	}

	float getDx() const { return dX; }
	float getDy() const { return dY; }

	void setDx(float dX) { this->dX = dX; }
	void setDy(float dY) { this->dY = dY; }

   void setMagAndDirection(int size, float angle);

	void add(const Velocity & velocity);
	void addDx(float dX) { setDx(getDx() + dX); }
	void addDy(float dY) { setDy(getDy() + dY); }
};


#endif /* velocity_h */

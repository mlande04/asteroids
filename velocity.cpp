#include "velocity.h"


// Put your velocity methods here
#include <iostream>
using namespace std;

/**********************************************************
* Function: add
* Purpose: Adds speed and direction to the flying objects.
***********************************************************/
void Velocity::add(const Velocity & velocity)
{
	dX += velocity.dX;
	dY += velocity.dY;

}

/********************************************************
* Velocity :: setMagAndDirection
* Purpose: sets the size and direction of moving objects
********************************************************/
void Velocity::setMagAndDirection(int size, float angle)
{
   this->size = size;
   this->angle = angle;

   dX = -cos(d2r(angle)) * size;
   dY = sin(d2r(angle)) * size; 
}

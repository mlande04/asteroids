/********************************************
* File: Ship
* Purpose: define Ship class methods
********************************************/
#include "ship.h"

// Put your ship methods here
void Ship :: moveRight()
{
   this->rotation += ROTATE_AMOUNT;
}

void Ship :: moveLeft()
{
   this->rotation -= ROTATE_AMOUNT;
}

void Ship :: addVelocity()
{
	velocity.addDy(cos(3.14159 / 180.0 * rotation) + THRUST_AMOUNT);
    velocity.addDx(-sin(3.14159 / 180.0 * rotation) + THRUST_AMOUNT);
}

void Ship :: draw()
{
   bool move = false;
   getRotation();
   getPoint();
   drawShip(point, rotation, move);
}

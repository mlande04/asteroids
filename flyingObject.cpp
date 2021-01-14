#include "flyingObject.h"


// Put your FlyingObject method bodies here

/**************************************************
* Function: advance
* Purpose: Moves the flying objects on the screen.
**************************************************/
void FlyingObject::advance()
{
	point.addX(velocity.getDx());
	point.addY(velocity.getDy());
	
	if (point.getY() > yMax)
		point.setY(yMin);
	if (point.getY() < yMin)
		point.setY(yMax);
	if (point.getX() > xMax)
		point.setX(xMin);
	if (point.getX() < xMin)
		point.setX(xMax);
}

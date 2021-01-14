#include "bullet.h"

// Put your bullet methods here
void Bullet::advance()
{
   // advance bullet position
   point.addX(velocity.getDx() + BULLET_SPEED);
   point.addY(velocity.getDy() + BULLET_SPEED);
   
   // check for bounds
   	if (point.getY() > yMax)
		point.setY(yMin);
	if (point.getY() < yMin)
		point.setY(yMax);
	if (point.getX() > xMax)
		point.setX(xMin);
	if (point.getX() < xMin)
		point.setX(xMax);
   
   // count for life of bullet
   count++;
}

void Bullet::fire(const Point &pt, float rotation, const Velocity &velocity)
{
   this->point = point;
   this->rotation = rotation;

   this->velocity.addDx(cos(D2R(rotation + 90)) * BULLET_SPEED);
   this->velocity.addDy(sin(D2R(rotation + 90)) * BULLET_SPEED);
}

void Bullet::draw()
{
   // draw bullets
   bool move = false;
   getPoint();
   drawDot(point);
}

void Bullet::kill()
{
	if (count > 40)
		!isAlive();
}
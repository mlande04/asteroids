/***************************
* File: flyingObject.h
***************************/

#ifndef flyingObject_h
#define flyingObject_h

#include "velocity.h"
#include "point.h"
#include "uiDraw.h"
#include <cmath>

#define D2R(angle) ((M_PI / 180) * angle)

#define xMin -200
#define xMax 200
#define yMin -200
#define yMax 200

// Put your FlyingObject class here

class FlyingObject
{
protected:
	Point point;
	Velocity velocity;
	bool alive;
	int size;

public:
	FlyingObject() : point(0, 0), velocity(0.0, 0.0)
	{
		point.setX(0.0);
		point.setY(0.0);
		velocity.setDx(0.0);
		velocity.setDy(0.0);
	}
   FlyingObject(Point pt, Velocity vel, bool alive)
   {
      setPoint(pt);
      setVelocity(vel);
      alive = true;
   }
	virtual ~FlyingObject() {}

	Point getPoint() const { return point; }
	Velocity getVelocity() const { return velocity; }

	void setPoint(const Point & point) { this->point = point; }
	void setVelocity(const Velocity & velocity)
	{
		this->velocity = velocity;
	}

	void setSize(int size) { this->size = size; }
	int getSize() const { return size; }
	void kill() { alive = false; }
	bool isAlive() const { return alive; }

	virtual void advance();
	virtual void draw() = 0;
};

#endif /* flyingObject_h */

/******************************
* File: ship.h
******************************/

#ifndef ship_h
#define ship_h

#include "flyingObject.h"
#include "uiDraw.h"

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5
//#define D2R(angle) ((M_PI / 180) * angle)

// Put your Ship class here
class Ship : public FlyingObject
{
public:
	Ship() : FlyingObject()
	{
      rotation = 0;
	}
	~Ship() {}

   void setRotation(int rotation) { this->rotation = rotation; }
   int getRotation() { return rotation; }
   
	void moveRight();
	void moveLeft();
	void addVelocity();
	virtual void draw();

protected:

private:
   int rotation;
};

#endif /* ship_h */

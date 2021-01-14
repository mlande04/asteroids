#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "flyingObject.h"
#include <list>

// Define the following classes here:
//   Rock
class Rocks : public FlyingObject
{
public:
	// constructors
   Rocks() : FlyingObject(), rotation(0) {}
   Rocks(Point point, Velocity vel, bool alive) : FlyingObject(point, vel, alive), rotation(0)
	{
		alive = true;
		setPoint(point);
		setVelocity(vel);
	}
	virtual ~Rocks() 
	{
		kill();
	}

	// rock mechanisms
	bool isHit();
	int getRotation() { return rotation; }
	void setRotation(int rotation) { this->rotation = rotation; }
	virtual void draw();
	virtual void rotate();
	virtual void splitAsteroid(std::list<Rocks*> &rocks) = 0;
	void kill() { alive = false; }
	
	Point getPoint() { return point; }

protected:
	bool hit;
	int radius;
	bool alive;
	int type;
	int rotation;
	
private:

};

//   BigRock
class BigRock :	public Rocks
{
public:
	// constructor
	BigRock(const Point &point) : Rocks()
	{
		setPoint(point);
		setSize(BIG_ROCK_SIZE);
		setRotation(BIG_ROCK_SPIN);
		float angle = random(0, 360);
		type = 1;
		velocity.setMagAndDirection(size, angle);
	}
	
	// rock logic
	virtual void draw();
	virtual void rotate();
   
	// big rock logic
	void splitAsteroid(std::list<Rocks*> &rocks);

private:
	int type;
	int rotation;
};

//   MediumRock
class MediumRock : public Rocks
{
public:
	// constructor
	MediumRock(const Point &point) : Rocks()
	{
		setPoint(point);
		setRotation(MEDIUM_ROCK_SPIN);
		setSize(MEDIUM_ROCK_SIZE);
		float angle = random(0, 360);
		type = 2;
		velocity.setMagAndDirection(size, angle);
	}

	// rock logic
	virtual void draw();
	virtual void rotate();
   
	// med rock logic
	void splitAsteroid(std::list<Rocks*> &rocks);

private:
	int type;
	int rotation;
	int radius;

};

//   SmallRock
class SmallRock : public Rocks
{
public:
	// constructor
	SmallRock(const Point &point) : Rocks()
	{
		setPoint(point);
		setRotation(SMALL_ROCK_SPIN);
		setSize(SMALL_ROCK_SIZE);
		float angle = random(0, 360);
		velocity.setMagAndDirection(size, angle);
		type = 3;
	}

	// rock logic
	virtual void draw();
	virtual void rotate();
	virtual void splitAsteroid(std::list<Rocks*> &rocks);

private:
	int type;

};


#endif /* rocks_h */

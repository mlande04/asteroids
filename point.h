/***********************************************************************
 * Header File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ************************************************************************/


#ifndef POINT_H
#define POINT_H

#include <iostream>

#define bounds 5
#define xMin -200
#define xMax 200
#define yMin -200
#define yMax 200

/*********************************************
 * POINT
 * A single position.  
 *********************************************/
class Point
{
public:
   // constructors
   Point()            : x(0.0), y(0.0) {}
   Point(bool check)  : x(0.0), y(0.0) {}
   Point(float x, float y);

   // getters
   float getX()       const { return x;              }
   float getY()       const { return y;              }
   bool getCheck()    const { return check;          }

   // setters
   void setX(float x);
   void setY(float y);
   void addX(float dx)      { setX(getX() + dx);     }
   void addY(float dy)      { setY(getY() + dy);     }
   void setCheck(bool check) { this->check = checkBounds(); }

   // check for point out of bounds
   bool checkBounds();

private:
   float x;           // horizontal position
   float y;           // vertical position
   bool check;
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Point & pt);
std::istream & operator >> (std::istream & in,        Point & pt);

#endif // POINT_H

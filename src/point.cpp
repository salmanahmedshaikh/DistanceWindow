#include "point.h"
//using namespace std;


Point::Point()
{
    //ctor
}

/*
Point::Point():xCOORD(0), yCOORD(0)
{
   //default constructor
   //does nothing
}
*/

Point::Point(double x, double y)
{
    // x = latitude
    // y = longitude
    xCOORD = x;
    yCOORD = y;
}

Point::~Point()
{
    //dtor
}

//MUTATOR FUNCTIONS
void Point::SetX(double x)
{
    xCOORD = x;
}
void Point::SetY(double y)
{
    yCOORD = y;
}

//ACCESSOR FUNCTIONS
double Point::GetX()
{
    return xCOORD;
}
double Point::GetY()
{
    return yCOORD;
}

// Print the point on the stream.  The class ostream is a base class
// for output streams of various types.
void Point::print(std::ostream &strm)
{
    strm << "(" << xCOORD << "," << yCOORD << ")";
}

bool Point::equals(Point p)
{
    if(xCOORD == p.GetX() && yCOORD == p.GetY())
        return true;
    else
        return false;
}

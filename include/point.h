#pragma once
#include "stdafx.h"
#include<fstream>

class Point
{
    public:
        //Default constructor
        double xCOORD, yCOORD;
        Point();
        Point(double x, double y);
        virtual ~Point();
        /*******Member Fucntions*******/
        //Accessors
        double GetX();
        double GetY();
        //Mutators
        void SetX(double x);
        void SetY(double Y);

        void print(std::ostream &strm);
        bool equals(Point p);

        // For unordered_map
        bool operator==(const Point &other) const
        {
            return (xCOORD == other.xCOORD && yCOORD == other.yCOORD);
        }

    private:
        // x = latitude
        // y = longitude
        //double xCOORD, yCOORD;
};


namespace std
{

  template <>
  struct hash<Point>
  {
    std::size_t operator()(const Point& p) const
    {
      using std::size_t;
      using std::hash;
      //using std::double

      // Compute individual hash values for first and second and combine them using XOR and bit shifting:

      return ((hash<double>()(p.xCOORD) ^ (hash<double>()(p.yCOORD) << 1)) >> 1);
    }
  };

}

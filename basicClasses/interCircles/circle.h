#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include "point.h" 

class Circle{
 private:
  Point center;
  const double radius;
 public:
  Circle (Point _center, double _radius): center(_center),  radius(_radius) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
#endif

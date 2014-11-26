#include "circle.h"
#include <math.h>

void Circle::move(double dx, double dy){
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle){
  double cirDist = center.distanceFrom(otherCircle.center);
  double firstRad = radius;
  double secondRad = otherCircle.radius;
  double cirArea = 0.0;
  if (cirDist == 0){
    if (firstRad>secondRad){
      return (pow(secondRad,2)*M_PI);
    }
    return (pow(firstRad,2)*M_PI);
  }
  if (firstRad == 0 || secondRad == 0){
    return cirArea;
  }
  if (secondRad > (firstRad + cirDist)){
    return (pow(firstRad,2)*M_PI);
  }
  if (firstRad > (secondRad + cirDist)){
    return (pow(secondRad,2)*M_PI);
  }
  if (cirDist >= (firstRad + secondRad)){
    return cirArea;
  }
  else{
  cirArea = pow(firstRad,2)*acos((pow(cirDist,2)+pow(firstRad,2)-pow(secondRad,2))/(2*cirDist*firstRad))+pow(secondRad,2)*acos((pow(cirDist,2)+pow(secondRad,2)-pow(firstRad,2))/(2*cirDist*secondRad))-0.5*sqrt((-cirDist+firstRad+secondRad)*(cirDist+firstRad-secondRad)*(cirDist-firstRad+secondRad)*(cirDist+firstRad+secondRad));
  }
  return cirArea;
}

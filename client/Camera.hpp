#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "Vector.hpp"

class Camera
{
public:
  Camera(const Point& pos_, double dist_): pos(pos_), dist(dist_)
  {}
  Point pos;
  double dist;
};

#endif

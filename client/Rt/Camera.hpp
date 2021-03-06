#ifndef _RT_CAMERA_HPP_
#define _RT_CAMERA_HPP_

#include "Vector.hpp"

namespace Rt
{

  class Camera
  {
  public:
    Camera(const Point& pos_, double dist_): pos(pos_), dist(dist_)
    {}
    Point pos;
    double dist;
  };

}

#endif

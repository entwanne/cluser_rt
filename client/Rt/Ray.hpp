#ifndef _RAY_HPP_
#define _RAY_HPP_

#include "Vector.hpp"

namespace Rt
{

  class Ray
  {
  public:
    Ray(const Point& src_, const Vector& dir_): src(src_), dir(dir_)
    {}
    Point point(double k) const
    {
      return Point(src.x + k * dir.x,
		   src.y + k * dir.y,
		   src.z + k * dir.z);
    }
    Point src;
    Vector dir;
  };

}

#endif

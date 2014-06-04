#include "shadow.hpp"
#include "../../utils/math.hpp"

using namespace Rt;
using namespace Rt::Lights;

#include <iostream>

bool Rt::Lights::shadow(Scene* scene, const Point& lum_pos, const Intersection& inter)
{
  Point point = inter.ray.point(inter.k);
  Vector to_obj = point - lum_pos;
  Intersection s = scene->intersect(Ray(lum_pos, to_obj));
  if (s.object != inter.object)
    return true;
  return (s.k < 1 - EPSILON);
}

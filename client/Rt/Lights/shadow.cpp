#include "shadow.hpp"

using namespace Rt;
using namespace Rt::Lights;

bool Rt::Lights::shadow(Scene* scene, const Point& lum_pos, const Intersection& inter)
{
  Point point = inter.ray.point(inter.k);
  Vector to_obj = point - lum_pos;
  Intersection s = scene->intersect(Ray(lum_pos, to_obj));
  return (s.object != inter.object);
}

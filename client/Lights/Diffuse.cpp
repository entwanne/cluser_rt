#include "Diffuse.hpp"
#include "../scene.hpp"

using namespace Rt;
using namespace Rt::Lights;

int Diffuse::color_at(const Intersection& inter) const
{
  return inter.object->color & color;
}

double Diffuse::intensity_at(const Intersection& inter) const
{
  Point point = inter.ray.point(inter.k);
  Vector to_obj(point.x - pos.x, point.y - pos.y, point.z - pos.z);
  Intersection shadow = scene->intersect(Ray(pos, to_obj));
  if (shadow.object != inter.object)
    return 0;
  Vector normal = inter.normal();
  Vector to_light(pos.x - point.x, pos.y - point.y, pos.z - point.z);
  double cos_angle = (normal * to_light) / (normal.norm() * to_light.norm());
  if (cos_angle < 0)
    cos_angle = 0;
  return (intensity * cos_angle);
}

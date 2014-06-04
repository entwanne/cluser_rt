#include "Diffuse.hpp"
#include "../Scene.hpp"
#include "shadow.hpp"

using namespace Rt;
using namespace Rt::Lights;

int Diffuse::color_at(const Intersection& inter) const
{
  return inter.color & color;
}

double Diffuse::intensity_at(const Intersection& inter) const
{
  if (shadow(scene, pos, inter))
    return 0;
  Point point = inter.ray.point(inter.k);
  Vector normal = inter.normal();
  Vector to_light = pos - point;
  double cos_angle = (normal * to_light) / (normal.norm() * to_light.norm());
  if (cos_angle < 0)
    cos_angle = 0;
  return (intensity * cos_angle);
}

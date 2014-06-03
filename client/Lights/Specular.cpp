#include "Specular.hpp"
#include "../scene.hpp"

using namespace Rt;
using namespace Rt::Lights;

int Specular::color_at(const Intersection&) const
{
  return color;
}

// Assume that inter.object has a specularity of 1
double Specular::intensity_at(const Intersection& inter) const
{
  Point point = inter.ray.point(inter.k);
  Vector to_obj(point.x - pos.x, point.y - pos.y, point.z - pos.z);
  Intersection shadow = scene->intersect(Ray(pos, to_obj));
  if (shadow.object != inter.object)
    return 0;
  Vector normal = inter.normal();
  Vector to_light(pos.x - point.x, pos.y - point.y, pos.z - point.z);
  normal = (1. / normal.norm()) * normal;
  to_light = (1. / to_light.norm()) * to_light;
  Vector r = (2. * (normal * to_light)) * normal - to_light;
  double cos_angle = -(r * inter.ray.dir) / (r.norm() * inter.ray.dir.norm());
  double k;
  if (cos_angle <= 0)
    k = 0;
  else
    {
      k = cos_angle;
      for (int i = 0; i < 5; ++i)
	k *= cos_angle;
    }
  return (intensity * k);
}

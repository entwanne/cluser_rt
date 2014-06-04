#include "Specular.hpp"
#include "../Scene.hpp"
#include "shadow.hpp"

using namespace Rt;
using namespace Rt::Lights;

int Specular::color_at(const Intersection&) const
{
  return color;
}

// Assume that inter.object has a specularity of 1
double Specular::intensity_at(const Intersection& inter) const
{
  if (shadow(scene, pos, inter))
    return 0;
  Point point = inter.ray.point(inter.k);
  Vector normal = inter.normal();
  Vector to_light = pos - point;
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

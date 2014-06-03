#include "Sphere.hpp"
#include "../Polynome.hpp"

using namespace Rt;
using namespace Rt::Objects;

double Sphere::intersect(const Ray& ray_) const
{
  Ray ray = Ray(inv_matrix * ray_.src, inv_matrix * ray_.dir);
  Polynome< 2 > eq({SQR(ray.dir),
	2 * (ray.src * ray.dir),
	SQR(ray.src) - 1
	});
  return polynome_min_positive_root(eq);
}

Vector Sphere::normal(const Point& p) const
{
  return Vector(p.x, p.y, p.z);
}

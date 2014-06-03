#include "Cylinder.hpp"
#include "../Polynome.hpp"

double Cylinder::intersect(const Ray& ray_) const
{
  Ray ray = Ray(inv_matrix * ray_.src, inv_matrix * ray_.dir);
  Polynome< 2 > eq({SQR(ray.dir.x) + SQR(ray.dir.y),
	2 * (ray.src.x * ray.dir.x + ray.src.y * ray.dir.y),
	  SQR(ray.src.x) + SQR(ray.src.y) - 1
	});
  return polynome_min_positive_root(eq);
}

Vector Cylinder::normal(const Point& p) const
{
  return Vector(p.x, p.y, 0);
}

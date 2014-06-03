#include "Cone.hpp"
#include "../Polynome.hpp"

double Cone::intersect(const Ray& ray_) const
{
  Ray ray = Ray(inv_matrix * ray_.src, inv_matrix * ray_.dir);
  Polynome< 2 > eq({SQR(ray.dir.x) + SQR(ray.dir.y) - coef * SQR(ray.dir.z),
	2 * (ray.src.x * ray.dir.x + ray.src.y * ray.dir.y - coef * ray.src.z * ray.dir.z),
	SQR(ray.src.x) + SQR(ray.src.y) - coef * SQR(ray.src.z)
	});
  return polynome_min_positive_root(eq);
}

Vector Cone::normal(const Point& p) const
{
  Vector n(p.x, p.y, -coef * p.z);
  double norm = n.norm();
  n.x /= norm;
  n.y /= norm;
  n.z /= norm;
  return n;
}

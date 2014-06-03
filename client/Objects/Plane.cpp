#include "Plane.hpp"

double Plane::intersect(const Ray& ray_) const
{
  Ray ray = Ray(inv_matrix * ray_.src, inv_matrix * ray_.dir);
  if (!ray.dir.z)
    return -1;
  return -ray.src.z / ray.dir.z;
}

Vector Plane::normal(const Point&) const
{
  return Vector(0., 0., 1.);
}

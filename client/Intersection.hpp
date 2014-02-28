#ifndef _INTERSECTION_HPP_
#define _INTERSECTION_HPP_

class NoIntersection
{};

class Intersection
{
public:
  Intersection(const Ray& ray_, Object* object_ = 0, double k_ = 0): ray(ray_), object(object_), k(k_)
  {}
  Point point() const
  {
    if (!object)
      throw NoIntersection();
    return ray.point(k);
  }
  Vector normal() const
  {
    if (!object)
      throw NoIntersection();
    Vector n = object->normal(local_coords(point()));
    if (n * (local_coords(ray.dir)) > 0)
      n = Vector(-n.x, -n.y, -n.z);
    return global_coords(n);
  }
  template < typename T >
  inline T global_coords(const T& v) const
  {
    return object->matrix * v;
  }
  template < typename T >
  inline T local_coords(const T& v) const
  {
    return object->inv_matrix * v;
  }
  inline operator bool() const
  {
    return (object ? true : false);
  }
  const Ray& ray;
  Object* object;
  double k;
};

#endif

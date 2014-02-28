#ifndef _OBJECTS_HPP_
#define _OBJECTS_HPP_

class Plane: public Object
{
public:
  Plane(int color, const matrix_t& matrix, const matrix_t& inv_matrix): Object(color, matrix, inv_matrix)
  {}
  double intersect(const Ray& ray_) const
  {
    Ray ray = Ray(inv_matrix * ray_.src, inv_matrix * ray_.dir);
    if (!ray.dir.z)
      return -1;
    return -ray.src.z / ray.dir.z;
  }
  Vector normal(const Point&) const
  {
    return Vector(0., 0., 1.);
  }
};

class Sphere: public Object
{
public:
  Sphere(int color, const matrix_t& matrix, const matrix_t& inv_matrix): Object(color, matrix, inv_matrix)
  {}
  double intersect(const Ray& ray_) const
  {
    Ray ray = Ray(inv_matrix * ray_.src, inv_matrix * ray_.dir);
    Polynome< 2 > eq({SQR(ray.dir),
	  2 * (ray.src * ray.dir),
	  SQR(ray.src) - 1
      });
    return polynome_min_positive_root(eq);
  }
  Vector normal(const Point& p) const
  {
    return Vector(p.x, p.y, p.z);
  }
};

class Cylinder: public Object
{
public:
  Cylinder(int color, const matrix_t& matrix, const matrix_t& inv_matrix): Object(color, matrix, inv_matrix)
  {}
  double intersect(const Ray& ray_) const
  {
    Ray ray = Ray(inv_matrix * ray_.src, inv_matrix * ray_.dir);
    Polynome< 2 > eq({SQR(ray.dir.x) + SQR(ray.dir.y),
	  2 * (ray.src.x * ray.dir.x + ray.src.y * ray.dir.y),
	  SQR(ray.src.x) + SQR(ray.src.y) - 1
      });
    return polynome_min_positive_root(eq);
  }
  Vector normal(const Point& p) const
  {
    return Vector(p.x, p.y, 0);
  }
};

class Cone: public Object
{
public:
  Cone(double angle, int color, const matrix_t& matrix, const matrix_t& inv_matrix): Object(color, matrix, inv_matrix)
  {
    coef = tan(angle);
    coef = SQR(coef);
  }
  double intersect(const Ray& ray_) const
  {
    Ray ray = Ray(inv_matrix * ray_.src, inv_matrix * ray_.dir);
    Polynome< 2 > eq({SQR(ray.dir.x) + SQR(ray.dir.y) - coef * SQR(ray.dir.z),
	  2 * (ray.src.x * ray.dir.x + ray.src.y * ray.dir.y - coef * ray.src.z * ray.dir.z),
	  SQR(ray.src.x) + SQR(ray.src.y) - coef * SQR(ray.src.z)
      });
    return polynome_min_positive_root(eq);
  }
  Vector normal(const Point& p) const
  {
    Vector n(p.x, p.y, -coef * p.z);
    double norm = n.norm();
    n.x /= norm;
    n.y /= norm;
    n.z /= norm;
    return n;
  }
  double coef;
};

#endif

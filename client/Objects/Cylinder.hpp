#ifndef _CYLINDER_HPP_
#define _CYLINDER_HPP_

#include "Object.hpp"

class Cylinder: public Object
{
public:
  Cylinder(int color, const matrix_t& matrix, const matrix_t& inv_matrix): Object(color, matrix, inv_matrix)
  {}
  double intersect(const Ray& ray_) const;
  Vector normal(const Point& p) const;
};

#endif

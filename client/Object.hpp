#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

class Object
{
public:
  Object(int color_, const matrix_t& matrix_, const matrix_t& inv_matrix_): color(color_), matrix(matrix_), inv_matrix(inv_matrix_)
  {}
  virtual double intersect(const Ray&) const = 0;
  // Unit vector of normal in simple coords
  virtual Vector normal(const Point&) const = 0;
  int color;
  matrix_t matrix, inv_matrix;
};

#endif

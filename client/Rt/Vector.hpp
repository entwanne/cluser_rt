#ifndef _RT_VECTOR_HPP_
#define _RT_VECTOR_HPP_

#include <cmath>
#include "../utils/math.hpp"

namespace Rt
{

  class Vector
  {
  public:
    Vector(double x_, double y_, double z_): x(x_), y(y_), z(z_), w(0)
    {}
    inline double operator*(const Vector& o) const
    {
      return x * o.x + y * o.y + z * o.z;
    }
    inline double norm() const
    {
      return sqrt(SQR(*this));
    }
    double x, y, z, w;
  protected:
    Vector(double x_, double y_, double z_, double w_): x(x_), y(y_), z(z_), w(w_)
    {}
  };

  class Point: public Vector
  {
  public:
    Point(double x_, double y_, double z_): Vector(x_, y_, z_, 1.)
    {}
  };

}

template < typename V >
V operator*(const V& v, double k)
{
  return V(k * v.x, k * v.y, k * v.z);
}
template < typename V >
V operator*(double k, const V& v)
{
  return operator*(v, k);
}

template < typename V >
V operator+(const V& v1, const V& v2)
{
  return V(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
template < typename V >
V operator-(const V& v1, const V& v2)
{
  return V(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

#endif

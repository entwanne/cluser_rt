#ifndef _RT_VECTOR_HPP_
#define _RT_VECTOR_HPP_

#include <cmath>
#include "../utils/math.hpp"

namespace Rt
{

  class _Vector
  {
  public:
    inline double operator*(const _Vector& rhs) const
    {
      return x * rhs.x + y * rhs.y + z * rhs.z;
    }
    inline double norm() const
    {
      return sqrt(SQR(*this));
    }
    double x, y, z, w;
  protected:
    _Vector(double x_, double y_, double z_, double w_): x(x_), y(y_), z(z_), w(w_)
    {}
  };

  // class Vector
  // {
  // public:
  //   Vector(double x_, double y_, double z_): x(x_), y(y_), z(z_), w(0)
  //   {}
  //   inline double operator*(const Vector& o) const
  //   {
  //     return x * o.x + y * o.y + z * o.z;
  //   }
  //   inline double norm() const
  //   {
  //     return sqrt(SQR(*this));
  //   }
  //   double x, y, z, w;
  // protected:
  //   Vector(double x_, double y_, double z_, double w_): x(x_), y(y_), z(z_), w(w_)
  //   {}
  // };

  class Vector: public _Vector
  {
  public:
    Vector(double x, double y, double z): _Vector(x, y, z, 0)
    {}
  };

  class Point: public _Vector
  {
  public:
    Point(double x, double y, double z): _Vector(x, y, z, 1.)
    {}
  };

}

Rt::Vector operator*(const Rt::Vector& v, double k);
Rt::Vector operator*(double k, const Rt::Vector& v);

Rt::Vector operator+(const Rt::Vector& v1, const Rt::Vector& v2);
Rt::Point operator+(const Rt::Point& p, const Rt::Vector& v);
Rt::Point operator+(const Rt::Vector& v, const Rt::Point& p);

Rt::Vector operator-(const Rt::Vector& v1, const Rt::Vector& v2);
Rt::Vector operator-(const Rt::Point& p1, const Rt::Point& p2);

#endif

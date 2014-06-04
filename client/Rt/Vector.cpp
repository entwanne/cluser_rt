#include "Vector.hpp"

using namespace Rt;

Vector operator*(const Vector& v, double k)
{
  return Vector(k * v.x, k * v.y, k * v.z);
}
Vector operator*(double k, const Vector& v)
{
  return operator*(v, k);
}

Vector operator+(const Vector& v1, const Vector& v2)
{
  return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
Point operator+(const Point& p, const Vector& v)
{
  return Point(p.x + v.x, p.y + v.y, p.z + v.z);
}
Point operator+(const Vector& v, const Point& p)
{
  return operator+(p, v);
}

Vector operator-(const Vector& v1, const Vector& v2)
{
  return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
Vector operator-(const Point& p1, const Point& p2)
{
  return Vector(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

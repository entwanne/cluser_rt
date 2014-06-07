#ifndef _RT_OBJECTS_SPHERE_HPP_
#define _RT_OBJECTS_SPHERE_HPP_

#include <cmath>
#include "Object.hpp"

namespace Rt
{
  namespace Objects
  {

    class Sphere: public Object
    {
    public:
      Sphere(int texture_id, const matrix_t& matrix, const matrix_t& inv_matrix, Scene* scene): Object(texture_id, matrix, inv_matrix, scene)
      {}
      double intersect(const Ray& ray_) const;
      Vector normal(const Point& p) const;
      virtual std::tuple<double, double> coords2d(const Point& p) const
      {
	double u;
	u = acos(p.y);
	if (p.x < 0)
	  u = -u;
	return std::make_tuple(u, p.z);
      }
    };

  }
}

#endif

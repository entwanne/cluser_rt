#ifndef _RT_OBJECTS_SPHERE_HPP_
#define _RT_OBJECTS_SPHERE_HPP_

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
      virtual std::tuple<double, double> coords2d(const Point&) const
      {
	return std::make_tuple(0., 0.);
      }
    };

  }
}

#endif

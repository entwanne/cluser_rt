#ifndef _RT_OBJECTS_PLANE_HPP_
#define _RT_OBJECTS_PLANE_HPP_

#include "Object.hpp"

namespace Rt
{
  namespace Objects
  {

    class Plane: public Object
    {
    public:
      Plane(int texture_id, const matrix_t& matrix, const matrix_t& inv_matrix, Scene* scene): Object(texture_id, matrix, inv_matrix, scene)
      {}
      double intersect(const Ray& ray_) const;
      Vector normal(const Point&) const;
      virtual std::tuple<double, double> coords2d(const Point&) const
      {
	return std::make_tuple(0., 0.);
      }
    };

  }
}

#endif

#ifndef _PLANE_HPP_
#define _PLANE_HPP_

#include "Object.hpp"

namespace Rt
{
  namespace Objects
  {

    class Plane: public Object
    {
    public:
      Plane(int color, const matrix_t& matrix, const matrix_t& inv_matrix, Scene* scene): Object(color, matrix, inv_matrix, scene)
      {}
      double intersect(const Ray& ray_) const;
      Vector normal(const Point&) const;
    };

  }
}

#endif

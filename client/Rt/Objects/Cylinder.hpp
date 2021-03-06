#ifndef _RT_OBJECTS_CYLINDER_HPP_
#define _RT_OBJECTS_CYLINDER_HPP_

#include "Object.hpp"

namespace Rt
{
  namespace Objects
  {

    class Cylinder: public Object
    {
    public:
      Cylinder(int color, const matrix_t& matrix, const matrix_t& inv_matrix, Scene* scene): Object(color, matrix, inv_matrix, scene)
      {}
      double intersect(const Ray& ray_) const;
      Vector normal(const Point& p) const;
    };

  }
}

#endif

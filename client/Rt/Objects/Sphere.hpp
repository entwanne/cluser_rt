#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include "Object.hpp"

namespace Rt
{
  namespace Objects
  {

    class Sphere: public Object
    {
    public:
      Sphere(int color, const matrix_t& matrix, const matrix_t& inv_matrix, Scene* scene): Object(color, matrix, inv_matrix, scene)
      {}
      double intersect(const Ray& ray_) const;
      Vector normal(const Point& p) const;
    };

  }
}

#endif

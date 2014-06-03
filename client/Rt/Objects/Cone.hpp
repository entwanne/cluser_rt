#ifndef _CONE_HPP_
#define _CONE_HPP_

#include <cmath>
#include "Object.hpp"
#include "../../utils.hpp"

namespace Rt
{
  namespace Objects
  {

    class Cone: public Object
    {
    public:
      Cone(double angle, int color, const matrix_t& matrix, const matrix_t& inv_matrix, Scene* scene): Object(color, matrix, inv_matrix, scene)
      {
	coef = tan(angle);
	coef = SQR(coef);
      }
      double intersect(const Ray& ray_) const;
      Vector normal(const Point& p) const;
      double coef;
    };

  }
}

#endif

#ifndef _RT_OBJECTS_CONE_HPP_
#define _RT_OBJECTS_CONE_HPP_

#include <cmath>
#include "Object.hpp"
#include "../../utils/math.hpp"

namespace Rt
{
  namespace Objects
  {

    class Cone: public Object
    {
    public:
      Cone(double angle, int texture_id, const matrix_t& matrix, const matrix_t& inv_matrix, Scene* scene): Object(texture_id, matrix, inv_matrix, scene)
      {
	coef = tan(angle);
	coef = SQR(coef);
      }
      double intersect(const Ray& ray_) const;
      Vector normal(const Point& p) const;
      virtual std::tuple<double, double> coords2d(const Point& p) const
      {
	double u;
	if (p.z == 0)
	  u = 0;
	else
	  {
	    u = acos(p.y / p.z);
	    if (p.x < 0)
	      u = -u;
	  }
	return std::make_tuple(u, p.z);
      }
      double coef;
    };

  }
}

#endif

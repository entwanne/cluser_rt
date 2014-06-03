#ifndef _DIFFUSE_HPP_
#define _DIFFUSE_HPP_

#include "Light.hpp"

namespace Rt
{
  namespace Lights
  {

    class Diffuse : public Light
    {
    public:
      Diffuse(double x, double y, double z, int color, double intensity, Scene* scene) : Light(color, intensity, scene), pos(x, y, z)
      {}
      int color_at(const Intersection& inter) const;
      double intensity_at(const Intersection& inter) const;
      Point pos;
    };

  }
}

#endif

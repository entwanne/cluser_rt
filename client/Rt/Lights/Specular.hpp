#ifndef _SPECULAR_HPP_
#define _SPECULAR_HPP_

#include "Light.hpp"

namespace Rt
{
  namespace Lights
  {

    class Specular : public Light
    {
    public:
      Specular(double x, double y, double z, int color, double intensity, Scene* scene) : Light(color, intensity, scene), pos(x, y, z)
      {}
      int color_at(const Intersection&) const;
      double intensity_at(const Intersection& inter) const;
      Point pos;
    };

  }
}

#endif

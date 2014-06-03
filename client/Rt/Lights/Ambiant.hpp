#ifndef _RT_LIGHTS_AMBIANT_HPP_
#define _RT_LIGHTS_AMBIANT_HPP_

#include "Light.hpp"

namespace Rt
{
  namespace Lights
  {

    class Ambiant : public Light
    {
    public:
      Ambiant(int color, double intensity, Scene* scene) : Light(color, intensity, scene)
      {}
      int color_at(const Intersection& inter) const;
      double intensity_at(const Intersection&) const;
    };

  }
}

#endif

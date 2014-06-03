#ifndef _AMBIANT_HPP_
#define _AMBIANT_HPP_

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

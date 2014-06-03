#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include "../Intersection.hpp"

namespace Rt
{
  class Scene;

  namespace Lights
  {

    class Light
    {
    public:
      Light(int color_, double intensity_, Scene* scene_) : color(color_), intensity(intensity_), scene(scene_)
      {}
      virtual int color_at(const Intersection&) const = 0;
      virtual double intensity_at(const Intersection&) const = 0;
      int color;
      double intensity;
      Scene* scene;
    };

  }
}

#endif

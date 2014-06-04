#ifndef _RT_LIGHT_SHADOW_HPP_
#define _RT_LIGHT_SHADOW_HPP_

#include "../Scene.hpp"
#include "../Intersection.hpp"

namespace Rt
{
  namespace Lights
  {

    bool shadow(Scene* scene, const Point& lum_pos, const Intersection& inter);

  }
}

#endif

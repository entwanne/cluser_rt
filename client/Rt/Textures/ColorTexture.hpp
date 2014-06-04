#ifndef _RT_TEXTURES_COLORTEXTURE_HPP_
#define _RT_TEXTURES_COLORTEXTURE_HPP_

#include "Texture.hpp"

namespace Rt
{
  namespace Textures
  {

    class ColorTexture: public Texture
    {
    public:
      ColorTexture(int color_): color(color_) {}
      virtual inline int color_at(int, int) const
      {
	return color;
      }
      int color;
    };

  }
}

#endif

#ifndef _RT_TEXTURES_BICOLOR_HPP
#define _RT_TEXTURES_BICOLOR_HPP_

#include "Texture.hpp"

namespace Rt
{
  namespace Textures
  {

    // REPLACE BICOLOR BY BITEXTURE (ref to textures)

    class Bicolor: public Texture
    {
    public:
      Bicolor(int color1_, int color2_, bool vertical_): color1(color1_), color2(color2_), vertical(vertical_) {}
      virtual inline int color_at(double u, double v) const
      {
	if (vertical && v >= 0)
	  return color1;
	if (!vertical && u >= 0)
	  return color1;
	return color2;
      }
      int color1, color2;
      bool vertical;
    };

  }
}

#endif

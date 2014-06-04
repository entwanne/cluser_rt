#ifndef _RT_TEXTURES_TEXTURE_HPP_
#define _RT_TEXTURES_TEXTURE_HPP_

namespace Rt
{
  namespace Textures
  {

    class Texture
    {
    public:
      virtual int color_at(double x, double y) const = 0;
    };

  }
}

#endif

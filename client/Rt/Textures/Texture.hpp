#ifndef _RT_TEXTURES_TEXTURE_HPP_
#define _RT_TEXTURES_TEXTURE_HPP_

namespace Rt
{
  namespace Textures
  {

    class Texture
    {
    public:
      virtual int color_at(int x, int y) const = 0;
    };

  }
}

#endif

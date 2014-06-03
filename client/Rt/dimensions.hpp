#ifndef _RT_DIMENSIONS_HPP_
#define _RT_DIMENSIONS_HPP_

namespace Rt
{

  struct dim_t
  {
  public:
    dim_t(int width_, int height_): width(width_), height(height_)
    {}
    int width;
    int height;
  };

}

#endif

#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include "../Intersection.hpp"

class Light
{
public:
  Light(int color_, double intensity_) : color(color_), intensity(intensity_)
  {}
  virtual int color_at(const Intersection&) const = 0;
  virtual double intensity_at(const Intersection&) const = 0;
  int color;
  double intensity;
};

#endif

#ifndef _AMBIANT_HPP_
#define _AMBIANT_HPP_

#include "Light.hpp"

class Ambiant : public Light
{
public:
  Ambiant(int color, double intensity) : Light(color, intensity)
  {}
  int color_at(const Intersection& inter) const;
  double intensity_at(const Intersection&) const;
};

#endif

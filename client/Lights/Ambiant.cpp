#include "Ambiant.hpp"

int Ambiant::color_at(const Intersection& inter) const
{
  return inter.object->color & color;
}

double Ambiant::intensity_at(const Intersection&) const
{
  return intensity;
}

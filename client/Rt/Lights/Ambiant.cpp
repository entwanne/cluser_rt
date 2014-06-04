#include "Ambiant.hpp"

using namespace Rt;
using namespace Rt::Lights;

int Ambiant::color_at(const Intersection& inter) const
{
  return inter.color & color;
}

double Ambiant::intensity_at(const Intersection&) const
{
  return intensity;
}

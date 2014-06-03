#include <cmath>
#include "Polynome.hpp"

using namespace Rt;

template < >
void Polynome< 2 >::solve()
{
  double delta = SQR(_a[1]) - 4 * _a[0] * _a[2];
  if (delta < 0)
    return ;
  roots[0] = (-_a[1] - sqrt(delta)) / (2 * _a[0]);
  roots[1] = (-_a[1] + sqrt(delta)) / (2 * _a[0]);
  n_roots = 2;
}

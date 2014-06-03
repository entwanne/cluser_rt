#ifndef _POLYNOME_HPP_
#define _POLYNOME_HPP_

#include <array>
#include "utils.hpp"

template < int N >
class Polynome
{
public:
  Polynome(const std::array< double, N + 1 >& a) : _a(a), roots(), n_roots(0)
  {}
  void solve()
  {}
protected:
  std::array< double, N + 1 > _a;
public:
  std::array< double, N > roots;
  int n_roots;
};

template < typename T >
double polynome_min_positive_root(T& eq)
{
  double mink = 0;
  eq.solve();
  for (int i = 0; i < eq.n_roots; ++i)
    {
      double k = eq.roots[i];
      if (LESS_AND_POSITIVE(k, mink))
	mink = k;
    }
  return mink;
}

template < >
void Polynome< 2 >::solve();

#endif

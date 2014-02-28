#ifndef _POLYNOME_HPP_
#define _POLYNOME_HPP_

class NoRootExists
{};

template < int N >
class Polynome
{
public:
  Polynome(const std::array< double, N + 1 >& a) : _a(a), _roots(), _i(0)
  {}
  void solve()
  {}
  double next_root()
  {
    if (_i >= N)
      throw NoRootExists();
    return _roots[_i++];
  }
protected:
  std::array< double, N + 1 > _a;
  std::array< double, N > _roots;
  int _i;
};

template < >
void Polynome< 2 >::solve()
{
  double delta = SQR(_a[1]) - 4 * _a[0] * _a[2];
  if (delta < 0)
    throw NoRootExists();
  _roots[0] = (-_a[1] - sqrt(delta)) / (2 * _a[0]);
  _roots[1] = (-_a[1] + sqrt(delta)) / (2 * _a[0]);
}

template < typename T >
double polynome_min_positive_root(T& eq)
{
  double mink = 0;
  try
    {
      eq.solve();
      while (true)
  	{
  	  double k = eq.next_root();
	  if (LESS_AND_POSITIVE(k, mink))
  	    mink = k;
  	}
    }
  catch (const NoRootExists&)
    {}
  return mink;
}

#endif

#ifndef _MATHUTILS_HPP_
#define _MATHUTILS_HPP_

#define SQR(x) ((x) * (x))
#define LESS_AND_POSITIVE(a, b) ((a) > 0 && ((b) <= 0 || (a) < (b)))

template < typename T >
inline T max(T a)
{
  return a;
}

template < typename T, typename ... Args >
inline T max(T v, Args... args)
{
  T q = max(args...);
  return (v > q ? v : q);
}

#endif

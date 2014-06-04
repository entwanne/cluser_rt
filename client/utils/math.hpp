#ifndef _UTILS_MATH_HPP_
#define _UTILS_MATH_HPP_

#define SQR(x) ((x) * (x))
#define LESS_AND_POSITIVE(a, b) ((a) > 0 && ((b) <= 0 || (a) < (b)))
#define EPSILON 0.00001

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

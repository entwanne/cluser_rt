#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <array>

namespace Rt
{
  typedef std::array< std::array< double, 4 >, 4 > matrix_t;
}

template < typename V >
V operator*(const Rt::matrix_t& m, const V& v)
{
  V r(0, 0, 0);
  r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
  r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
  r.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
  r.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
  return r;
}

#endif

#ifndef _RT_COLOR_HPP_
#define _RT_COLOR_HPP_

namespace Rt
{

  class Color
  {
  public:
    Color(unsigned int r_, unsigned int g_, unsigned int b_): r(r_), g(g_), b(b_) {}
    Color(const Color& rhs): Color(rhs.r, rhs.g, rhs.b) {}
    Color(unsigned int c): Color((c / (256 * 256)) % 256, (c / 256) % 256, c % 256) {}

    Color& operator=(const Color& rhs)
    {
      r = rhs.r;
      g = rhs.g;
      b = rhs.b;
      return *this;
    }
    inline Color operator+(const Color& rhs) const
    {
      return Color(r + rhs.r, g + rhs.g, b + rhs.b);
    }
    Color& operator+=(const Color& rhs)
    {
      r += rhs.r;
      g += rhs.g;
      b += rhs.b;
      return *this;
    }
    inline Color operator*(double k) const
    {
      return Color(r * k, g * k, b * k);
    }
    Color& operator*=(double k)
    {
      r *= k;
      g *= k;
      b *= k;
      return *this;
    }

    unsigned int to_int() const
    {
      unsigned int r_ = r, g_ = g, b_ = b;
      unsigned int cmax = max(r_, g_, b_);
      if (cmax > 255)
	{
	  r_ = (r_ * 255) / cmax;
	  g_ = (g_ * 255) / cmax;
	  b_ = (b_ * 255) / cmax;
	}
      return r_ * 256 *256 + g_ * 256 + b_;
    }

    unsigned int r;
    unsigned int g;
    unsigned int b;
  };

}

inline Rt::Color operator*(double k, const Rt::Color& color)
{
  return color.operator*(k);
}

#endif

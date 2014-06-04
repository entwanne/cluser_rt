#ifndef _RT_COLOR_HPP_
#define _RT_COLOR_HPP_

#include <tuple>

namespace Rt
{

  using color_t = std::tuple<unsigned int, unsigned int, unsigned int>;

  inline color_t extract_color(unsigned int c)
  {
    return std::make_tuple((c / (256 * 256)) % 256,
			   (c / 256) % 256,
			   c % 256);
  }
  inline unsigned int compact_color(const color_t& t)
  {
    return std::get<0>(t) * 256 * 256 + std::get<1>(t) * 256 + std::get<2>(t);
  }

  class ColorAdder
  {
  public:
    ColorAdder(): color(0, 0, 0) {}

    void add(const color_t& c, double k = 1.)
    {
      std::get<0>(color) += std::get<0>(c) * k;
      std::get<1>(color) += std::get<1>(c) * k;
      std::get<2>(color) += std::get<2>(c) * k;
    }
    void add(int c, double k = 1.)
    {
      add(extract_color(c), k);
    }

    unsigned int value() const
    {
      color_t c(color);
      unsigned int cmax = max(std::get<0>(c), std::get<1>(c), std::get<2>(c));
      if (cmax > 255)
	{
	  std::get<0>(c) = (std::get<0>(c) * 255) / cmax;
	  std::get<1>(c) = (std::get<1>(c) * 255) / cmax;
	  std::get<2>(c) = (std::get<2>(c) * 255) / cmax;
	}
      return compact_color(c);
    }

    color_t color;
  };

}

#endif

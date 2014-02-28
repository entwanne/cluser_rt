#ifndef _CONSUMER_COLLECT_HPP_
#define _CONSUMER_COLLECT_HPP_

#include <tuple>

#include "Consumer.hpp"

// Collect read values from consumer into a tuple

template < typename ... Types >
struct s_collector;

template < typename T, typename ... Types >
struct s_collector< T, Types... >
{
  static std::tuple< T, Types... > collect(Consumer& consumer)
  {
    T val;
    consumer.read(val);
    return std::tuple_cat(std::tuple< T >(val), s_collector< Types... >::collect(consumer));
  }
};

template < >
struct s_collector< >
{
  static std::tuple< > collect(Consumer&)
  {
    return std::tuple< >();
  }
};

template < typename ... Types >
std::tuple< Types... > collect(Consumer& consumer)
{
  return s_collector< Types... >::collect(consumer);
}

#endif

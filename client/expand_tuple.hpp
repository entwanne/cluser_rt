#ifndef _EXPAND_TUPLE_HPP_
#define _EXPAND_TUPLE_HPP_

// Numeric sequences for unpacking tuples

template < int ... >
struct num_seq
{};

template < int N, int ... List >
struct gen_num_seq
{
  typedef typename gen_num_seq< N - 1, N - 1, List... >::type type;
};

template < int ... List >
struct gen_num_seq< 0, List... >
{
  typedef num_seq< List... > type;
};

template < typename R, typename C, typename ... TupleTypes, typename ... Args, int ... S >
static R _call_expand_tuple(C callable, const num_seq< S... >&, const std::tuple< TupleTypes... >& tuple, Args... args)
{
  return callable(std::get< S >(tuple)..., args...);
}

template < typename R, typename C, typename ... TupleTypes, typename ... Args >
R call_expand_tuple(C callable, const std::tuple< TupleTypes... >& tuple, Args... args)
{
  return _call_expand_tuple< R >(callable, typename gen_num_seq< sizeof...(TupleTypes) >::type(),
				 tuple, args...);
}

#endif

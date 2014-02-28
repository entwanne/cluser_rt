#ifndef _CONSTRUCTOR_CALLER_HPP_
#define _CONSTRUCTOR_CALLER_HPP_

template < typename RO, typename O >
class ConstructorCaller
{
public:
  template < typename... Args >
  RO* operator()(Args... args)
  {
    return new O(args...);
  }
};

#endif

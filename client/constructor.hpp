#ifndef _CONSTRUCTOR_HPP_
#define _CONSTRUCTOR_HPP_

template < typename O, typename RO=O >
class constructor
{
public:
  template < typename... Args >
  RO* operator()(Args... args)
  {
    return new O(args...);
  }
};

#endif

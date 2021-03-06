#ifndef _NETWORK_CONSUMER_HPP_
#define _NETWORK_CONSUMER_HPP_

#include <exception>

namespace Network
{

  class Consumer
  {
  public:
    class Exception : public std::exception
    {
    public:
      Exception(const char* msg) : _msg(msg)
      {}
      const char* what() const throw()
      {
	return _msg;
      }
    private:
      const char* _msg;
    };

    Consumer(const char* data, size_t size): _data(data), _size(size)
    {}
    template < typename T >
    void read(T& buff, size_t buff_size=static_cast<size_t>(~0))
    {
      if (buff_size == static_cast<size_t>(~0))
	buff_size = sizeof(T);
      if (buff_size > _size)
	throw Exception("End of stream reached");
      memcpy(&buff, _data, buff_size);
      _data += buff_size;
      _size -= buff_size;
    }
  private:
    const char* _data;
    size_t _size;
  };

}

#endif

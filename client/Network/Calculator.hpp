#ifndef _NETWORK_CALCULATOR_HPP_
#define _NETWORK_CALCULATOR_HPP_

#include <zmq.hpp>
#include <cstdlib>
#include <functional>

namespace Network
{

  template < typename Key >
  class Calculator
  {
  public:
    using calc_func_t = std::function<void* (Key, size_t&)>;
    using welcome_func_t = std::function<void (const char*, size_t)>;

    explicit Calculator(const std::string& conn, const calc_func_t& calc_func, const welcome_func_t& welcome_func): _context(1), _req(_context, ZMQ_REQ), _calc_func(calc_func), _welcome_func(welcome_func)
    {
      _req.connect(conn.c_str());
    }
    ~Calculator()
    {
      _req.close();
    }
    void start()
    {
      zmq::message_t msg;

      _req.send("hello", 5);
      _req.recv(&msg);
      _welcome_func(static_cast< const char* >(msg.data()), msg.size());

      while (true)
	{
	  _req.send("ready", 5);
	  _req.recv(&msg);

	  char status;
	  memcpy(&status, msg.data(), sizeof(status));
	  if (status != 0)
	    break ;

	  Key key;
	  memcpy(&key, static_cast< const char* >(msg.data()) + sizeof(status), sizeof(key));

	  size_t calc_size;
	  void* calc = _calc_func(key, calc_size);
	  zmq::message_t response(sizeof(char) + sizeof(Key) + calc_size);

	  memcpy(static_cast< char* >(response.data()), &status, sizeof(status));
	  memcpy(static_cast< char* >(response.data()) + sizeof(status), &key, sizeof(key));
	  memcpy(static_cast< char* >(response.data()) + sizeof(status) + sizeof(key), calc, calc_size);
	  _req.send(response.data(), sizeof(status) + sizeof(key) + calc_size);

	  _req.recv(&msg);
	  if (!memcmp(msg.data(), "end", 3))
	    break ;
	}
    }
  protected:
    zmq::context_t _context;
    zmq::socket_t _req;
    calc_func_t _calc_func;
    welcome_func_t _welcome_func;
  };

}

#endif

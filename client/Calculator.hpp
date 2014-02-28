#ifndef _CALCULATOR_HPP_
#define _CALCULATOR_HPP_

#include <zmq.hpp>
#include <cstdlib>

template < typename Key >
class Calculator
{
public:
  typedef void (*welcome_func_t)(const void*, size_t);
  explicit Calculator(const std::string& conn, void* (*calc_func)(Key, size_t&), void (*welcome_func)(const char*, size_t)): _context(1), _req(_context, ZMQ_REQ), _calc_func(calc_func), _welcome_func(welcome_func)
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
    // zmq::message_t response(sizeof(char) + sizeof(Key) + sizeof(Resp));

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

	// Resp calc = _calc_func(key);
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
  void* (*_calc_func)(Key, size_t&);
  void (*_welcome_func)(const char*, size_t);
};

#endif

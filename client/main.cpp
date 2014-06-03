#include "TraceClient.hpp"

int main()
{
  TraceClient client("tcp://127.0.0.1:61385");
  client.start();
}

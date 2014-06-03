#include "RtClient.hpp"

int main()
{
  RtClient client("tcp://127.0.0.1:61385");
  client.start();
}

#include <iostream>

#include <uuid_short/uuid_short.hpp>

int main()
{
  const std::string user_id = uuid_short::make_prefixed("user");
  const std::string request_id = uuid_short::make_prefixed("req", 10, "-");

  std::cout << "User ID:    " << user_id << std::endl;
  std::cout << "Request ID: " << request_id << std::endl;

  return 0;
}

#include <iostream>

#include <uuid_short/uuid_short.hpp>

int main()
{
  const std::string id = uuid_short::make();

  std::cout << "Generated ID: " << id << std::endl;

  return 0;
}

#include <iostream>

#include <uuid_short/uuid_short.hpp>

int main()
{
  const std::string id8 = uuid_short::make(8);
  const std::string id16 = uuid_short::make(16);

  std::cout << "8 char ID:  " << id8 << std::endl;
  std::cout << "16 char ID: " << id16 << std::endl;

  return 0;
}

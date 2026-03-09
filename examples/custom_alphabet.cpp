#include <iostream>

#include <uuid_short/uuid_short.hpp>

int main()
{
  const std::string alphabet = "0123456789abcdef";

  const std::string id = uuid_short::make_with_alphabet(16, alphabet);

  std::cout << "Hex ID: " << id << std::endl;

  return 0;
}

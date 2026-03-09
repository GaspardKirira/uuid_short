#include <iostream>

#include <uuid_short/uuid_short.hpp>

int main()
{
  uuid_short::Options opt;

  opt.length = 12;
  opt.prefix = "order";
  opt.separator = "-";
  opt.alphabet = "abcdefghijklmnopqrstuvwxyz0123456789";

  const uuid_short::Result result = uuid_short::generate(opt);

  if (!result.ok)
  {
    std::cerr << "Error: " << result.error << std::endl;
    return 1;
  }

  std::cout << "Generated order ID: " << result.value << std::endl;

  return 0;
}

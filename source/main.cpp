#include <iostream>

#include "lib.hpp"

auto main() -> int
{
  library lib;
  std::cout << "Hello from " << lib.name << "!\n";
  return 0;
}

#include "lib.hpp"

auto main() -> int
{
  using namespace std::literals;

  library lib;
  return lib.name == "codegen"sv ? 0 : 1;
}

#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

static void process(std::ifstream& input, std::ofstream& output)
{
  output << R"(#pragma once

inline constexpr char const characters[] = {
)" << std::setbase(16);
  input >> std::setbase(16);
  for (int a, b; input >> a >> b;) {
    output << "    0x" << (a + b) << ",\n";
  }
  output << "};\n";
}

static auto parse_argv(int argc, char const* argv[])
{
  auto result = std::vector<char const*>();
  result.reserve(static_cast<std::size_t>(argc - 1));
  for (int i = 1; i != argc; ++i) {
    result.push_back(argv[i]);
  }
  return result;
}

static int my_main(int argc, char const* argv[])
{
  const auto args = parse_argv(argc, argv);
  if (args.size() != 2) {
    std::cerr << "Usage: parse <input> <output>\n";
    return EXIT_FAILURE;
  }

  auto input = std::ifstream(args[0]);
  if (!input) {
    std::cerr << "Failed to open " << args[0] << " for reading\n";
    return EXIT_FAILURE;
  }

  auto output = std::ofstream(args[1]);
  if (!output) {
    std::cerr << "Failed to open " << args[1] << " for writing\n";
    return EXIT_FAILURE;
  }

  input.exceptions(std::ios::badbit);
  output.exceptions(std::ios::badbit | std::ios::failbit);
  process(input, output);

  return EXIT_SUCCESS;
}

int main(int argc, char const* argv[])
{
  if (argc == 0) {
    std::cerr << "Fatal error: argc == 0\n";
    return EXIT_FAILURE;
  }

  try {
    return my_main(argc, argv);
  } catch (std::exception& ex) {
    std::cerr << ex.what() << '\n';
  }
  return EXIT_FAILURE;
}

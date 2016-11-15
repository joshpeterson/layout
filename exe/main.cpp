#include "../include/driver.hpp"
#include <algorithm>
#include <string>
#include <vector>

static std::vector<std::string> transformArguments(int number, const char** argv)
{
  std::vector<std::string> arguments;
  if (number != 0)
  {
    arguments.reserve(number);
    std::copy_n(argv, number, std::back_inserter(arguments));
  }

  return arguments;
}

int main(int argc, const char* argv[])
{
  // This line violates cppcoreguidelines-pro-bounds-pointer-arithmetic
  return ComputeLayout(argv[1], transformArguments(argc - 2, &argv[2])); // NOLINT
}

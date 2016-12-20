#include "../include/driver.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

static std::vector<std::string> TransformArguments(int number, const char** argv)
{
  std::vector<std::string> arguments;
  if (number != 0)
  {
    arguments.reserve(number);
    std::copy_n(argv, number, std::back_inserter(arguments));
  }

  return arguments;
}

static void PrintUsage()
{
  std::cout << "Usage: layout <source file> [compiler arguments]\n";
}

static bool Equals(const char* standard, const char* candidate1,
                   const char* candidate2)
{
  return strcmp(standard, candidate1) == 0 || strcmp(standard, candidate2) == 0;
}

int main(int argc, const char* argv[])
{
  // These lines violate cppcoreguidelines-pro-bounds-pointer-arithmetic
  if (argc < 2 || (argc == 2 && Equals(argv[1], "--help", "-h"))) // NOLINT
  {
    PrintUsage();
    return 1;
  }

  return ComputeLayout(argv[1], TransformArguments(argc - 2, &argv[2]), // NOLINT
                       std::cout);
}

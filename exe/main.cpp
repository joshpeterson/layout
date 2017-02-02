#include "../include/driver.hpp"
#include "../include/gsl/multi_span"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

static std::vector<std::string> ToStrings(gsl::multi_span<const char*> args)
{
  std::vector<std::string> arguments;
  auto number_of_args = args.rank();
  if (number_of_args != 0)
  {
    arguments.reserve(number_of_args);
    std::copy(args.begin(), args.end(), std::back_inserter(arguments));
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
  auto args = gsl::multi_span<const char*>(argv, argc);
  if (argc < 2 || (argc == 2 && Equals(args[1], "--help", "-h")))
  {
    PrintUsage();
    return 1;
  }

  return ComputeLayout(args[1], ToStrings(args.last(argc - 2)), std::cout);
}

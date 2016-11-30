#include "../include/driver.hpp"
#include "../include/output_string.hpp"
#include "../include/type_inspector.hpp"
#include <iostream>

int ComputeLayout(const char* filename, const std::vector<std::string>& arguments)
{
  auto types = GatherTypes(filename, arguments);
  OutputString(types, filename, std::cout);
  return 0;
}

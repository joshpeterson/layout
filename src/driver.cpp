#include "../include/driver.hpp"
#include "../include/output_string.hpp"
#include "../include/type_inspector.hpp"
#include <iostream>

int ComputeLayout(const char* filename, const std::vector<std::string>& arguments,
                  std::ostream& out)
{
  auto[types, error] = GatherTypes(filename, arguments);

  OutputString(types, filename, out);

  if (error)
  {
    std::cerr << "We were not able to completely parse the input code. Please "
                 "treat the output with caution. It is a best guess, but it might "
                 "not work as you expect.\n";
    return 1;
  }

  return 0;
}

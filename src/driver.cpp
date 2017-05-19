#include "../include/driver.hpp"
#include "../include/output_string.hpp"
#include "../include/type_inspector.hpp"

int ComputeLayout(const char* filename, const std::vector<std::string>& arguments,
                  std::ostream& out)
{
  bool error = false;
  auto types = GatherTypes(filename, arguments, &error);
  if (error)
    return 1;

  OutputString(types, filename, out);
  return 0;
}

#include "../include/driver.hpp"
#include "../include/type_inspector.hpp"
#include "../include/output_string.hpp"
#include "../include/code_writer.hpp"
#include "../include/load_file.hpp"
#include <iostream>

int ComputeLayout(const char* filename)
{
  auto types = GatherTypes(filename);
  CodeWriter writer(std::cout);

  writer.WriteIncludes();
  writer.WriteLine();
  writer.WriteLine(LoadFile(filename));
  writer.WriteMainStart();

  for (auto line : CodeForStrings(types))
    writer.WriteLineIndented(line);

  writer.WriteMainEnd();

  return 0;
}

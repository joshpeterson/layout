#include "../include/driver.hpp"
#include "../include/code_writer.hpp"
#include "../include/load_file.hpp"
#include "../include/output_markdown.hpp"
#include "../include/output_string.hpp"
#include "../include/type_inspector.hpp"
#include <iostream>

int ComputeLayout(const char* filename, const std::vector<std::string>& arguments)
{
  auto types = GatherTypes(filename, arguments);
  std::cout << MarkdownFor(types);

  std::cout << "Use this snippet with your compiler:\n";
  std::cout << "```\n";

  for (auto line : CodeForStrings(types))
  {
    std::cout << line << "\n";
  }

  std::cout << "```\n";

  return 0;
}

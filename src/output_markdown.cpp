#include "../include/output_markdown.hpp"
#include <sstream>

std::string MarkdownFor(const std::vector<TypeInfo>& types)
{
  const char* header = "||||\n"
                       "---|:---:|:---:|:---:\n"
                       "**Name**|**Type**|**Offset**|**Size**\n";

  std::stringstream output;
  for (auto type : types)
  {
    output << type.name << " (" << type.size << "B)" << header;
    for (auto field : type.fields)
    {
      output << field.name << "|" << field.type << "|" << field.offset << "B|"
             << field.size << "B\n";
    }
    output << "\n";
  }

  return output.str();
}

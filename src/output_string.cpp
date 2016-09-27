#include "../include/output_string.hpp"
#include <sstream>

std::vector<std::string> CodeForStrings(const std::vector<TypeInfo>& types)
{
  std::vector<std::string> code;
  for (auto type : types)
  {
    std::stringstream line;
    line << "printf(\"Size of " << type.name << ": %d\\n\", (int)sizeof("
         << type.name << "));";
    code.push_back(line.str());

    for (auto field : type.fields)
    {
      std::stringstream line;
      line << "printf(\"" << field.name << " - type: " << field.type
           << " offset: %d size: %d\\n\", (int)offsetof(" << type.name << ", "
           << field.name << "), (int)sizeof(" << field.type << "));";
      code.push_back(line.str());
    }
  }

  return code;
}

#include "../include/output_string.hpp"
#include <sstream>

std::vector<std::string> CodeForStrings(const std::vector<TypeInfo>& types)
{
  std::vector<std::string> code;
  for (auto type : types)
  {
    std::stringstream line;
    line << "printf(\"Size of " << type.name << ": %d\\n\", sizeof("
          << type.name << "));";
    code.push_back(line.str());

    for (auto field : type.fields)
    {
      std::stringstream line;
      line << "printf(\"" << field.name << " - size: %d offset: %d\\n\", sizeof("
            << field.type << "), offsetof(" << type.name << ", " << field.name
            << "));";
      code.push_back(line.str());
    }
  }

  return code;
}

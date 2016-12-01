#include "../include/output_string.hpp"
#include "../include/code_writer.hpp"
#include "../include/load_file.hpp"
#include <sstream>

std::vector<std::string> CodeForStrings(const std::vector<TypeInfo>& types)
{
  std::vector<std::string> code;
  for (auto type : types)
  {
    std::stringstream line;
    line << "printf(\"" << type.name << " - size: %d bytes\\n\", (int)sizeof("
         << type.name << "));";
    code.push_back(line.str());

    for (auto field : type.fields)
    {
      std::stringstream line;
      line << "printf(\"* " << field.name << " - type: " << field.type
           << " offset: %d size: %d\\n\", (int)offsetof(" << type.name << ", "
           << field.name << "), (int)sizeof(" << field.type << "));";
      code.push_back(line.str());
    }
  }

  return code;
}

void OutputString(const std::vector<TypeInfo>& types, const char* filename,
                  std::ostream& out)
{
  CodeWriter writer(out);

  writer.WriteIncludes();
  writer.WriteLine();
  auto original = LoadFile(filename);
  auto withoutClass = writer.Replace(original, "class", "struct");
  auto withoutPrivate = writer.Replace(withoutClass, "private:", "public:");
  writer.WriteLine(withoutPrivate);
  writer.WriteMainStart();

  for (auto line : CodeForStrings(types))
    writer.WriteLineIndented(line);

  writer.WriteMainEnd();
}

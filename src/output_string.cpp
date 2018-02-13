#include "../include/output_string.hpp"
#include "../include/code_writer.hpp"
#include "../include/load_file.hpp"
#include <cstring>
#include <sstream>
#include <string>

static std::vector<std::string> CodeForType(const TypeInfo& type,
                                            bool firstType)
{
  std::vector<std::string> code;
  auto numberOfFields = type.fields.size();

  if (!firstType)
    code.push_back(EmitEmptyLine());

  auto typeName = type.name;
  if (numberOfFields != 0)
  {
    code.push_back(EmitFieldCount(typeName, numberOfFields));

    code.push_back(EmitFieldArrayStart(typeName, numberOfFields));
    for (const auto& field : type.fields)
      code.push_back("  " + EmitFieldArrayEntry(typeName, field));
    code.push_back(EmitFieldArrayEnd());
  }

  code.push_back(EmitTypeNameAndSize(type));

  if (numberOfFields == 0)
  {
    code.push_back(EmitNoFieldsLine());
  }
  else
  {
    auto widths = ComputeColumnWidths(type.fields);
    code.push_back(EmitHeaderRow(widths));

    code.push_back(EmitForLoopStart(typeName));
    code.push_back("  " + EmitFieldOutput(widths));
    code.push_back(EmitForLoopEnd());
  }

  return code;
}

static std::vector<std::string> CodeForTypes(const std::vector<TypeInfo>& types)
{
  std::vector<std::string> code;
  auto i = 0;
  for (const auto& type : types)
  {
    auto codeForType = CodeForType(type, i == 0);
    code.insert(code.end(), codeForType.begin(), codeForType.end());
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
  writer.WriteLine(EmitFieldInformationStruct());

  writer.WriteMainStart();

  for (const auto& line : CodeForTypes(types))
    writer.WriteLineIndented(line);

  writer.WriteMainEnd();
}

std::string EmitFieldCount(const std::string& typeName, int numberOfFields)
{
  std::stringstream out;
  out << "const int " << typeName << "_fieldCount = " << numberOfFields << ";";
  return out.str();
}

std::string EmitFieldArrayStart(const std::string& typeName, int numberOfFields)
{
  std::stringstream out;
  out << "FieldInfo " << typeName << "_fields[" << numberOfFields << "] = {";
  return out.str();
}

std::string EmitFieldArrayEnd() { return "};"; }

std::string EmitFieldArrayEntry(const std::string& typeName,
                                const FieldInfo& field)
{
  std::stringstream out;
  out << R"({")" << field.name << R"(", ")" << field.type << R"(", offsetof()"
      << typeName << ", " << field.name << "), sizeof(" << field.type << ")},";
  return out.str();
}

std::string EmitFieldInformationStruct()
{
  std::stringstream out;
  out << "typedef struct\n";
  out << "{\n";
  out << "  const char* name;\n";
  out << "  const char* type;\n";
  out << "  size_t offset;\n";
  out << "  size_t size;\n";
  out << "} FieldInfo;\n";
  return out.str();
}

std::string EmitTypeNameAndSize(const TypeInfo& typeInfo)
{
  std::stringstream out;
  out << R"(printf(")" << typeInfo.name << R"( (%zub):\n", sizeof()"
      << typeInfo.name << "));";
  return out.str();
}

std::string EmitForLoopStart(const std::string& typeName)
{
  std::stringstream out;
  out << "for (int i = 0; i < " << typeName << "_fieldCount; i++)\n";
  out << "  {\n";
  out << "    FieldInfo* field = &" << typeName << "_fields[i];\n"
      << "    size_t padding = i < " << typeName << "_fieldCount - 1 ? "
      << typeName << "_fields[i + 1].offset != 0 ? " << typeName
      << "_fields[i + 1].offset"
      << " - field->offset - field->size : 0 : sizeof(" << typeName
      << ") - field->offset - field->size;\n";
  return out.str();
}

std::string EmitForLoopEnd() { return "}"; }

std::string EmitHeaderRow(const ColumnWidths& widths)
{
  std::stringstream out;
  out << R"(printf("%)" << widths.name << "s | %" << widths.type << "s | %"
      << widths.offset << "s | %" << widths.size << "s | %" << widths.padding
      << R"(s\n", "Field", "Type", "Offset", "Size", "Padding");)";
  return out.str();
}

std::string EmitFieldOutput(const ColumnWidths& widths)
{
  std::stringstream out;
  out << R"(printf("%)" << widths.name << "s | %" << widths.type << "s | %"
      << widths.offset << "zu | %" << widths.size << "zu | %" << widths.padding
      << R"(zu\n", )"
      << "field->name, field->type, field->offset, field->size, padding);";
  return out.str();
}

std::string EmitEmptyLine() { return R"(printf("\n");)"; }

std::string EmitNoFieldsLine() { return R"(printf("No fields\n");)"; }

ColumnWidths ComputeColumnWidths(const std::vector<FieldInfo>& fields)
{
  ColumnWidths widths{};
  widths.type = FindLongestFieldTypeName(fields);
  widths.name = FindLongestFieldName(fields);
  widths.size = FindLongestFieldSize(fields);
  widths.offset = FindLongestFieldOffset(fields);
  widths.padding = 7;

  return widths;
}

size_t FindLongestFieldTypeName(const std::vector<FieldInfo>& fields)
{
  return FindLongestFieldEntryName(
      fields, [](auto field) { return field.type; }, std::strlen("Type"));
}

size_t FindLongestFieldName(const std::vector<FieldInfo>& fields)
{
  return FindLongestFieldEntryName(
      fields, [](auto field) { return field.name; }, std::strlen("Name") + 1);
}

size_t FindLongestFieldSize(const std::vector<FieldInfo>& fields)
{
  return FindLongestFieldEntryName(
      fields, [](auto field) { return std::to_string(field.size); },
      std::strlen("Size"));
}

size_t FindLongestFieldOffset(const std::vector<FieldInfo>& fields)
{
  return FindLongestFieldEntryName(
      fields, [](auto field) { return std::to_string(field.offset); },
      std::strlen("Offset"));
}

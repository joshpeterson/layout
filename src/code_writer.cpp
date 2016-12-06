#include "../include/code_writer.hpp"
#include "../include/output_markdown.hpp"
#include <regex>

CodeWriter::CodeWriter(std::ostream& out) : out_(out) {}

void CodeWriter::WriteIncludes()
{
  WriteLine("#include <stdio.h>");
  WriteLine("#include <stddef.h>");
}

void CodeWriter::WriteLine() { WriteLine(std::string()); }

void CodeWriter::WriteLine(const std::string& code) { out_ << code << "\n"; }

void CodeWriter::WriteLineIndented(const std::string& code)
{
  WriteLine("  " + code);
}

void CodeWriter::WriteMainStart()
{
  WriteLine("int main(int argc, const char* argv[])");
  WriteLine("{");
}

void CodeWriter::WriteMainEnd()
{
  WriteLineIndented("return 0;");
  WriteLine("}");
}

void CodeWriter::WriteFieldInformationStruct()
{
  WriteLine("typedef struct");
  WriteLine("{");
  WriteLineIndented("const char* name;");
  WriteLineIndented("const char* type;");
  WriteLineIndented("size_t offset;");
  WriteLineIndented("size_t size;");
  WriteLine("} FieldInfo;");
}

std::string CodeWriter::Replace(const std::string& haystack,
                                const std::string& needle,
                                const std::string& replacement)
{
  std::regex match(needle);
  return std::regex_replace(haystack, match, replacement);
}

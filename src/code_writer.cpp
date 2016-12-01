#include "../include/code_writer.hpp"
#include "../include/output_markdown.hpp"
#include <regex>

CodeWriter::CodeWriter(std::ostream& out) : out_(out) {}

void CodeWriter::WriteIncludes()
{
  out_ << "#include <stdio.h>\n";
  out_ << "#include <stddef.h>\n";
}

void CodeWriter::WriteLine() { WriteLine(std::string()); }

void CodeWriter::WriteLine(const std::string& code) { out_ << code << "\n"; }

void CodeWriter::WriteLineIndented(const std::string& code)
{
  WriteLine("\t" + code);
}

void CodeWriter::WriteMainStart()
{
  out_ << "int main(int argc, const char* argv[])\n";
  out_ << "{\n";
}

void CodeWriter::WriteMainEnd()
{
  out_ << "\treturn 0;\n";
  out_ << "}\n";
}

std::string CodeWriter::Replace(const std::string& haystack,
                                const std::string& needle,
                                const std::string& replacement)
{
  std::regex match(needle);
  return std::regex_replace(haystack, match, replacement);
}

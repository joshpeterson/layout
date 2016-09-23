#include "../include/code_writer.hpp"

CodeWriter::CodeWriter(std::ostream& out) : out_(out)
{
}

void CodeWriter::WriteIncludes()
{
  out_ << "#include <cstdio>\n";
  out_ << "#include <cstddef>\n";
}

void CodeWriter::WriteLine(const std::string& code)
{
  out_ << code << "\n";
}

void CodeWriter::WriteLineIndented(const std::string& code)
{
  out_ << "\t" << code << "\n";
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

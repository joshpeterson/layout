#pragma once
#include <ostream>

class CodeWriter
{
public:
  CodeWriter(std::ostream& out);
  void WriteIncludes();
  void WriteLine();
  void WriteLine(const std::string& code);
  void WriteLineIndented(const std::string& code);
  void WriteMainStart();
  void WriteMainEnd();
  void WriteFieldInformationStruct();
  std::string Replace(const std::string& haystack, const std::string& needle,
                      const std::string& replacement);

private:
  std::ostream& out_;
};

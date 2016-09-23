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

  private:
    std::ostream& out_;
};

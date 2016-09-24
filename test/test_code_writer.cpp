#include "catch.hpp"
#include "../include/code_writer.hpp"
#include <string>
#include <sstream>

TEST_CASE("Code Writer")
{
  std::stringstream code;
  CodeWriter writer(code);

  SECTION("Can write includes")
  {
    writer.WriteIncludes();
    REQUIRE(code.str() == "#include <stdio.h>\n#include <stddef.h>\n");
  }

  SECTION("Can write line")
  {
    std::string expected = "struct Test{};";
    writer.WriteLine(expected);
    REQUIRE(code.str() == expected + "\n");
  }

  SECTION("Can write line indented")
  {
    std::string expected = "struct Test{};";
    writer.WriteLineIndented(expected);
    REQUIRE(code.str() == "\t" + expected + "\n");
  }

  SECTION("Can write blank line")
  {
    writer.WriteLine();
    REQUIRE(code.str() == "\n");
  }

  SECTION("Can write main start")
  {
    writer.WriteMainStart();
    REQUIRE(code.str() == "int main(int argc, const char* argv[])\n{\n");
  }

  SECTION("Can write main end")
  {
    writer.WriteMainEnd();
    REQUIRE(code.str() == "\treturn 0;\n}\n");
  }
}

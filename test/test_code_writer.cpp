#include "../include/code_writer.hpp"
#include "catch.hpp"
#include <sstream>
#include <string>

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
    REQUIRE(code.str() == "  " + expected + "\n");
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
    REQUIRE(code.str() == "  return 0;\n}\n");
  }

  SECTION("Can replace text in string")
  {
    std::string expected = "struct Test {};";
    REQUIRE(writer.Replace("class Test {};", "class", "struct") == expected);
  }

  SECTION("Does not replace anything when the match is not found")
  {
    std::string expected = "class Test {};";
    REQUIRE(writer.Replace(expected, "private:", "public:") == expected);
  }

  SECTION("Can write field information struct")
  {
    auto expected = "typedef struct\n"
                    "{\n"
                    "  const char* name;\n"
                    "  const char* type;\n"
                    "  size_t offset;\n"
                    "  size_t size;\n"
                    "} FieldInfo;\n";
    writer.WriteFieldInformationStruct();
    REQUIRE(code.str() == expected);
  }
}

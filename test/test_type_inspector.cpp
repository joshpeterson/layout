#include "../include/type_inspector.hpp"
#include "catch.hpp"
#include "temp_source_file.hpp"
#include <string>
#include <vector>

std::vector<TypeInfo> Setup(const char* source);
std::vector<TypeInfo> Setup(const char* source,
                            const std::vector<std::string>& arguments);

TEST_CASE("Type Inspector")
{
  SECTION("Can parse one type with no fields from a source file")
  {
    const char* source = "struct Test{};";
    auto types = Setup(source);
    REQUIRE(types.size() == 1);
  }

  SECTION("Can parse one class with no fields from a source file")
  {
    const char* source = "class Test{};";
    auto types = Setup(source);
    REQUIRE(types.size() == 1);
  }

  SECTION("Can parse two types with no fields from a source file")
  {
    const char* source = "struct Test1{}; struct Test2{};";
    auto types = Setup(source);
    REQUIRE(types.size() == 2);
  }

  SECTION("Parse a C-style struct only once")
  {
    const char* source = "typedef struct {} Test;";
    auto types = Setup(source);
    REQUIRE(types.size() == 1);
  }

  SECTION("Can parse the name of one type with no fields from a source file")
  {
    const char* source = "struct Test{};";
    auto types = Setup(source);
    REQUIRE(types[0].name == "Test");
  }

  SECTION("Can parse the size of one type with no fields from a source file")
  {
    const char* source = "struct Test{};";
    auto types = Setup(source);
    REQUIRE(types[0].size == 1);
  }

  SECTION("Can parse one type with one field from a source file")
  {
    const char* source = "struct Test{int field1;};";
    auto types = Setup(source);
    REQUIRE(types[0].fields.size() == 1);
  }

  SECTION("Can parse the size of a type with one field from a source file")
  {
    const char* source = "struct Test{int field1;};";
    auto types = Setup(source);
    REQUIRE(types[0].size == 4);
  }

  SECTION("Can parse the type of one field from a source file")
  {
    const char* source = "struct Test{int field1;};";
    auto types = Setup(source);
    REQUIRE(types[0].fields[0].type == "int");
  }

  SECTION("Can parse the name of one field from a source file")
  {
    const char* source = "struct Test{int field1;};";
    auto types = Setup(source);
    REQUIRE(types[0].fields[0].name == "field1");
  }

  SECTION("Can parse the size of one field from a source file")
  {
    const char* source = "struct Test{int field1;};";
    auto types = Setup(source);
    REQUIRE(types[0].fields[0].size == 4);
  }

  SECTION("Can parse the size of one field from a source file")
  {
    const char* source = "struct Test{int field1;};";
    auto types = Setup(source);
    REQUIRE(types[0].fields[0].offset == 0);
  }

  SECTION("Can parse the type of a second field from a source file")
  {
    const char* source = "struct Test{int field1; double field2;};";
    auto types = Setup(source);
    REQUIRE(types[0].fields[1].type == "double");
  }

  SECTION("Can parse the name of a second field from a source file")
  {
    const char* source = "struct Test{int field1; double field2;};";
    auto types = Setup(source);
    REQUIRE(types[0].fields[1].name == "field2");
  }

  SECTION("Can parse the size of a second field from a source file")
  {
    const char* source = "struct Test{int field1; double field2;};";
    auto types = Setup(source);
    REQUIRE(types[0].fields[1].size == 8);
  }

  SECTION("Can parse the offset of a second field from a source file")
  {
    const char* source = "struct Test{int field1; double field2;};";
    auto types = Setup(source);
    REQUIRE(types[0].fields[1].offset == 8);
  }

  SECTION("Can parse type using a standard library type")
  {
    const char* source = "#include <string>\n"
                         "struct Test{std::string field;};\n";
    auto types = Setup(source);
    REQUIRE(types[0].fields[0].name == "field");
  }

  SECTION("Can parse the size of a field using a standard library type")
  {
    const char* source = "#include <string>\n"
                         "struct Test{std::string field;};\n";
    auto types = Setup(source);
    REQUIRE(types[0].fields[0].size == sizeof(std::string));
  }

  SECTION("Can parse the offset of a field using a standard library type")
  {
    const char* source = "#include <string>\n"
                         "struct Test{std::string field;\n"
                         "int field2;};\n";
    auto types = Setup(source);
    REQUIRE(types[0].fields[1].offset == sizeof(std::string));
  }

  SECTION("Can parse the size of a field in a bit field")
  {
    const char* source = "struct Test{int a:16; int b:17;};\n";
    auto types = Setup(source);
    REQUIRE(types[0].fields[1].size == 4);
  }

  SECTION("Can parse the offset of a field in a bitfield")
  {
    const char* source = "struct Test{int a:16; int b:17;};\n";
    auto types = Setup(source);
    REQUIRE(types[0].fields[1].offset == 4);
  }

  SECTION("Can parse the size of a field after a bit field")
  {
    const char* source = "struct Test{int a:16; int b:17; int c;};\n";
  }

  SECTION("Can parse the offset of a field after a bitfield")
  {
    const char* source = "struct Test{int a:16; int b:17; int c;};\n";
    auto types = Setup(source);
    REQUIRE(types[0].fields[2].offset == 8);
  }

  SECTION("Can parse the size of a pointer field in a 64-bit build")
  {
    const char* source = "struct Test{int* pointer;};\n";
    std::vector<std::string> arguments;
    arguments.push_back("-m64");
    auto types = Setup(source, arguments);
    REQUIRE(types[0].fields[0].size == 8);
  }

  SECTION("Can parse the size of a pointer field in a 32-bit build")
  {
    const char* source = "struct Test{int* pointer;};\n";
    std::vector<std::string> arguments;
    arguments.push_back("-m32");
    auto types = Setup(source, arguments);
    REQUIRE(types[0].fields[0].size == 4);
  }

  SECTION("Skips a forward declaration")
  {
    const char* source = "struct Test;";
    auto types = Setup(source);
    REQUIRE(types.size() == 0);
  }
}

std::vector<TypeInfo> Setup(const char* source)
{
  std::vector<std::string> empty;
  return Setup(source, empty);
}

std::vector<TypeInfo> Setup(const char* source,
                            const std::vector<std::string>& arguments)
{
  const char* testFilename = "source_file_for_tests.hh";
  TempSourceFile testFile(testFilename, source);
  return GatherTypes(testFilename, arguments);
}

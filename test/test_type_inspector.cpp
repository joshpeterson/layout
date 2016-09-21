#include "catch.hpp"
#include "temp_source_file.hpp"
#include "../include/type_inspector.hpp"

const char* test_filename = "source_file_for_tests.h";

TEST_CASE("Type Inspector")
{
  SECTION("Can parse one type with no fields from a source file")
  {
    const char* source = "struct Test{};";
    TempSourceFile testFile(test_filename, source);
    auto types = GatherTypes(test_filename);
    REQUIRE(types.size() == 1);
  }

  SECTION("Can parse two types with no fields from a source file")
  {
    const char* source = "struct Test1{}; struct Test2{};";
    TempSourceFile testFile(test_filename, source);
    auto types = GatherTypes(test_filename);
    REQUIRE(types.size() == 2);
  }

  SECTION("Can parse the name of one type with no fields from a source file")
  {
    const char* source = "struct Test{};";
    TempSourceFile testFile(test_filename, source);
    auto types = GatherTypes(test_filename);
    REQUIRE(types[0].name == "struct Test");
  }

  SECTION("Can parse one type with one field from a source file")
  {
    const char* source = "struct Test{int field1;};";
    TempSourceFile testFile(test_filename, source);
    auto types = GatherTypes(test_filename);
    REQUIRE(types[0].fields.size() == 1);
  }

  SECTION("Can parse the type of one field from a source file")
  {
    const char* source = "struct Test{int field1;};";
    TempSourceFile testFile(test_filename, source);
    auto types = GatherTypes(test_filename);
    REQUIRE(types[0].fields[0].type == "int");
  }

  SECTION("Can parse the name of one field from a source file")
  {
    const char* source = "struct Test{int field1;};";
    TempSourceFile testFile(test_filename, source);
    auto types = GatherTypes(test_filename);
    REQUIRE(types[0].fields[0].name == "field1");
  }

  SECTION("Can parse the type of a second field from a source file")
  {
    const char* source = "struct Test{int field1; double field2;};";
    TempSourceFile testFile(test_filename, source);
    auto types = GatherTypes(test_filename);
    REQUIRE(types[0].fields[1].type == "double");
  }

  SECTION("Can parse the name of a second field from a source file")
  {
    const char* source = "struct Test{int field1; double field2;};";
    TempSourceFile testFile(test_filename, source);
    auto types = GatherTypes(test_filename);
    REQUIRE(types[0].fields[1].name == "field2");
  }
}
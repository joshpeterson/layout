#include "catch.hpp"
#include "temp_source_file.hpp"
#include "../include/type_inspector.hpp"

const char* test_filename = "source_file_for_tests";

TEST_CASE("Type Inspector")
{
  SECTION("Can parse one type with no fields from a source file")
  {
    const char* source = "struct Test{};";
    TempSourceFile testFile(test_filename, source);
    auto types = GatherTypes(test_filename);
    REQUIRE(types.size() == 1);
  }
}

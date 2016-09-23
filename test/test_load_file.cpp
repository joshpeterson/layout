#include "catch.hpp"
#include "temp_source_file.hpp"
#include "../include/load_file.hpp"


TEST_CASE("Load File")
{
  const char* test_filename = "file_for_tests";
  SECTION("Can get text file contents in string")
  {
    const char* source = "struct Test{};";
    TempSourceFile testFile(test_filename, source);
    REQUIRE(LoadFile(test_filename) == source);
  }
}

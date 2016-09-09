#include "catch.hpp"
#include <cstdio>
#include <experimental/filesystem>
#include "../include/type_inspector.hpp"

namespace fs = std::experimental::filesystem;

const char* test_filename = "source_file_for_tests";

TEST_CASE("Type Inspector")
{
  SECTION("Can parse one type with no fields from a source file")
  {
    const char* source = "struct Test{};";
    auto tempFile = fopen(test_filename, "w");
    std::fputs(source, tempFile);
    fclose(tempFile);
    auto types = GatherTypes(test_filename);
    REQUIRE(types.size() == 1);
    std::remove(test_filename);
  }
}

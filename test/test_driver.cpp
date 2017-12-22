#include "../include/driver.hpp"
#include "../include/load_file.hpp"
#include "catch.hpp"
#include "temp_source_file.hpp"
#include <experimental/filesystem>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::experimental::filesystem;

static std::string Verify(const std::string& input);

TEST_CASE("Driver")
{
  SECTION("End to end tests")
  {
    for (auto& file : fs::directory_iterator("../../test/end-to-end"))
    {
      if (fs::is_regular_file(file.status()) &&
          file.path().extension() == ".hpp")
      {
        auto expectedPath = file.path();
        expectedPath.replace_extension();
        expectedPath.replace_filename(expectedPath.filename().string() +
                                      "_expected.txt");
        if (!fs::exists(expectedPath))
          REQUIRE("This file should exist but does not:" ==
                  expectedPath.string());

        auto input = LoadFile(file.path().c_str());
        auto expected = LoadFile(expectedPath.c_str());
        INFO("The expected output is in file: " << expectedPath)
        CHECK(Verify(input) == expected);
      }
    }
  }
}

static std::string Verify(const std::string& input)
{
  const char* testFilename = "source_file_for_tests.hh";
  TempSourceFile testFile(testFilename, input.c_str());
  std::vector<std::string> empty;
  std::stringstream out;
  ComputeLayout(testFilename, empty, out);
  return out.str();
}

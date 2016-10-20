#include "../include/field_info.hpp"
#include "../include/output_markdown.hpp"
#include "../include/type_info.hpp"
#include "catch.hpp"

TEST_CASE("Output Markdown")
{
  SECTION("Empty type outputs table header and type size")
  {
    const char* expected = "Test (0)||||\n"
                           "---|:---:|:---:|:---:\n"
                           "**Name**|**Type**|**Offset**|**Size**\n";
    TypeInfo typeInfo{"Test"};
    std::vector<TypeInfo> types{typeInfo};
    auto markdown = MarkdownFor(types);
    REQUIRE(markdown == expected);
  }

  SECTION("Verify table for a type with twp fields")
  {
    const char* expected = "Test (16)||||\n"
                           "---|:---:|:---:|:---:\n"
                           "**Name**|**Type**|**Offset**|**Size**\n"
                           "one|int|0|4\n"
                           "two|double|8|8\n";
    std::vector<FieldInfo> fields = {{"int", "one", 4, 0},
                                     {"double", "two", 8, 8}};
    TypeInfo typeInfo{"Test", 16, fields};
    std::vector<TypeInfo> types{typeInfo};
    auto markdown = MarkdownFor(types);
    REQUIRE(markdown == expected);
  }
}

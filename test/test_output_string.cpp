#include "catch.hpp"
#include "../include/output_string.hpp"
#include "../include/type_info.hpp"
#include "../include/field_info.hpp"

TEST_CASE("Output String")
{
  SECTION("First entry is name and size of type")
  {
    TypeInfo typeInfo { "Test" };
    std::vector<TypeInfo> types { typeInfo };
    auto lines = CodeForStrings(types);
    REQUIRE(lines[0] == "printf(\"Size of Test: %d\\n\", sizeof(Test));");
  }

  SECTION("Second entry is name, size, and offset of first field")
  {
    FieldInfo fieldInfo { "int", "field1" };
    TypeInfo typeInfo { "Test", std::vector<FieldInfo> { fieldInfo } };
    std::vector<TypeInfo> types { typeInfo };
    auto lines = CodeForStrings(types);
    REQUIRE(lines[1] == "printf(\"field1 - size: %d offset: %d\\n\", sizeof(int),"
                        " offsetof(Test, field1));");
  }
}

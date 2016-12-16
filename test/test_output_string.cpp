#include "../include/field_info.hpp"
#include "../include/output_string.hpp"
#include "../include/type_info.hpp"
#include "catch.hpp"

TEST_CASE("Output String")
{
  SECTION("Can emit const field count")
  {
    REQUIRE(EmitFieldCount("TestType", 8) == "const int TestType_fieldCount = 8;");
  }

  SECTION("Can emit the start of a field array")
  {
    REQUIRE(EmitFieldArrayStart("TestType", 8) ==
            "FieldInfo TestType_fields[8] = {");
  }

  SECTION("Can emit the end of a field array")
  {
    REQUIRE(EmitFieldArrayEnd() == "};");
  }

  SECTION("Can emit field array entry")
  {
    FieldInfo fieldInfo{"int", "field1"};
    REQUIRE(EmitFieldArrayEntry("TestType", fieldInfo) ==
            "{\"field1\", \"int\", offsetof(TestType, field1), sizeof(int)},");
  }

  SECTION("Can emit field information struct")
  {
    auto expected = "typedef struct\n"
                    "{\n"
                    "  const char* name;\n"
                    "  const char* type;\n"
                    "  size_t offset;\n"
                    "  size_t size;\n"
                    "} FieldInfo;\n";
    REQUIRE(EmitFieldInformationStruct() == expected);
  }

  SECTION("Can emit type name and size")
  {
    TypeInfo typeInfo{"TestType", 24};
    REQUIRE(EmitTypeNameAndSize(typeInfo) ==
            "printf(\"TestType (%zu bytes):\\n\", sizeof(TestType));");
  }

  std::vector<FieldInfo> fields{{"Big", "field1", 16, 0},
                                {"double", "longFieldName", 8, 16}};

  auto widths = ComputeColumnWidths(fields);

  SECTION("Can compute type column width") { REQUIRE(widths.type == 6); }

  SECTION("Can compute name column width") { REQUIRE(widths.name == 13); }

  SECTION("Can compute size column width") { REQUIRE(widths.size == 4); }

  SECTION("Can compute offset column width") { REQUIRE(widths.offset == 6); }

  SECTION("Can compute offset column width") { REQUIRE(widths.padding == 7); }

  SECTION("Can emit header row")
  {
    REQUIRE(EmitHeaderRow(widths) == "printf(\"%13s | %6s | %6s | %4s | "
                                     "%7s\\n\", \"Field\", \"Type\", \"Offset\", "
                                     "\"Size\", \"Padding\");");
  }

  SECTION("Can emit field output")
  {
    REQUIRE(EmitFieldOutput(widths) == "printf(\"%13s | %6s | %6zu | %4zu | "
                                       "%7zu\\n\", field->name, field->type, "
                                       "field->offset, field->size, padding);");
  }

  SECTION("Can emit for loop start")
  {
    REQUIRE(EmitForLoopStart("TestType") ==
            "for (int i = 0; i < TestType_fieldCount; i++)\n"
            "  {\n"
            "    FieldInfo* field = &TestType_fields[i];\n"
            "    size_t padding = i < TestType_fieldCount - 1 "
            "? TestType_fields[i + 1].offset - field->offset "
            "- field->size : sizeof(TestType) - field->offset - field->size;\n");
  }

  SECTION("Can emit for loop end") { REQUIRE(EmitForLoopEnd() == "}"); }

  SECTION("Can emit an empty line")
  {
    REQUIRE(EmitEmptyLine() == "printf(\"\\n\");");
  }
}

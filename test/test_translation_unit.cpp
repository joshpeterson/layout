#include "catch.hpp"
#include "../include/translation_unit.hpp"
#include "libclang_test_double.hpp"

extern bool createIndexCalled;
extern bool parseTranslationUnitCalled;
extern clangIndex indexPassedToParseTranslationUnit;
extern const char* fileNamePassedToParseTranslationUnit;
extern bool disposeTranslationUnitCalled;
extern bool disposeIndexCalled;
extern clangTranslationUnit translationUnitPassedToDisposeTranslationUnit;

TEST_CASE("Translation Unit")
{
  SECTION("Creating a TranslationUnit calls createIndex")
  {
    TranslationUnit test("");
    REQUIRE(createIndexCalled == true);
  }

  SECTION("Creating a TranslationUnit calls parseTranslationUnit")
  {
    TranslationUnit test("");
    REQUIRE(parseTranslationUnitCalled == true);
  }

  SECTION("parseTranslationUnit is called with the index from createIndex")
  {
    TranslationUnit test("");
    REQUIRE(indexPassedToParseTranslationUnit == expectedIndex);
  }

  SECTION("parseTranslationUnit is called with the input file name")
  {
    const char* expectedFileName = "Foo.cpp";
    TranslationUnit test(expectedFileName);
    REQUIRE(fileNamePassedToParseTranslationUnit == expectedFileName);
  }

  SECTION("disposeTranslationUnit is called in destructor")
  {
    {
      TranslationUnit test("");
    }
    REQUIRE(disposeTranslationUnitCalled == true);
  }

  SECTION("disposeTranslationUnit is called with the proper translation unit")
  {
    {
      TranslationUnit test("");
    }
    REQUIRE(translationUnitPassedToDisposeTranslationUnit ==
            expectedTranslationUnit);
  }

  SECTION("disposeIndex is called in destructor")
  {
    {
      TranslationUnit test("");
    }
    REQUIRE(disposeIndexCalled == true);
  }
}

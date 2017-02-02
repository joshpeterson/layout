#include "../include/translation_unit.hpp"
#include "catch.hpp"
#include "libclang_test_double.hpp"
#include <string>
#include <vector>

#if ENABLE_FAKING

extern bool createIndexCalled;
extern bool parseTranslationUnitCalled;
extern CXIndex indexPassedToParseTranslationUnit;
extern const char* fileNamePassedToParseTranslationUnit;
extern std::vector<std::string> argumentsPassedToParseTranslationUnit;
extern bool disposeTranslationUnitCalled;
extern bool disposeIndexCalled;
extern CXTranslationUnit translationUnitPassedToDisposeTranslationUnit;

TEST_CASE("Translation Unit")
{
  FAKE(CreateIndex, CreateIndexDouble);
  FAKE(ParseTranslationUnit, ParseTranslationUnitDouble);
  FAKE(DisposeTranslationUnit, DisposeTranslationUnitDouble);
  FAKE(DisposeIndex, DisposeIndexDouble);

  SECTION("Creating a TranslationUnit calls createIndex")
  {
    TranslationUnit test("", std::vector<std::string>());
    REQUIRE(createIndexCalled == true);
  }

  SECTION("Creating a TranslationUnit calls parseTranslationUnit")
  {
    TranslationUnit test("", std::vector<std::string>());
    REQUIRE(parseTranslationUnitCalled == true);
  }

  SECTION("parseTranslationUnit is called with the index from createIndex")
  {
    TranslationUnit test("", std::vector<std::string>());
    REQUIRE(indexPassedToParseTranslationUnit == expectedIndex);
  }

  SECTION("parseTranslationUnit is called with the input file name")
  {
    const char* expectedFileName = "Foo.cpp";
    TranslationUnit test(expectedFileName, std::vector<std::string>());
    REQUIRE(fileNamePassedToParseTranslationUnit == expectedFileName);
  }

  SECTION("parseTranslationUnit is called with command line arguments")
  {
    const char* expectedArgument = "-m32";
    std::vector<std::string> expectedArguments;
    expectedArguments.push_back(expectedArgument);

    TranslationUnit test("Foo.cpp", expectedArguments);
    REQUIRE(argumentsPassedToParseTranslationUnit[0] == expectedArgument);
  }

  SECTION("disposeTranslationUnit is called in destructor")
  {
    {
      TranslationUnit test("", std::vector<std::string>());
    }
    REQUIRE(disposeTranslationUnitCalled == true);
  }

  SECTION("disposeTranslationUnit is called with the proper translation unit")
  {
    {
      TranslationUnit test("", std::vector<std::string>());
    }
    REQUIRE(translationUnitPassedToDisposeTranslationUnit ==
            expectedTranslationUnit);
  }

  SECTION("disposeIndex is called in destructor")
  {
    {
      TranslationUnit test("", std::vector<std::string>());
    }
    REQUIRE(disposeIndexCalled == true);
  }
}

#endif // ENABLE_FAKING

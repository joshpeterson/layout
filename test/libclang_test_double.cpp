#include "libclang_test_double.hpp"
#include <string>
#include <vector>

bool createIndexCalled = false;
bool parseTranslationUnitCalled = false;
CXIndex indexPassedToParseTranslationUnit;
const char* fileNamePassedToParseTranslationUnit;
std::vector<std::string> argumentsPassedToParseTranslationUnit;
bool disposeTranslationUnitCalled = false;
bool disposeIndexCalled = false;
CXTranslationUnit translationUnitPassedToDisposeTranslationUnit;

CXIndex CreateIndexDouble(bool /*displayDiagnostics*/)
{
  createIndexCalled = true;
  return expectedIndex;
}

ParseResult ParseTranslationUnitDouble(CXIndex index, const char* fileName,
                                       const std::vector<std::string>& arguments)
{
  parseTranslationUnitCalled = true;
  indexPassedToParseTranslationUnit = index;
  fileNamePassedToParseTranslationUnit = fileName;
  argumentsPassedToParseTranslationUnit = arguments;
  return {expectedTranslationUnit, false};
}

void DisposeTranslationUnitDouble(CXTranslationUnit translationUnit)
{
  disposeTranslationUnitCalled = true;
  translationUnitPassedToDisposeTranslationUnit = translationUnit;
}

void DisposeIndexDouble(CXIndex /* index */) { disposeIndexCalled = true; }

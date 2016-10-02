#include "../include/libclang.hpp"
#include "libclang_test_double.hpp"

bool createIndexCalled = false;
bool parseTranslationUnitCalled = false;
CXIndex indexPassedToParseTranslationUnit;
const char* fileNamePassedToParseTranslationUnit;
bool disposeTranslationUnitCalled = false;
bool disposeIndexCalled = false;
CXTranslationUnit translationUnitPassedToDisposeTranslationUnit;

CXIndex createIndexDouble()
{
  createIndexCalled = true;
  return expectedIndex;
}

CXTranslationUnit parseTranslationUnitDouble(CXIndex index, const char* fileName)
{
  parseTranslationUnitCalled = true;
  indexPassedToParseTranslationUnit = index;
  fileNamePassedToParseTranslationUnit = fileName;
  return expectedTranslationUnit;
}

void disposeTranslationUnitDouble(CXTranslationUnit translationUnit)
{
  disposeTranslationUnitCalled = true;
  translationUnitPassedToDisposeTranslationUnit = translationUnit;
}

void disposeIndexDouble(CXIndex /* index */) { disposeIndexCalled = true; }

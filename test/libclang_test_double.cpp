#include "../include/libclang.hpp"
#include "libclang_test_double.hpp"

bool createIndexCalled = false;
bool parseTranslationUnitCalled = false;
clangIndex indexPassedToParseTranslationUnit;
const char* fileNamePassedToParseTranslationUnit;
bool disposeTranslationUnitCalled = false;
bool disposeIndexCalled = false;
clangTranslationUnit translationUnitPassedToDisposeTranslationUnit;

clangIndex createIndexDouble()
{
  createIndexCalled = true;
  return expectedIndex;
}

clangTranslationUnit parseTranslationUnitDouble(clangIndex index,
                                                const char* fileName)
{
  parseTranslationUnitCalled = true;
  indexPassedToParseTranslationUnit = index;
  fileNamePassedToParseTranslationUnit = fileName;
  return expectedTranslationUnit;
}

void disposeTranslationUnitDouble(clangTranslationUnit translationUnit)
{
  disposeTranslationUnitCalled = true;
  translationUnitPassedToDisposeTranslationUnit = translationUnit;
}

void disposeIndexDouble(clangIndex index)
{
  disposeIndexCalled = true;
}

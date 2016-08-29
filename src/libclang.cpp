#include "../include/libclang.hpp"
#include <clang-c/Index.h>

DEFINE_FAKE(createIndex)
DEFINE_FAKE(parseTranslationUnit)
DEFINE_FAKE(disposeTranslationUnit)
DEFINE_FAKE(disposeIndex)

clangIndex createIndex()
{
  CALL_FAKE(createIndex, ())
  return clang_createIndex(0, 1);
}

clangTranslationUnit parseTranslationUnit(clangIndex index, const char* fileName)
{
  CALL_FAKE(parseTranslationUnit, (index, fileName))
  return clang_parseTranslationUnit(index, fileName, NULL, 0, NULL, 0,
                                    CXTranslationUnit_None);
}

void disposeTranslationUnit(clangTranslationUnit translationUnit)
{
  CALL_FAKE(disposeTranslationUnit, (translationUnit))
  clang_disposeTranslationUnit((CXTranslationUnit)translationUnit);
}

void disposeIndex(clangIndex index)
{
  CALL_FAKE(disposeIndex, (index))
  clang_disposeIndex(index);
}

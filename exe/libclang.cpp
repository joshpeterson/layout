#include "../include/libclang.hpp"
#include <clang-c/Index.h>

clangIndex createIndex()
{
  return clang_createIndex(0, 1);
}

clangTranslationUnit parseTranslationUnit(clangIndex index, const char* fileName)
{
  return clang_parseTranslationUnit(index, fileName, NULL, 0, NULL, 0,
                                    CXTranslationUnit_None);
}

void disposeTranslationUnit(clangTranslationUnit translationUnit)
{
  clang_disposeTranslationUnit((CXTranslationUnit)translationUnit);
}

void disposeIndex(clangIndex index)
{
  clang_disposeIndex(index);
}

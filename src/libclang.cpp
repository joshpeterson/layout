#include "../include/libclang.hpp"
#include "../include/clang_string.hpp"

DEFINE_FAKE(createIndex)
DEFINE_FAKE(parseTranslationUnit)
DEFINE_FAKE(disposeTranslationUnit)
DEFINE_FAKE(disposeIndex)

CXIndex createIndex()
{
  CALL_FAKE(createIndex, ())
  return clang_createIndex(0, 1);
}

CXTranslationUnit parseTranslationUnit(CXIndex index, const char* fileName)
{
  CALL_FAKE(parseTranslationUnit, (index, fileName))
  return clang_parseTranslationUnit(index, fileName, nullptr, 0, nullptr, 0,
                                    CXTranslationUnit_None);
}

void disposeTranslationUnit(CXTranslationUnit translationUnit)
{
  CALL_FAKE(disposeTranslationUnit, (translationUnit))
  clang_disposeTranslationUnit(translationUnit);
}

void disposeIndex(CXIndex index)
{
  CALL_FAKE(disposeIndex, (index))
  clang_disposeIndex(index);
}

std::string getCursorSpelling(CXCursor cursor)
{
  ClangString cursorSpelling(clang_getCursorSpelling(cursor));
  return cursorSpelling.str();
}

std::string getTypeSpelling(CXType type)
{
  ClangString typeSpelling(clang_getTypeSpelling(type));
  return typeSpelling.str();
}

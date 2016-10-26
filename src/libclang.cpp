#include "../include/libclang.hpp"
#include "../include/clang_string.hpp"
#include <vector>

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
  std::vector<const char*> arguments;
  arguments.push_back("-I/usr/lib/llvm-3.8/lib/clang/3.8.0/include");
  return clang_parseTranslationUnit(index, fileName, arguments.data(),
                                    arguments.size(), nullptr, 0,
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

int64_t getOffsetOfFieldInBytes(CXCursor cursor)
{
  // This call finds the offset in bits.
  return clang_Cursor_getOffsetOfField(cursor) / 8;
}

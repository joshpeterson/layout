#include "../include/libclang.hpp"
#include "../include/clang_string.hpp"
#include <algorithm>
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

CXTranslationUnit parseTranslationUnit(CXIndex index, const char* fileName,
                                       const std::vector<std::string>& arguments)
{
  CALL_FAKE(parseTranslationUnit, (index, fileName, arguments))
  std::vector<const char*> all_arguments;
  all_arguments.push_back("-I/usr/lib/llvm-3.8/lib/clang/3.8/include");
  std::transform(arguments.begin(), arguments.end(),
                 std::back_inserter(all_arguments),
                 [](const std::string& s) { return s.c_str(); });
  return clang_parseTranslationUnit(index, fileName, all_arguments.data(),
                                    all_arguments.size(), nullptr, 0,
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

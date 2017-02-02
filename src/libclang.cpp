#include "../include/libclang.hpp"
#include "../include/clang_string.hpp"
#include "../include/platform.hpp"
#include <algorithm>
#include <vector>

DEFINE_FAKE(CreateIndex)
DEFINE_FAKE(ParseTranslationUnit)
DEFINE_FAKE(DisposeTranslationUnit)
DEFINE_FAKE(DisposeIndex)

CXIndex CreateIndex()
{
  CALL_FAKE(CreateIndex, ())
  return clang_createIndex(0, 1);
}

CXTranslationUnit ParseTranslationUnit(CXIndex index, const char* fileName,
                                       const std::vector<std::string>& arguments)
{
  CALL_FAKE(ParseTranslationUnit, (index, fileName, arguments))
  std::vector<const char*> allArguments;
  allArguments.push_back(SystemIncludeDirectoryArgument);
  std::transform(arguments.begin(), arguments.end(),
                 std::back_inserter(allArguments),
                 [](const std::string& s) { return s.c_str(); });
  return clang_parseTranslationUnit(index, fileName, allArguments.data(),
                                    allArguments.size(), nullptr, 0,
                                    CXTranslationUnit_None);
}

void DisposeTranslationUnit(CXTranslationUnit translationUnit)
{
  CALL_FAKE(DisposeTranslationUnit, (translationUnit))
  clang_disposeTranslationUnit(translationUnit);
}

void DisposeIndex(CXIndex index)
{
  CALL_FAKE(DisposeIndex, (index))
  clang_disposeIndex(index);
}

std::string GetCursorSpelling(CXCursor cursor)
{
  ClangString cursorSpelling(clang_getCursorSpelling(cursor));
  return cursorSpelling.Str();
}

std::string GetTypeSpelling(CXType type)
{
  ClangString typeSpelling(clang_getTypeSpelling(type));
  return typeSpelling.Str();
}

int64_t GetOffsetOfFieldInBytes(CXCursor cursor)
{
  // This call finds the offset in bits.
  return clang_Cursor_getOffsetOfField(cursor) / 8;
}

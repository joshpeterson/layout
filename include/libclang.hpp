#pragma once
#include <clang-c/Index.h>
#include "faking.hpp"
#include <string>

FAKEABLE(CXIndex, createIndex, ())
FAKEABLE(CXTranslationUnit, parseTranslationUnit,
          (CXIndex index, const char* filename))
FAKEABLE(void, disposeTranslationUnit, (CXTranslationUnit translationUnit))
FAKEABLE(void, disposeIndex, (CXIndex index))

std::string getCursorSpelling(CXCursor cursor);
std::string getTypeSpelling(CXType type);

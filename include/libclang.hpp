#pragma once
#include "faking.hpp"
#include <clang-c/Index.h>
#include <cstddef>
#include <string>
#include <vector>

FAKEABLE(CXIndex, createIndex, ())
FAKEABLE(CXTranslationUnit, parseTranslationUnit,
         (CXIndex index, const char* fileName,
          const std::vector<std::string>& arguments))
FAKEABLE(void, disposeTranslationUnit, (CXTranslationUnit translationUnit))
FAKEABLE(void, disposeIndex, (CXIndex index))

std::string getCursorSpelling(CXCursor cursor);
std::string getTypeSpelling(CXType type);
int64_t getOffsetOfFieldInBytes(CXCursor cursor);

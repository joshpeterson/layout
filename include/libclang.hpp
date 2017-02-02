#pragma once
#include "faking.hpp"
#include <clang-c/Index.h>
#include <cstddef>
#include <string>
#include <vector>

FAKEABLE(CXIndex, CreateIndex, ())
FAKEABLE(CXTranslationUnit, ParseTranslationUnit,
         (CXIndex index, const char* fileName,
          const std::vector<std::string>& arguments))
FAKEABLE(void, DisposeTranslationUnit, (CXTranslationUnit translationUnit))
FAKEABLE(void, DisposeIndex, (CXIndex index))

std::string GetCursorSpelling(CXCursor cursor);
std::string GetTypeSpelling(CXType type);
int64_t GetOffsetOfFieldInBytes(CXCursor cursor);

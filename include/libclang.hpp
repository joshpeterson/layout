#pragma once
#include <clang-c/Index.h>
#include "faking.hpp"

FAKEABLE(CXIndex, createIndex, ())
FAKEABLE(CXTranslationUnit, parseTranslationUnit,
          (CXIndex index, const char* filename))
FAKEABLE(void, disposeTranslationUnit, (CXTranslationUnit translationUnit))
FAKEABLE(void, disposeIndex, (CXIndex index))

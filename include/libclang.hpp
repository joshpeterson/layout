#pragma once
#include "faking.hpp"

typedef void* clangIndex;
typedef void* clangTranslationUnit;

FAKEABLE(clangIndex, createIndex, ())
FAKEABLE(clangTranslationUnit, parseTranslationUnit,
          (clangIndex index, const char* filename))
FAKEABLE(void, disposeTranslationUnit, (clangTranslationUnit translationUnit))
FAKEABLE(void, disposeIndex, (clangIndex index))

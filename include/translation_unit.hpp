#pragma once
#include "libclang.hpp"

class TranslationUnit
{
public:
  TranslationUnit(const char* fileName);
  ~TranslationUnit();

private:
  clangIndex index_;
  clangTranslationUnit translationUnit_;
};

#pragma once
#include "libclang.hpp"

class TranslationUnit
{
public:
  TranslationUnit(const char* fileName);
  ~TranslationUnit();

private:
  CXIndex index_;
  CXTranslationUnit translationUnit_;
};

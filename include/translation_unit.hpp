#pragma once
#include "libclang.hpp"
#include <string>
#include <vector>

class TranslationUnit
{
public:
  TranslationUnit(const char* fileName, const std::vector<std::string>& arguments);
  ~TranslationUnit();

  CXTranslationUnit GetCXTranslationUnit() const;
  bool HasError() const;

private:
  CXIndex index_;
  CXTranslationUnit translationUnit_;
  bool hasError_;
};

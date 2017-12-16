#include "../include/translation_unit.hpp"

TranslationUnit::TranslationUnit(const char* fileName,
                                 const std::vector<std::string>& arguments,
                                 bool displayDiagnostics)
{
  hasError_ = false;
  index_ = CreateIndex(displayDiagnostics);
  translationUnit_ = ParseTranslationUnit(index_, fileName, arguments, &hasError_);
}

TranslationUnit::~TranslationUnit()
{
  DisposeTranslationUnit(translationUnit_);
  DisposeIndex(index_);
}

CXTranslationUnit TranslationUnit::GetCXTranslationUnit() const
{
  return translationUnit_;
}

bool TranslationUnit::HasError() const { return hasError_; }

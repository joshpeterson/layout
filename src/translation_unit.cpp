#include "../include/translation_unit.hpp"

TranslationUnit::TranslationUnit(const char* fileName)
{
  index_ = createIndex();
  translationUnit_ = parseTranslationUnit(index_, fileName);
}

TranslationUnit::~TranslationUnit()
{
  disposeTranslationUnit(translationUnit_);
  disposeIndex(index_);
}

CXTranslationUnit TranslationUnit::cxTranslationUnit() const
{
  return translationUnit_;
}

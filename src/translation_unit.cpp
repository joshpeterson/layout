#include "../include/translation_unit.hpp"

TranslationUnit::TranslationUnit(const char* fileName,
                                 const std::vector<std::string>& arguments)
{
  index_ = createIndex();
  translationUnit_ = parseTranslationUnit(index_, fileName, arguments);
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

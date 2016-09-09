#include "../include/type_inspector.hpp"
#include "../include/translation_unit.hpp"

std::vector<TypeInfo> GatherTypes(const char* filename)
{
  TranslationUnit translationUnit(filename);
  return std::vector<TypeInfo>();
}

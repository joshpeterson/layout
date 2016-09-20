#include "../include/type_inspector.hpp"
#include "../include/translation_unit.hpp"
#include "../include/libclang.hpp"

CXChildVisitResult visitor(CXCursor cursor, CXCursor /* parent */,
                            CXClientData clientData)
{
  CXSourceLocation location = clang_getCursorLocation(cursor);
  if(clang_Location_isFromMainFile(location) == 0)
    return CXChildVisit_Continue;

  CXCursorKind cursorKind = clang_getCursorKind(cursor);

  auto types = reinterpret_cast<std::vector<TypeInfo>*>(clientData);
  if (cursorKind == CXCursor_StructDecl)
  {
    TypeInfo typeInfo;
    auto type = clang_getCursorType(cursor);
    auto typeSpelling = clang_getTypeSpelling(type);
    typeInfo.name = clang_getCString(typeSpelling);

    types->push_back(typeInfo);
  }

  clang_visitChildren(cursor, visitor, types);

  return CXChildVisit_Continue;
}

std::vector<TypeInfo> GatherTypes(const char* filename)
{
  TranslationUnit tu(filename);
  auto rootCursor = clang_getTranslationUnitCursor(tu.cxTranslationUnit());

  std::vector<TypeInfo> types;
  clang_visitChildren(rootCursor, visitor, &types);

  return types;
}

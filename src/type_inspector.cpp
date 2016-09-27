#include "../include/type_inspector.hpp"
#include "../include/libclang.hpp"
#include "../include/translation_unit.hpp"

CXChildVisitResult field_visitor(CXCursor cursor, CXCursor /* parent */,
                                 CXClientData clientData)
{
  if (clang_getCursorKind(cursor) == CXCursor_FieldDecl)
  {
    auto type = clang_getCursorType(cursor);
    FieldInfo fieldInfo{getTypeSpelling(type), getCursorSpelling(cursor)};

    auto typeInfo = reinterpret_cast<TypeInfo*>(clientData);
    typeInfo->fields.push_back(fieldInfo);
  }

  return CXChildVisit_Continue;
}

CXChildVisitResult type_visitor(CXCursor cursor, CXCursor /* parent */,
                                CXClientData clientData)
{
  auto cursorKind = clang_getCursorKind(cursor);
  if (cursorKind == CXCursor_StructDecl || cursorKind == CXCursor_ClassDecl)
  {
    auto type = clang_getCursorType(cursor);
    TypeInfo typeInfo{getTypeSpelling(type)};

    clang_visitChildren(cursor, field_visitor, &typeInfo);

    auto types = reinterpret_cast<std::vector<TypeInfo>*>(clientData);
    types->push_back(typeInfo);
  }

  clang_visitChildren(cursor, type_visitor, clientData);

  return CXChildVisit_Continue;
}

std::vector<TypeInfo> GatherTypes(const char* filename)
{
  TranslationUnit tu(filename);
  auto rootCursor = clang_getTranslationUnitCursor(tu.cxTranslationUnit());

  std::vector<TypeInfo> types;
  clang_visitChildren(rootCursor, type_visitor, &types);

  return types;
}

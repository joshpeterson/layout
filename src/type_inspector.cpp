#include "../include/type_inspector.hpp"
#include "../include/translation_unit.hpp"
#include "../include/libclang.hpp"

std::string getCursorSpelling (CXCursor cursor)
{
  auto cursorSpelling = clang_getCursorSpelling(cursor);
  std::string result = clang_getCString(cursorSpelling);

  clang_disposeString(cursorSpelling);
  return result;
}

CXChildVisitResult field_visitor(CXCursor cursor, CXCursor /* parent */,
                                  CXClientData clientData)
{
  if (clang_getCursorKind(cursor) == CXCursor_FieldDecl)
  {
    auto type = clang_getCursorType(cursor);
    auto typeSpelling = clang_getTypeSpelling(type);

    FieldInfo fieldInfo;
    fieldInfo.type = clang_getCString(typeSpelling);
    fieldInfo.name = getCursorSpelling(cursor);
    auto typeInfo = reinterpret_cast<TypeInfo*>(clientData);

    typeInfo->fields.push_back(fieldInfo);

    clang_disposeString(typeSpelling);
  }

  return CXChildVisit_Continue;
}

CXChildVisitResult type_visitor(CXCursor cursor, CXCursor /* parent */,
                                CXClientData clientData)
{
  if (clang_getCursorKind(cursor) == CXCursor_StructDecl)
  {
    auto type = clang_getCursorType(cursor);
    auto typeSpelling = clang_getTypeSpelling(type);

    TypeInfo typeInfo;
    typeInfo.name = clang_getCString(typeSpelling);

    clang_visitChildren(cursor, field_visitor, &typeInfo);

    auto types = reinterpret_cast<std::vector<TypeInfo>*>(clientData);
    types->push_back(typeInfo);

    clang_disposeString(typeSpelling);
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

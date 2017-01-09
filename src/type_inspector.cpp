#include "../include/type_inspector.hpp"
#include "../include/libclang.hpp"
#include "../include/translation_unit.hpp"

static bool is_forward_declaration(CXCursor cursor)
{
  return clang_equalCursors(clang_getCursorDefinition(cursor),
                            clang_getNullCursor());
}

static bool is_from_file_to_inspect(CXCursor cursor)
{
  return clang_Location_isFromMainFile(clang_getCursorLocation(cursor));
}

CXChildVisitResult field_visitor(CXCursor cursor, CXCursor /* parent */,
                                 CXClientData clientData)
{
  if (clang_getCursorKind(cursor) == CXCursor_FieldDecl)
  {
    auto type = clang_getCursorType(cursor);
    auto size = clang_Type_getSizeOf(type);
    auto offset = getOffsetOfFieldInBytes(cursor);
    FieldInfo fieldInfo{getTypeSpelling(type), getCursorSpelling(cursor), size,
                        offset};

    auto typeInfo = reinterpret_cast<TypeInfo*>(clientData);
    typeInfo->fields.push_back(fieldInfo);
  }

  return CXChildVisit_Continue;
}

CXChildVisitResult type_visitor(CXCursor cursor, CXCursor /* parent */,
                                CXClientData clientData)
{
  if (!is_from_file_to_inspect(cursor) || is_forward_declaration(cursor))
    return CXChildVisit_Continue;

  auto cursorKind = clang_getCursorKind(cursor);
  if (cursorKind == CXCursor_StructDecl || cursorKind == CXCursor_ClassDecl)
  {
    auto type = clang_getCursorType(cursor);
    auto size = clang_Type_getSizeOf(type);
    TypeInfo typeInfo{getTypeSpelling(type), size};

    clang_visitChildren(cursor, field_visitor, &typeInfo);

    auto types = reinterpret_cast<std::vector<TypeInfo>*>(clientData);
    types->push_back(typeInfo);
  }

  clang_visitChildren(cursor, type_visitor, clientData);

  return CXChildVisit_Continue;
}

std::vector<TypeInfo> GatherTypes(const char* filename,
                                  const std::vector<std::string>& arguments)
{
  TranslationUnit tu(filename, arguments);
  auto rootCursor = clang_getTranslationUnitCursor(tu.cxTranslationUnit());

  std::vector<TypeInfo> types;
  clang_visitChildren(rootCursor, type_visitor, &types);

  return types;
}

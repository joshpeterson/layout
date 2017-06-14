#include "../include/type_inspector.hpp"
#include "../include/libclang.hpp"
#include "../include/translation_unit.hpp"
#include <algorithm>

static bool IsForwardDeclaration(CXCursor cursor)
{
  return static_cast<bool>(clang_equalCursors(clang_getCursorDefinition(cursor),
                                              clang_getNullCursor()));
}

static bool IsFromFileToInspect(CXCursor cursor)
{
  return static_cast<bool>(
      clang_Location_isFromMainFile(clang_getCursorLocation(cursor)));
}

static bool contains(const std::vector<TypeInfo>& types, unsigned hash)
{
  auto it = std::find_if(types.begin(), types.end(),
                         [hash](const TypeInfo& t) { return t.hash == hash; });
  return it != types.end();
}

CXChildVisitResult FieldVisitor(CXCursor cursor, CXCursor /* parent */,
                                CXClientData clientData)
{
  if (clang_getCursorKind(cursor) == CXCursor_FieldDecl)
  {
    auto type = clang_getCursorType(cursor);
    auto size = clang_Type_getSizeOf(type);
    auto offset = GetOffsetOfFieldInBytes(cursor);
    FieldInfo fieldInfo{GetTypeSpelling(type), GetCursorSpelling(cursor), size,
                        offset};

    auto typeInfo = reinterpret_cast<TypeInfo*>(clientData);
    typeInfo->fields.push_back(fieldInfo);
  }

  return CXChildVisit_Continue;
}

CXChildVisitResult TypeVisitor(CXCursor cursor, CXCursor /* parent */,
                               CXClientData clientData)
{
  if (!IsFromFileToInspect(cursor) || IsForwardDeclaration(cursor))
    return CXChildVisit_Continue;

  auto cursorKind = clang_getCursorKind(cursor);
  if (cursorKind == CXCursor_StructDecl || cursorKind == CXCursor_ClassDecl)
  {
    auto types = reinterpret_cast<std::vector<TypeInfo>*>(clientData);
    auto hash = clang_hashCursor(cursor);
    if (!contains(*types, hash))
    {
      auto type = clang_getCursorType(cursor);
      auto size = clang_Type_getSizeOf(type);
      TypeInfo typeInfo{GetTypeSpelling(type), size, hash};

      clang_visitChildren(cursor, FieldVisitor, &typeInfo);

      types->push_back(typeInfo);
    }
  }

  clang_visitChildren(cursor, TypeVisitor, clientData);

  return CXChildVisit_Continue;
}

std::vector<TypeInfo> GatherTypes(const char* filename,
                                  const std::vector<std::string>& arguments,
                                  bool* error, bool displayDiagnostics)
{
  TranslationUnit tu(filename, arguments, displayDiagnostics);

  std::vector<TypeInfo> types;
  if (!tu.HasError())
  {
    clang_visitChildren(clang_getTranslationUnitCursor(tu.GetCXTranslationUnit()),
                        TypeVisitor, &types);
  }
  else if (error != nullptr)
  {
    *error = true;
  }

  return types;
}

#include "../include/type_inspector.hpp"
#include "../include/libclang.hpp"
#include "../include/translation_unit.hpp"
#include <algorithm>

static bool IsForwardDeclaration(CXCursor cursor)
{
  auto definition = clang_getCursorDefinition(cursor);

  // If the definition is null, then there is no definition in this translation
  // unit, so this cursor must be a forward declaration.
  if (clang_equalCursors(definition, clang_getNullCursor()))
    return true;

  // If there is a definition, then the forward declaration and the definition
  // are in the same translation unit. This cursor is the forward declaration if
  // it is _not_ the definition.
  return !clang_equalCursors(cursor, definition);
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

static bool IsAnonymousType(CXCursor cursor)
{
  if (clang_Cursor_isAnonymous(cursor))
    return true;

  // For a reason I don't understand, clang_Cursor_isAnonymous returns false
  // when an anonymous type has an int32_t field. Add another check for the name
  // of the type to ensure that we don't process the anonymous type.
  auto type = clang_getCursorType(cursor);
  if (GetTypeSpelling(type).find("::(anonymous") != std::string::npos)
    return true;
  return false;
}

CXChildVisitResult FieldVisitor(CXCursor cursor, CXCursor /* parent */,
                                CXClientData clientData)
{
  auto typeInfo = reinterpret_cast<TypeInfo*>(clientData);
  auto cursorKind = clang_getCursorKind(cursor);
  if (cursorKind == CXCursor_FieldDecl)
  {
    auto type = clang_getCursorType(cursor);
    auto size = clang_Type_getSizeOf(type);
    auto offset = GetOffsetOfFieldInBytes(cursor);
    FieldInfo fieldInfo{GetTypeSpelling(type), GetCursorSpelling(cursor), size,
                        offset};

    typeInfo->fields.push_back(fieldInfo);
  }
  else if (cursorKind == CXCursor_UnionDecl ||
           cursorKind == CXCursor_StructDecl)
  {
    clang_visitChildren(cursor, FieldVisitor, typeInfo);
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
    if (!contains(*types, hash) && !IsAnonymousType(cursor))
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

TypesResult GatherTypes(const char* filename,
                        const std::vector<std::string>& arguments,
                        bool displayDiagnostics)
{
  TranslationUnit tu(filename, arguments, displayDiagnostics);

  std::vector<TypeInfo> types;
  clang_visitChildren(clang_getTranslationUnitCursor(tu.GetCXTranslationUnit()),
                      TypeVisitor, &types);
  return {types, tu.HasError()};
}

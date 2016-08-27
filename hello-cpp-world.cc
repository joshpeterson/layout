#include <iostream>
#include <cstddef>
#include <string>
#include <clang-c/Index.h>

using namespace std;

std::string getCursorKindName( CXCursorKind cursorKind )
{
  CXString kindName  = clang_getCursorKindSpelling( cursorKind );
  std::string result = clang_getCString( kindName );

  clang_disposeString( kindName );
  return result;
}

std::string getCursorSpelling( CXCursor cursor )
{
  CXString cursorSpelling = clang_getCursorSpelling( cursor );
  std::string result      = clang_getCString( cursorSpelling );

  clang_disposeString( cursorSpelling );
  return result;
}

CXChildVisitResult visitor( CXCursor cursor, CXCursor /* parent */, CXClientData clientData )
{
  CXSourceLocation location = clang_getCursorLocation( cursor );
  if( clang_Location_isFromMainFile( location ) == 0 )
    return CXChildVisit_Continue;

  CXCursorKind cursorKind = clang_getCursorKind( cursor );

  unsigned int curLevel  = *( reinterpret_cast<unsigned int*>( clientData ) );
  unsigned int nextLevel = curLevel + 1;
  
  if (cursorKind == CXCursor_FieldDecl)
  {
    CXType type = clang_getCursorType(cursor);
    CXString typeSpelling = clang_getTypeSpelling(type);
    std::string typeSpellingStr = clang_getCString(typeSpelling);
    
    std::cout << std::string( curLevel, '-' ) << " " << getCursorKindName(
    cursorKind ) << " (" << typeSpellingStr << "," << getCursorSpelling( cursor ) << ")\n";
  }
  else
  {
    std::cout << std::string( curLevel, '-' ) << " " << getCursorKindName(
    cursorKind ) << " (" << getCursorSpelling( cursor ) << ")\n";
  }

  clang_visitChildren( cursor,
                       visitor,
                       &nextLevel ); 

  return CXChildVisit_Continue;
}

int main()
{
  std::cout << "Here 1\n";
  CXIndex index        = clang_createIndex( 0, 1 );
  std::cout << "Here 1.1\n";
  CXTranslationUnit tu = clang_parseTranslationUnit(index,
      "/home/josh/layout/test.cpp", NULL, 0, NULL, 0, CXTranslationUnit_None );
  std::cout << "Here 1.3\n";
  if( !tu )
  {
    std::cout << "Here 2\n";
    return -1;
  }

  std::cout << "Here 3\n";
  CXCursor rootCursor  = clang_getTranslationUnitCursor( tu );

  unsigned int treeLevel = 0;

  clang_visitChildren( rootCursor, visitor, &treeLevel );

  clang_disposeTranslationUnit( tu );
  clang_disposeIndex( index );
  return 0;
}


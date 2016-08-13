#pragma once

typedef void* clangIndex;
typedef void* clangTranslationUnit;

clangIndex createIndex();
clangTranslationUnit parseTranslationUnit(clangIndex index, const char* filename);
void disposeTranslationUnit(clangTranslationUnit translationUnit);
void disposeIndex(clangIndex index);

#pragma once

const clangIndex expectedIndex = reinterpret_cast<clangIndex>(1);
const clangTranslationUnit expectedTranslationUnit =
        reinterpret_cast<clangTranslationUnit>(1);

clangIndex createIndexDouble();
clangTranslationUnit parseTranslationUnitDouble(clangIndex index,
                                                const char* fileName);
void disposeTranslationUnitDouble(clangTranslationUnit translationUnit);
void disposeIndexDouble(clangIndex index);

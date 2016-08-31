#pragma once

const CXIndex expectedIndex = reinterpret_cast<CXIndex>(1);
const CXTranslationUnit expectedTranslationUnit =
        reinterpret_cast<CXTranslationUnit>(1);

CXIndex createIndexDouble();
CXTranslationUnit parseTranslationUnitDouble(CXIndex index,
                                                const char* fileName);
void disposeTranslationUnitDouble(CXTranslationUnit translationUnit);
void disposeIndexDouble(CXIndex index);

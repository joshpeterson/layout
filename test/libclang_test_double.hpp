#pragma once

#include "../include/libclang.hpp"
#include <string>
#include <vector>

const CXIndex expectedIndex = reinterpret_cast<CXIndex>(1);
const CXTranslationUnit expectedTranslationUnit =
    reinterpret_cast<CXTranslationUnit>(1);

CXIndex CreateIndexDouble(bool displayDiagnostics);
ParseResult ParseTranslationUnitDouble(CXIndex index, const char* fileName,
                                       const std::vector<std::string>& arguments);
void DisposeTranslationUnitDouble(CXTranslationUnit translationUnit);
void DisposeIndexDouble(CXIndex index);

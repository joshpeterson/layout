#include "../include/clang_string.hpp"

ClangString::ClangString(CXString value) : value_(value) {}

ClangString::~ClangString() { clang_disposeString(value_); }
std::string ClangString::Str() const { return clang_getCString(value_); }

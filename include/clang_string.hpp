#pragma once
#include "libclang.hpp"
#include <string>

class ClangString
{
public:
  explicit ClangString(CXString value);
  ~ClangString();

  std::string Str() const;

private:
  CXString value_;
};

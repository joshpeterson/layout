#pragma once
#include "../include/libclang.hpp"
#include "field_info.hpp"
#include <string>
#include <vector>

struct TypeInfo
{
  std::string name;
  long long size; // in bytes
  unsigned hash;
  std::vector<FieldInfo> fields;
};

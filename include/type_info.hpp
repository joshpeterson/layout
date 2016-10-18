#pragma once
#include "field_info.hpp"
#include <string>
#include <vector>

struct TypeInfo
{
  std::string name;
  long long size;
  std::vector<FieldInfo> fields;
};

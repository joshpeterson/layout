#pragma once
#include "field_info.hpp"
#include <string>
#include <vector>

struct TypeInfo
{
  std::string name;
  std::vector<FieldInfo> fields;
};

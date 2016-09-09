#pragma once
#include <string>
#include <vector>
#include "field_info.hpp"

struct TypeInfo
{
  std::string name;
  std::vector<FieldInfo> fields;
};

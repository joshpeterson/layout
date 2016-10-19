#pragma once
#include <string>

struct FieldInfo
{
  std::string type;
  std::string name;
  long long size;   // in bytes
  long long offset; // in bytes
};

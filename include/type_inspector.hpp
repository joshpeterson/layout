#pragma once
#include "type_info.hpp"
#include <string>
#include <vector>

struct TypesResult
{
  std::vector<TypeInfo> types;
  bool error;
};

TypesResult GatherTypes(const char* filename,
                        const std::vector<std::string>& arguments,
                        bool displayDiagnostics = true);

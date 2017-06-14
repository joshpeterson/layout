#pragma once
#include "type_info.hpp"
#include <string>
#include <vector>

std::vector<TypeInfo> GatherTypes(const char* filename,
                                  const std::vector<std::string>& arguments,
                                  bool* error, bool displayDiagnostics = true);

#pragma once
#include "type_info.hpp"
#include <ostream>
#include <string>
#include <vector>

std::vector<std::string> CodeForStrings(const std::vector<TypeInfo>& types);
void OutputString(const std::vector<TypeInfo>& types, const char* filename,
                  std::ostream& out);

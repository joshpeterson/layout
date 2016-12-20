#pragma once
#include <ostream>
#include <string>
#include <vector>

int ComputeLayout(const char* filename, const std::vector<std::string>& arguments,
                  std::ostream& out);

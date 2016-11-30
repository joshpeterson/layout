#pragma once
#include "type_info.hpp"
#include <ostream>
#include <string>
#include <vector>

std::string MarkdownFor(const std::vector<TypeInfo>& types);
void OutputMarkdown(const std::vector<TypeInfo>& types, std::ostream& out);

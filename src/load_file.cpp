#include "../include/load_file.hpp"
#include <fstream>
#include <sstream>

std::string LoadFile(const char* filename)
{
  std::ifstream file(filename);
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

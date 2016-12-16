#pragma once
#include "type_info.hpp"
#include <algorithm>
#include <ostream>
#include <string>
#include <vector>

void OutputString(const std::vector<TypeInfo>& types, const char* filename,
                  std::ostream& out);

std::string EmitFieldCount(const std::string& typeName, int numberOfFields);
std::string EmitFieldArrayStart(const std::string& typeName, int numberOfFields);
std::string EmitFieldArrayEnd();
std::string EmitFieldArrayEntry(const std::string& typeName,
                                const FieldInfo& field);
std::string EmitFieldInformationStruct();
std::string EmitTypeNameAndSize(const TypeInfo& typeInfo);
std::string EmitForLoopStart(const std::string& typeName);
std::string EmitForLoopEnd();
std::string EmitEmptyLine();

struct ColumnWidths
{
  size_t type;
  size_t name;
  size_t size;
  size_t offset;
  size_t padding;
};

std::string EmitHeaderRow(const ColumnWidths& widths);
std::string EmitFieldOutput(const ColumnWidths& widths);

ColumnWidths ComputeColumnWidths(const std::vector<FieldInfo>& fields);
size_t FindLongestFieldTypeName(const std::vector<FieldInfo>& fields);
size_t FindLongestFieldName(const std::vector<FieldInfo>& fields);
size_t FindLongestFieldSize(const std::vector<FieldInfo>& fields);
size_t FindLongestFieldOffset(const std::vector<FieldInfo>& fields);

template <typename Lambda>
size_t FindLongestFieldEntryName(const std::vector<FieldInfo>& fields,
                                 Lambda selector, size_t minimum)
{
  size_t largest = minimum;
  for (auto field : fields)
    largest = std::max(largest, selector(field).size());

  return largest;
}

#pragma once
#include <cstdio>

class TempSourceFile
{
public:
  TempSourceFile(const char* filename, const char* source) : filename_(filename)
  {
    auto tempFile = fopen(filename_, "w");
    std::fputs(source, tempFile);
    fclose(tempFile);
  }

  ~TempSourceFile()
  {
    std::remove(filename_);
  }

private:
  const char* filename_;
};

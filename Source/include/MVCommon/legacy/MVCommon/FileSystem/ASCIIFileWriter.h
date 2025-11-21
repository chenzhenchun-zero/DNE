#pragma once
#include "FileWriter.h"

namespace MVCommon
{
  class ASCIIFileWriter : public FileWriter
  {
  public:
    MVCOMMON_API ASCIIFileWriter(const char* filePath, const char* lineBreak = "\n");
    MVCOMMON_API virtual ~ASCIIFileWriter();

    MVCOMMON_API bool WriteLine(const char* str) const;

  private:
    std::string _lineBreak;
  };
}


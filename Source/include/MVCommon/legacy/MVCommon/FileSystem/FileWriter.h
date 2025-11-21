#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <string>

namespace MVCommon
{
  class FileWriter
  {
  public:
    MVCOMMON_API FileWriter(const char* filePath);
    MVCOMMON_API virtual ~FileWriter();

    MVCOMMON_API bool IsReady() const;
    MVCOMMON_API void CloseFile();
    MVCOMMON_API bool Write(void* pSrcBuf, uint32_t numBytes) const;

  protected:
    MVCOMMON_API static int openFile(const char* filePath);
    MVCOMMON_API static void closeFile(int& fileHandle);

    int _fileHandle;
    std::string _filePath;
  };
}


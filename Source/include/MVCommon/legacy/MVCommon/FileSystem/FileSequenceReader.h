#pragma once
#include <MVCommon/MVCommonAPI.h>
#include <string>
#include <vector>

namespace MVCommon
{
  class FileSequenceReader
  {
  public:
    MVCOMMON_API FileSequenceReader(const char* directory, const char* extension, bool subDir = true);
    MVCOMMON_API FileSequenceReader(const char* directory, std::vector<std::string> extensions, bool subDir = true);
    MVCOMMON_API virtual ~FileSequenceReader(void);
    MVCOMMON_API std::string GetFilePath(int i) const;
    MVCOMMON_API int GetNumFilesFromStart();
    MVCOMMON_API int GetNumFilesInDirectory();

    // number in filepath that is used for the first file (not necessarily 0)
    MVCOMMON_API int GetStartIndex() const;

  protected:
    std::string _filePattern;
    std::string findFilePattern(const char* rootDir, bool subDir);
    static std::string FindFileSubdir(const char* rootDir, const char* extension);
    static std::string FindFile(const char* rootDir, const char* extension);

    int _recentIndex;

  private:
    void initStartIndex();
    int _numFiles;
    int _startIndex;
    std::vector<std::string> _extensions;
  };
}


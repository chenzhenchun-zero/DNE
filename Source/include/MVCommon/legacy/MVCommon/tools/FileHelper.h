#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <vector>

#include <string>
#include <sstream>
#include <iostream>

const std::string correct_filepath_separator_string = "/";
const std::string wrong_filepath_separator_string = "\\";
const char correct_filepath_separator_char = '/';
const char wrong_filepath_separator_char = '\\';

namespace MVCommon
{
  class FileHelper
  {
  public:

    // ----------------------------- directory ----------------------------

    MVCOMMON_API static bool IsDirectory(const char* filePath);

    MVCOMMON_API static int MakeDirectory(const char* filePath);

    MVCOMMON_API static std::string const & GetAppExeFilePath();

    MVCOMMON_API static std::string GetDirectory(const char* filePath);

    MVCOMMON_API static std::string GetFileNameWithoutDirectory(const char* filePath, bool includeExtension = true);

    MVCOMMON_API static void SetAppExeDirectory(std::string const &path);

    MVCOMMON_API static std::string const & GetAppExeDirectory();

    MVCOMMON_API static std::string GetDataDirectory();

    MVCOMMON_API static void SetDataDirectory(const std::string& dataDirectory);

    MVCOMMON_API static std::string GetFullPath(const char* filePath);
    MVCOMMON_API static std::string GetRelativePath(const char* childPath, const char* parentPath);
    
    MVCOMMON_API static bool GetDirFileNames(const char* directory, std::vector<std::string>& fileNames);
    MVCOMMON_API static bool GetDirectoryContent(const char* directory, std::vector<std::string>& directoryItems);

    // ----------------------------- direct file access ----------------------------

    MVCOMMON_API static bool Delete(const char* filePath);

    MVCOMMON_API static bool DeleteDirectory(const char* path);

    MVCOMMON_API static void CloseFile(int& fileHandle);

    // possible values for origin are: SEEK_SET, SEEK_CUR, SEEK_END
    MVCOMMON_API static uint64_t Seek(int fileHandle, uint64_t offset, int origin);

    MVCOMMON_API static int Read(int fileHandle, void* pDestBuf, uint32_t numBytes);

    MVCOMMON_API static uint64_t Write(int fileHandle, void* pSrcBuf, uint32_t numBytes);

    MVCOMMON_API static int ReadLine(int fileHandle, std::string& strLine);

    MVCOMMON_API static bool DoesFileExist(const char* filePath, bool checkIfFileSizeIsBiggerThanZero = false, const char* ending = nullptr);

    // returns fileHandle. -1 if invalid
    MVCOMMON_API static int OpenFileReadOnly(const char* filePath);

    // returns fileHandle. -1 if invalid or if file size is 0 bytes
    MVCOMMON_API static int OpenFileReadOnly(const char* filePath, uint64_t& fileLen);

    // returns fileHandle. -1 if invalid
    MVCOMMON_API static int OpenFileForWriting(const char* filePath);

    MVCOMMON_API static uint64_t GetFileSize(const char* filePath);

    // ----------------------------- other helper functions ----------------------------

    // caller is responsible to delete the returned buffer!
    MVCOMMON_API static char* ReadFileContentToByteArray(const char* filePath, uint32_t& numBytes, bool appendZero = false);
    MVCOMMON_API static bool WriteFileContentFromString(const char* filePath, const char* filecontent);

    MVCOMMON_API static std::string ReadFileToString(const char *filePath);

    MVCOMMON_API static bool FileCopy(const char* source, const char* dest, uint32_t bufferSize = 100 * 1024 * 1024);//100M

    MVCOMMON_API static bool FileMove(const char* source, const char* dest);

    MVCOMMON_API static bool FileRename(const char* source, const char* dest);

    MVCOMMON_API static std::string MakeCompatible(const char* path);

    MVCOMMON_API static std::string CombinePath(const char* path1, const char* path2);

    MVCOMMON_API static std::string GetExtension(const char* filePath);

    MVCOMMON_API static std::string GetExtensionInLowerCase(const char* filePath);

    MVCOMMON_API static std::string RemoveExtension(const char* filePath);

    MVCOMMON_API static std::string RemovePath(const char* filePath);

    MVCOMMON_API static std::string MakeEndsWith(const char* filePath, const char* ending);

    MVCOMMON_API static uint64_t GetModifiedTime(const char* filePath);

    MVCOMMON_API static bool IsFileOpened(const char *filepath);

    MVCOMMON_API static uint64_t CreateHash(const char *filepath);
  };
}


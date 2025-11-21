#pragma once
#include <MVCommon/MVCommonAPI.h>
#include <string>

namespace MVCommon
{
  class Mv4dDefinitions
  {
  public:
    MVCOMMON_API static std::string GetMV4DRigFileName();
    MVCOMMON_API static std::string GetMV4DColorRigFileName();
    MVCOMMON_API static std::string GetMV4DConfigFileName();
    MVCOMMON_API static std::string GetMV4DPhotogrammetryFileName();
    MVCOMMON_API static std::string GetMV4DGraphFileName();

    MVCOMMON_API static std::string GetMV4DColorRig2FileName();
    MVCOMMON_API static std::string GetMV4DColorRigC2CFileName();

    static std::string MV4DRigFileName;
    static std::string MV4DColorRigFileName;
    static std::string MV4DConfigFileName;
    static std::string MV4DPhotogrammetryFileName;
    static std::string MV4DGraphFileName;

    static std::string MV4DColorRig2FileName;
    static std::string MV4DColorRigC2CFileName;
  };
}

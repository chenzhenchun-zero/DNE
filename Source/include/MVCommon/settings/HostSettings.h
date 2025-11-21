/// \cond
#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>
#include <MVCommon/utils/String.h>

namespace MVCommon
{
  struct HostSettingsImpl;

  class HostSettings : public NonAssignable
  {
  private:
    HostSettings();

  public:
    MVCOMMON_API static HostSettings& GetInstance();
    MVCOMMON_API virtual ~HostSettings();

    MVCOMMON_API bool AmILord();

    MVCOMMON_API int32_t GetHostId() const;
    MVCOMMON_API void SetHostId(int32_t i);
    MVCOMMON_API static bool IsLocalHostId(int32_t hostId);

    MVCOMMON_API String GetHostName() const;

    MVCOMMON_API String GetHostSettingsDir(bool asPathWithoutVars = true) const;
    MVCOMMON_API bool SetHostSettingsDir(String const & hostSettingsDir);

    MVCOMMON_API String GetHostLocalStorageDir(bool asPathWithoutVars = true) const;
    MVCOMMON_API bool SetHostLocalStorageDir(String const & hostLocalStorageDir);

    MVCOMMON_API String GetHostRemoteStorageDir(bool asPathWithoutVars = true) const;
    MVCOMMON_API bool SetHostRemoteStorageDir(String const & hostRemoteStorageDir);

    MVCOMMON_API String GetHostLocalGraphsDir(bool asPathWithoutVars = true) const;
    MVCOMMON_API bool SetHostLocalGraphsDir(String const & hostLocalGraphsDir);

    MVCOMMON_API String GetGalleryDirs(bool asPathWithoutVars = true) const;
    MVCOMMON_API bool SetGalleryDirs(String const & galleryDirs);

    MVCOMMON_API String GetSessionName() const;
    MVCOMMON_API void SetSessionName(String const & sessionName);

    MVCOMMON_API bool GetAutoLoadGraphOnStartup() const;
    MVCOMMON_API void SetAutoLoadGraphOnStartup(bool autoLoadGraphOnStartup);

    MVCOMMON_API bool GetEnableStreamSelection() const;
    MVCOMMON_API void SetEnableStreamSelection(bool streamSelection);

    MVCOMMON_API uint32_t GetGatewayRPCTimeout() const;
    MVCOMMON_API void SetGatewayRPCTimeout(uint32_t gatewayRPCTimeout);

    MVCOMMON_API bool GetWatchdogRestart() const;
    MVCOMMON_API void SetWatchdogRestart(bool watchdogRestart);

    MVCOMMON_API uint32_t GetWatchdogTimerInterval() const;
    MVCOMMON_API void SetWatchdogTimerInterval(uint32_t watchdogTimerInterval);

    MVCOMMON_API bool GetEnableMVNet() const;
    MVCOMMON_API void SetEnableMVNet(bool enableMVNet);

    MVCOMMON_API String GetNucTransmitterCommandsAddress() const;
    MVCOMMON_API String GetNucTransmitterDataAddress() const;
    MVCOMMON_API String GetLordTransmitterAddress1() const;
    MVCOMMON_API bool SetLordTransmitterAddress1(String const & address);
    MVCOMMON_API String GetLordTransmitterAddress2() const;
    MVCOMMON_API bool SetLordTransmitterAddress2(String const & address);

    MVCOMMON_API bool GetEnableHttpServer() const;
    MVCOMMON_API void SetEnableHttpServer(bool enableHttpServer);

    MVCOMMON_API void ReadFromFile();
    MVCOMMON_API void WriteToFile() const;

    MVCOMMON_API String GetStudioFileName() const;
    MVCOMMON_API void SetStudioFileName(String const & studioFileName);

  private:
    HostSettingsImpl * _pImpl;
  };
}
/// \endcond
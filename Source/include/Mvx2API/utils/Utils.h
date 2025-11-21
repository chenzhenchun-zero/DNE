/// \file
#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/utils/String.h>
#include <MVCommon/logger/WeakLoggerPtr.h>
#include <MVCommon/guid/SharedGuidAliasDatabasePtr.h>

namespace Mvx2API
{
  namespace Utils
  {
    /// \brief Sets the MVX logger instance.
    /// \details
    /// \par
    /// Replaces the previous logger instance if there was any.
    /// \par
    /// There is no logger instance set by default - it is a responsibility of the application to install one.
    /// \param wpLogger a weak pointer to the new logger instance
    MVX2_API void SetMVXLoggerInstance(MVCommon::WeakLoggerPtr wpLogger);
    /// \brief Resets the MVX logger instance.
    /// \details No logs will be generated.
    MVX2_API void ResetMVXLoggerInstance();
    /// \brief Accesses current MVX logger instance.
    /// \returns  weak pointer to the current MVX logger instance
    MVX2_API MVCommon::WeakLoggerPtr GetMVXLoggerInstance();

    /// \brief A getter of the database containing MVX2 framework's internal guids and their aliases.
    /// \returns  a database of guids and their aliases
    MVX2_API MVCommon::SharedGuidAliasDatabasePtr GetMVXGuidAliasDatabase();

    /// \brief Returns path of the application's executable file.
    /// \returns  executable file path
    MVX2_API MVCommon::String GetAppExeFilePath();
    /// \brief Returns directory of the application's executable file.
    /// \returns  executable directory
    MVX2_API MVCommon::String GetAppExeDirectory();
  };
}
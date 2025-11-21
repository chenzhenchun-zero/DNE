/// \file
#pragma once

#include <Mvx2API/Mvx2API.h>

namespace MVCommon
{
  class String;
}

namespace Mvx2API
{
  namespace PluginsLoader
  {
    /// \brief Loads all MVX plugins from a specified folder.
    /// \param folder           a folder containing MVX plugins
    /// \param checkCacheFile   an indication whether to check existing cache file of plugins and their filters
    /// \param storeCacheFile   an indication whether to store information about plugins and their filters into a cache file
    /// \param checkSubfolders  if true, checks also subfolders of the folder
    MVX2_API void LoadPluginsInFolder(MVCommon::String const & folder, bool checkCacheFile = false, bool storeCacheFile = false, bool checkSubfolders = true);

    /// \brief Loads single MVX plugin specified by its path.
    /// \param pluginPath a path to the plugin
    MVX2_API void LoadPlugin(MVCommon::String const & pluginPath);
  };
}
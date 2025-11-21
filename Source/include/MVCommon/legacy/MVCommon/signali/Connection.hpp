#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <functional>

namespace MVCommon
{
namespace signali
{
  class Connection
  {
    using Disconnect = std::function<void()>;

  public:
    MVCOMMON_API Connection();
    MVCOMMON_API Connection(Connection const &that);
    MVCOMMON_API Connection(Disconnect disconnect);

    MVCOMMON_API bool connected() const;
    MVCOMMON_API void disconect();
    MVCOMMON_API void swap(Connection &that);
    MVCOMMON_API Connection& operator =(Connection const &that);

  private:
    Disconnect m_Disconnect;
  };

  class ScopedConnection
    : public Connection
  {
  public:
    MVCOMMON_API ScopedConnection();
    MVCOMMON_API ScopedConnection(Connection const &that);
    MVCOMMON_API ScopedConnection(ScopedConnection const &that);
    MVCOMMON_API ~ScopedConnection();

    MVCOMMON_API Connection release();
    MVCOMMON_API void swap(ScopedConnection &that);
    MVCOMMON_API ScopedConnection& operator =(Connection const &that);
    MVCOMMON_API ScopedConnection& operator =(ScopedConnection const &that);
    

  private:
    mutable bool m_bReleased;
  };

} //namespace signali
} //namespace MVBase
#pragma once

#include <Mvx2BasicIO/Mvx2BasicIO.h>
#include <Mvx2API/graphnodes/SingleFilterGraphNode.h>

namespace Mvx2BasicIO
{
  /// \brief A target graph node for transmission of frames via network.
  /// \details
  /// \par
  /// Internally maintains a single transmitting filter. The same filter is reused even when the graph node is added to multiple graphs.
  /// \par
  /// Supports counting of dropped atoms.
  class NetworkTransmitterGraphNode : public Mvx2API::SingleFilterGraphNode
  {
  public:
    /// \brief A constructor.
    /// \param commandsSocket     a socket for communication with receivers (e.g. 'tcp://192.168.1.1:5555')
    /// \param dataSocket         a socket for data transmission (e.g. 'tcp://192.168.1.1:5556')
    /// \param sendBufferCapacity a capacity of the underlying socket's send-buffer
    /// \param enableTransmission an indication whether the transmission shall be enabled right away
    /// \param enableIPv6         enables IPv6 support - unless enabled, only IPv4 communication will work
    MVX2BASICIO_API NetworkTransmitterGraphNode(MVCommon::String const & commandsSocket, MVCommon::String const & dataSocket,
      uint32_t sendBufferCapacity = 2, bool enableTransmission = true, bool enableIPv6 = false);
    /// \brief A constructor.
    /// \param unsupportedReceiverProtocolVersions
    /// a comma-separated string for specifying which protocol version receivers the transmitter shall not respond to
    /// \param commandsSocket     a socket for communication with receivers (e.g. 'tcp://192.168.1.1:5555')
    /// \param dataSocket         a socket for data transmission (e.g. 'tcp://192.168.1.1:5556')
    /// \param sendBufferCapacity a capacity of the underlying socket's send-buffer
    /// \param enableTransmission an indication whether the transmission shall be enabled right away
    /// \param enableIPv6         enables IPv6 support - unless enabled, only IPv4 communication will work
    MVX2BASICIO_API NetworkTransmitterGraphNode(MVCommon::String const & unsupportedReceiverProtocolVersions,
      MVCommon::String const & commandsSocket, MVCommon::String const & dataSocket, 
      uint32_t sendBufferCapacity = 2, bool enableTransmission = true, bool enableIPv6 = false);
    /// \brief A destructor.
    MVX2BASICIO_API virtual ~NetworkTransmitterGraphNode();

    /// \brief Changes the specification of which protocol version receivers the transmitter shall not respond to.
    /// \param unsupportedReceiverProtocolVersions
    /// a comma-separated string of protocol versions, or empty string if all versions receivers can be responded to
    MVX2BASICIO_API void SetUnsupportedReceiverProtocolVersions(MVCommon::String const & unsupportedReceiverProtocolVersions) const;

    /// \brief Changes the sockets of the transmitter.
    /// \param commandsSocket a new socket for communication with receivers (e.g. 'tcp://192.168.1.1:5555')
    /// \param dataSocket     a new socket for data transmission (e.g. 'tcp://192.168.1.1:5556')
    /// \param enableIPv6     enables IPv6 support - unless enabled, only IPv4 communication will work
    MVX2BASICIO_API void SetSockets(MVCommon::String const & commandsSocket, MVCommon::String const & dataSocket, bool enableIPv6 = false) const;

    /// \brief Enables/disables actual frames transmission.
    /// \param enable true in order to enable transmission, false in order to disable it
    MVX2BASICIO_API void EnableTransmission(bool enable = true) const;
    /// \brief Returns a count of dropped (not transmitted) atoms.
    /// \returns  the count of dropped atoms
    MVX2BASICIO_API uint64_t GetDroppedAtomsCount() const;
    /// \brief Resets the internal counter of dropped (not transmitted) atoms.
    MVX2BASICIO_API void ResetDroppedAtomsCounter() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2BASICIO_API)
  };
}


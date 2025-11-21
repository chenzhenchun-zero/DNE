#pragma once

#include <Mvx2BasicIO/Mvx2BasicIO.h>
#include <Mvx2API/graphnodes/SingleFilterGraphNode.h>

namespace Mvx2BasicIO
{
  /// \brief A source graph node for reception of frames via network.
  /// \details
  /// Internally maintains a single receiving filter. The same filter is reused even when the graph node is added to multiple graphs.
  class NetworkReceiverGraphNode : public Mvx2API::SingleFilterGraphNode
	{
  public:
    /// \brief A constructor.
    /// \param commandsSocket         a socket for communication with transmitter (e.g. 'tcp://192.168.1.1:5555')
    /// \param dataSocket             a socket for data reception (e.g. 'tcp://192.168.1.1:5556')
    /// \param receiveBufferCapacity  a capacity of the underlying socket's receive-buffer
    /// \param responseReceiveTimeout an interval to wait for response from transmitter until the connection is considered unavailable (in ms)
    /// \param enableIPv6             enables IPv6 support - unless enabled, only IPv4 communication will work
    MVX2BASICIO_API NetworkReceiverGraphNode(MVCommon::String const & commandsSocket, MVCommon::String const & dataSocket,
      uint32_t receiveBufferCapacity = 5, int64_t responseReceiveTimeout = 3000, bool enableIPv6 = false);
    /// \brief A constructor.
    /// \param unsupportedTransmitterProtocolVersions
    /// a comma-separated string for specifying which protocol version transmitters the receiver shall not respond to
    /// \param commandsSocket         a socket for communication with transmitter (e.g. 'tcp://192.168.1.1:5555')
    /// \param dataSocket             a socket for data reception (e.g. 'tcp://192.168.1.1:5556')
    /// \param receiveBufferCapacity  a capacity of the underlying socket's receive-buffer
    /// \param responseReceiveTimeout an interval to wait for response from transmitter until the connection is considered unavailable (in ms)
    /// \param enableIPv6             enables IPv6 support - unless enabled, only IPv4 communication will work
    MVX2BASICIO_API NetworkReceiverGraphNode(MVCommon::String const & unsupportedTransmitterProtocolVersions,
      MVCommon::String const & commandsSocket, MVCommon::String const & dataSocket,
      uint32_t receiveBufferCapacity = 5, int64_t responseReceiveTimeout = 3000, bool enableIPv6 = false);
    /// \brief A destructor.
    MVX2BASICIO_API virtual ~NetworkReceiverGraphNode();

    /// \brief Changes the specification of which protocol version transmitters the receiver shall not respond to.
    /// \param unsupportedTransmitterProtocolVersions
    /// a comma-separated string of protocol versions, or empty string if all versions transmitters can be responded to
    MVX2BASICIO_API void SetUnsupportedTransmitterProtocolVersions(MVCommon::String const & unsupportedTransmitterProtocolVersions) const;

    /// \brief Changes the sockets of the receiver.
    /// \param commandsSocket a new socket for communication with transmitter (e.g. 'tcp://192.168.1.1:5555')
    /// \param dataSocket     a new socket for data reception (e.g. 'tcp://192.168.1.1:5556')
    /// \param enableIPv6     enables IPv6 support - unless enabled, only IPv4 communication will work
    MVX2BASICIO_API void SetSockets(MVCommon::String const & commandsSocket, MVCommon::String const & dataSocket, bool enableIPv6 = false) const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2BASICIO_API)
	};
}


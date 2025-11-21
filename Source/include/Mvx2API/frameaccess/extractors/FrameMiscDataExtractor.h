/// \file
#pragma once

#include <Mvx2API/Mvx2API.h>

#include <MVCommon/guid/Guid.h>

namespace MVCommon
{
  struct Matrix4x4f;
  struct CameraParams;
}

namespace Mvx2API
{
  class Frame;

  namespace FrameMiscDataExtractor
  {
    /// \brief Gets color camera parameters of a frame.
    /// \param frame        a frame
    /// \param cameraParams a target to store the camera parameters in
    /// \param purposeGuid  a purpose guid of data to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns            true if the frame contains color camera parameters data and they were successfully extracted
    MVX2_API bool GetColorCameraParams(Frame * frame, MVCommon::CameraParams & cameraParams, MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());

    /// \brief Gets IR camera parameters of a frame.
    /// \param frame        a frame
    /// \param cameraParams a target to store the camera parameters in
    /// \param purposeGuid  a purpose guid of data to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns            true if the frame contains IR camera parameters data and they were successfully extracted
    MVX2_API bool GetIRCameraParams(Frame * frame, MVCommon::CameraParams & cameraParams, MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());
    
    /// \brief Gets transformation matrix of a frame.
    /// \param frame        a frame
    /// \param transform    a target to store the transformation matrix in
    /// \param purposeGuid  a purpose guid of data to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns            true if the frame contains transformation data and it was successfully extracted
    MVX2_API bool GetTransform(Frame * frame, MVCommon::Matrix4x4f & transform, MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());

    /// \brief Gets an ID of a segment a frame belongs to.
    /// \param frame        a frame
    /// \param segmentID    a target to store the segment ID in
    /// \param purposeGuid  a purpose guid of data to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns            true if the frame contains segment information data and it was successfully extracted
    MVX2_API bool GetSegmentID(Frame * frame, uint16_t & segmentID, MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());

    /// \brief Gets a bytearray data of a frame.
    /// \param frame        a frame
    /// \param byteArray    a target to store the bytearray data in
    /// \param purposeGuid  a purpose guid of data to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns            true if the frame contains bytearray data and it was successfully extracted
    MVX2_API bool GetByteArrayData(Frame * frame, MVCommon::ByteArray & byteArray, MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());
  };
}
/// \file
#pragma once

#include <Mvx2API/Mvx2API.h>

#include <MVCommon/guid/Guid.h>

namespace Mvx2API
{
  class Frame;

  namespace FrameAudioExtractor
  {
    /// \brief Returns a frame's audio sampling information.
    /// \param frame            a frame
    /// \param numChannels      an outputted count of audio channels
    /// \param bitsPerSample    an outputted bits count per sample
    /// \param numSamplesPerSec an outputted count of samples per second
    /// \param purposeGuid      a purpose guid of audio data to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns                true if the audio sampling information were successfully retrieved
    MVX2_API bool GetAudioSamplingInfo(Frame * frame, uint32_t& numChannels, uint32_t& bitsPerSample, uint32_t& numSamplesPerSec, 
      MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());
    /// \brief Returns a frame's audio pulse-code modulation (PCM) data offset.
    /// \param frame        a frame
    /// \param purposeGuid  a purpose guid of audio data to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns            PCM data offset
    MVX2_API uint32_t GetPCMDataOffset(Frame * frame, MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());
    /// \brief Returns a frame's audio pulse-code modulation (PCM) data size (in bytes).
    /// \param frame        a frame
    /// \param purposeGuid  a purpose guid of audio data to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns            PCM data size
    MVX2_API uint32_t GetPCMDataSize(Frame * frame, MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());
    /// \brief A getter of the raw pointer to audio pulse-code modulation (PCM) data.
    /// \param frame        a frame
    /// \param purposeGuid  a purpose guid of audio data to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns            PCM data
    MVX2_API uint8_t const * GetPCMData(Frame * frame, MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());
    /// \brief Copies a frame's audio pulse-code modulation (PCM) data.
    /// \param frame        a frame
    /// \param targetData   a target PCM data array (must be pre-allocated with (PCM data size) elements)
    /// \param purposeGuid  a purpose guid of audio data to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns            true if the PCM data were successfully copied
    MVX2_API bool CopyPCMData(Frame * frame, uint8_t * targetData, MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());
  };
}


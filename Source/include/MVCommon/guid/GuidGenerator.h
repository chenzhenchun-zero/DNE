/// \file
#pragma once

#include "Guid.h"

namespace MVCommon
{
  namespace GuidGenerator
  {
    /// \brief Generates a Guid based on another Guid (a namespace) and a string seed.
    /// \details Using the same Guid namespace and the same seed will always produce the same generated Guid.
    /// \param guidNamespace  a Guid in the role of a namespace (ancestor) for the new Guid
    /// \param seed           a seed for the new Guid generation
    /// \returns              generated Guid
    MVCOMMON_API Guid GenerateGuid(Guid const & guidNamespace, String const & seed);
    /// \brief Generates a Guid based on a string seed.
    /// \details Using the same seed will always produce the same generated Guid.
    /// \param seed a seed for the new Guid generation
    /// \returns    generated Guid
    MVCOMMON_API Guid GenerateGuid(String const & seed);
  };
}


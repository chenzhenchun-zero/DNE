/// \file
#pragma once

/// \brief A macro for converting a value into a string literal.
/// \details Example:
/// \code
/// char const * string_literal = MV_VALUE_TO_STR_LITERAL(5);
/// // preceding line is processed into:
/// // char const * string_literal = "5";
/// \endcode
#define MV_VALUE_TO_STR(x) #x
/// \brief A macro for converting a pre-processor constant into a string literal.
/// \details Example:
/// \code
/// #define A_CONSTANT 5
/// char const * string_literal = MV_CONSTANT_TO_STR_LITERAL(A_CONSTANT);
/// // preceding line is processed into:
/// // char const * string_literal = "5";
/// \endcode
#define MV_CONSTANT_TO_STR(x) MV_VALUE_TO_STR(x)
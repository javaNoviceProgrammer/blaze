//=================================================================================================
/*!
//  \file blaze/math/Functions.h
//  \brief Header file for mathematical functions
//
//  Copyright (C) 2012-2018 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_MATH_FUNCTIONS_H_
#define _BLAZE_MATH_FUNCTIONS_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <blaze/system/Inline.h>
#include <blaze/util/constraints/Integral.h>
#include <blaze/util/Types.h>
#include <blaze/util/typetraits/CommonType.h>
#include <blaze/util/typetraits/IsBuiltin.h>


namespace blaze {

//=================================================================================================
//
//  MATHEMATICAL UTILITY FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\name Mathematical utility functions */
//@{
template< typename T >
inline size_t digits( T a ) noexcept;

template< typename T1, typename T2 >
BLAZE_ALWAYS_INLINE constexpr auto nextMultiple( T1 value, T2 factor ) noexcept;

template< typename T1, typename T2 >
BLAZE_ALWAYS_INLINE constexpr bool greater( const T1& a, const T2& b )
   noexcept( IsBuiltin_v< CommonType_t<T1,T2> > );
//@}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Returns the number of valid digits of an integral value.
// \ingroup math
//
// \param a The integral value.
// \return The number of valid digits.
//
// This function counts the number of valid digits in the given integral value.

   \code
   digits( 100   );  // Returns 3
   digits( 12345 );  // Returns 5
   digits( 0     );  // Returns 0
   \endcode

// The digits function only works for integral built-in data types. The attempt to use any
// other type will result in a compile time error.
*/
template< typename T >
inline size_t digits( T a ) noexcept
{
   BLAZE_CONSTRAINT_MUST_BE_INTEGRAL_TYPE( T );

   size_t count( 0 );

   while( a != 0 ) {
      a /= 10;
      ++count;
   }

   return count;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Rounds up an integral value to the next multiple of a given factor.
// \ingroup math
//
// \param value The integral value to be rounded up \f$[1..\infty)\f$.
// \param factor The factor of the multiple \f$[1..\infty)\f$.
// \return The multiple of the given factor.
//
// This function rounds up the given integral value to the next multiple of the given integral
// factor. In case the integral value is already a multiple of the given factor, the value itself
// is returned. Note that the attempt to use the function with non-integral types results in a
// compilation error!
*/
template< typename T1, typename T2 >
BLAZE_ALWAYS_INLINE constexpr auto nextMultiple( T1 value, T2 factor ) noexcept
{
   return ( value + ( factor - ( value % factor ) ) % factor );
}
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Default greater-than comparison for any data type.
// \ingroup math
//
// \param a First value.
// \param b Second value.
// \return \a true if the first value is greater than the second, \a false if not.
//
// Default implementation of a greater-than comparison of two data values.
*/
template< typename T >
BLAZE_ALWAYS_INLINE constexpr bool greater_backend( const T& a, const T& b )
   noexcept( IsBuiltin_v<T> )
{
   return a > b;
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Greater-than comparison for single precision floating point values.
// \ingroup math
//
// \param a First value.
// \param b Second value.
// \return \a true if the first value is greater than the second, \a false if not.
//
// Greater-than function for the comparison of two single precision floating point numbers. Due
// to the limited machine accuracy, a direct comparison of two floating point numbers should
// be avoided. This functions offers the possibility to compare two floating-point values with
// a certain accuracy margin.
*/
BLAZE_ALWAYS_INLINE constexpr bool greater_backend( float a, float b ) noexcept
{
   return ( b - a ) > 1E-8F;
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Greater-than comparison for double precision floating point values.
// \ingroup math
//
// \param a First value.
// \param b Second value.
// \return \a true if the first value is greater than the second, \a false if not.
//
// Greater-than function for the comparison of two double precision floating point numbers. Due
// to the limited machine accuracy, a direct comparison of two floating point numbers should
// be avoided. This functions offers the possibility to compare two floating-point values with
// a certain accuracy margin.
*/
BLAZE_ALWAYS_INLINE constexpr bool greater_backend( double a, double b ) noexcept
{
   return ( b - a ) > 1E-8;
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Greater-than comparison for long double precision floating point values.
// \ingroup math
//
// \param a First value.
// \param b Second value.
// \return \a true if the first value is greater than the second, \a false if not.
//
// Greater-than function for the comparison of two long double precision floating point numbers.
// Due to the limited machine accuracy, a direct comparison of two floating point numbers should
// be avoided. This functions offers the possibility to compare two floating-point values with a
// certain accuracy margin.
*/
BLAZE_ALWAYS_INLINE constexpr bool greater_backend( long double a, long double b ) noexcept
{
   return ( b - a ) > 1E-10;
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Generic greater-than comparison.
// \ingroup math
//
// \param a First value.
// \param b Second value.
// \return \a true if the first value is greater than the second, \a false if not.
//
// Generic greater-than comparison between to numeric values. Depending on the types of the
// two arguments, a special comparison for floating point values is selected that takes
// the limited machine accuracy into account.
*/
template< typename T1, typename T2 >
BLAZE_ALWAYS_INLINE constexpr bool greater( const T1& a, const T2& b )
   noexcept( IsBuiltin_v< CommonType_t<T1,T2> > )
{
   return greater_backend< CommonType_t<T1,T2> >( a, b );
}
//*************************************************************************************************

} // namespace blaze

#endif

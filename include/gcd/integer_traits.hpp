/*
** File Name: integer_traits.hpp
** Author:    Aditya Ramesh
** Date:      11/29/2014
** Contact:   _@adityaramesh.com
*/

#ifndef Z4F0D1545_07B3_48B0_ACAD_D1A3CB71E8E2
#define Z4F0D1545_07B3_48B0_ACAD_D1A3CB71E8E2

namespace gcd {

template <class T>
struct make_signed_impl
{ using type = T; };

template <>
struct make_signed_impl<unsigned char>
{ using type = char; };

template <>
struct make_signed_impl<unsigned short>
{ using type = short; };

template <>
struct make_signed_impl<unsigned>
{ using type = int; };

template <>
struct make_signed_impl<unsigned long>
{ using type = long; };

template <>
struct make_signed_impl<unsigned long long>
{ using type = long long; };

template <class T>
using make_signed = typename make_signed_impl<T>::type;

}

#endif

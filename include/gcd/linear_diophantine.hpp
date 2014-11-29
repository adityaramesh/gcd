/*
** File Name: linear_diophantine.hpp
** Author:    Aditya Ramesh
** Date:      11/29/2014
** Contact:   _@adityaramesh.com
**
** This header provides algorithms for solving linear Diophantine equations.
*/

#ifndef ZCA41570E_09BC_41C4_A25F_4F2CE786BA73
#define ZCA41570E_09BC_41C4_A25F_4F2CE786BA73

#include <boost/optional.hpp>
#include <gcd/extended_gcd.hpp>
#include <gcd/solution_family.hpp>

namespace gcd {

template <
	class T,
	typename std::enable_if_t<std::is_integral<T>::value, int> = 0
>
auto solve_lde(const T& a, const T& b, const T& c) noexcept ->
boost::optional<solution_family<make_signed<T>>>
{
	using std::get;
	using signed_int = make_signed<T>;

	auto r = extended_gcd(a, b);
	if (c % get<2>(r) != 0) {
		return boost::none;
	}

	auto e = c / get<2>(r);
	return solution_family<signed_int>{
		signed_int(e) * get<0>(r),
		signed_int(e) * get<1>(r),
		signed_int(b / get<2>(r)),
		-signed_int(a / get<2>(r))
	};
}

}

#endif

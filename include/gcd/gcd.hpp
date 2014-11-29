/*
** File Name: gcd.hpp
** Author:    Aditya Ramesh
** Date:      11/26/2014
** Contact:   _@adityaramesh.com
*/

#ifndef Z7795F501_FE86_410A_9D8B_9EA20AD3827E
#define Z7795F501_FE86_410A_9D8B_9EA20AD3827E

#include <numeric>
#include <type_traits>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/range/numeric.hpp>

namespace gcd {
namespace detail {

auto ctz(unsigned x) noexcept { return __builtin_ctz(x); }
auto ctz(unsigned long x) noexcept { return __builtin_ctzl(x); }
auto ctz(unsigned long long x) noexcept { return __builtin_ctzll(x); }
auto ctz(unsigned char x) noexcept { return ctz((unsigned)x); }

auto ctz(char x) noexcept { return ctz((unsigned)x); }
auto ctz(int x) noexcept { return ctz((unsigned)x); }
auto ctz(long x) noexcept { return ctz((unsigned long)x); }
auto ctz(long long x) noexcept { return ctz((unsigned long long)x); }

/*
** See `notes/gcd.md` for details.
*/
template <class T>
auto euclid_gcd(T a, T b) noexcept ->
std::enable_if_t<std::is_integral<T>::value, T>
{
	if (b > a) {
		std::swap(a, b);
	}
	while (b != 0) {
		std::tie(a, b) = std::make_tuple(b, a % b);
	}
	return a;
}

/*
** See `notes/gcd.md` for details.
*/
template <class T>
auto binary_gcd(T a, T b) noexcept ->
std::enable_if_t<std::is_integral<T>::value, T>
{
	if (a == 0) return b;
	if (b == 0) return a;

	auto s = ctz(a | b);
	a >>= ctz(a);

	do {
		b >>= ctz(b);
		if (a > b) {
			std::swap(a, b);
		}
		b = b - a;
	}
	while (b != 0);
	return a << s;
}

}

template <
	class T, class... Ts,
	typename std::enable_if_t<
		std::is_integral<T>::value && sizeof...(Ts) >= 1, int
	> = 0
>
auto gcd(const T& t, const Ts&... ts) noexcept
{
	return boost::fusion::accumulate(
		std::forward_as_tuple(ts...), t,
		[] (const auto& x, const auto& y) {
			return detail::binary_gcd(x, y);
		}
	);
}

/*
** Note: the LCM is computed by taking the product of the integers and dividing
** by their GCD. If the product overflows, the answer will be incorrect.
*/
template <
	class T, class... Ts,
	std::enable_if_t<
		std::is_integral<T>::value && sizeof...(Ts) >= 1, T
	> = 0
>
auto lcm(const T& t, const Ts&... ts) noexcept
{
	auto prod = boost::fusion::accumulate(
		std::forward_as_tuple(ts...), t,
		[] (const auto& x, const auto& y) {
			return x * y;
		}
	);
	return prod / gcd(t, ts...);
}


/*
** Requirements:
** - `Range` is a single-pass range.
*/
template <class Range>
auto gcd(const Range& r) noexcept
{
	assert(size(r) > 1);

	return std::accumulate(r.begin() + 1, r.end(), *r.begin(),
		[] (const auto& x, const auto& y) {
			return detail::binary_gcd(x, y);
		}
	);
}

/*
** Note: the LCM is computed by taking the product of the integers and dividing
** by their GCD. If the product overflows, the answer will be incorrect.
**
** Requirements:
** - `Range` is a single-pass range.
*/
template <class Range>
auto lcm(const Range& r) noexcept
{
	assert(size(r) > 1);

	auto prod = boost::accumulate(r,
		[] (const auto& x, const auto& y) {
			return x * y;
		}
	);
	return prod / gcd(r);
}

}

#endif

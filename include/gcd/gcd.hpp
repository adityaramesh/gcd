/*
** File Name: gcd.hpp
** Author:    Aditya Ramesh
** Date:      11/26/2014
** Contact:   _@adityaramesh.com
*/

#ifndef Z7795F501_FE86_410A_9D8B_9EA20AD3827E
#define Z7795F501_FE86_410A_9D8B_9EA20AD3827E

#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/algorithm.hpp>

namespace gcd {
namespace detail {

auto ctz(unsigned char x) noexcept { return ctz((unsigned)x); }
auto ctz(unsigned x) noexcept { return __builtin_ctz(x); }
auto ctz(unsigned long x) noexcept { return __builtin_ctzl(x); }
auto ctz(unsigned long long x) noexcept { return __builtin_ctzll(x); }

auto ctz(char x) noexcept { return ctz((unsigned)x); }
auto ctz(int x) noexcept { return ctz((unsigned)x); }
auto ctz(long x) noexcept { return ctz((unsigned long)x); }
auto ctz(long long x) noexcept { return ctz((unsigned long long)x); }

template <class T>
T euclid_gcd(T a, T b) noexcept
{
	if (b > a) {
		std::swap(a, b);
	}
	while (b != 0) {
		std::tie(a, b) = std::make_tuple(b, a % b);
	}
	return a;
}

template <class T>
T binary_gcd(T a, T b) noexcept
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

template <class T, class... Ts>
auto gcd(const T& t, const Ts&... ts) noexcept
{
	return boost::fusion::accumulate(
		std::forward_as_tuple(ts...), t,
		[] (const auto& x, const auto& y) {
			return detail::binary_gcd(x, y);
		}
	);
}

template <class T, class... Ts>
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

}

#endif

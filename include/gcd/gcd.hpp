/*
** File Name: gcd.hpp
** Author:    Aditya Ramesh
** Date:      11/26/2014
** Contact:   _@adityaramesh.com
*/

#ifndef Z7795F501_FE86_410A_9D8B_9EA20AD3827E
#define Z7795F501_FE86_410A_9D8B_9EA20AD3827E

#include <type_traits>

namespace gcd {
namespace detail {

auto ctz(unsigned x) noexcept { return __builtin_ctz(x); }
auto ctz(unsigned long x) noexcept { return __builtin_ctzl(x); }
auto ctz(unsigned long long x) noexcept { return __builtin_ctzll(x); }

/*
** This is Stein's algorithm (aka binary GCD), based on the version given in
** Knuth. Experiments show that Stein's algorithm only beats Euclid's algorithm
** if the native `ctz` instruction is used in both places given below.
*/
template <class T>
T gcd(T a, T b) noexcept
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

template <class... Ts>
struct gcd_helper;

template <class T>
T gcd(T a, T b) noexcept
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

namespace detail
{

template <class... Ts>
struct gcd_helper;

template <class T, class U, class... Ts>
struct gcd_helper<T, U, Ts...>
{
	static auto
	apply(const T& t, const U& u, const Ts&... ts) noexcept
	{
		return gcd_helper<Ts...>::apply(gcd(t, u), ts...);
	}
};

template <class T, class U>
struct gcd_helper<T, U>
{
	static auto
	apply(const T& t, const U& u) noexcept
	{
		return gcd(t, u);
	}
};

}

template <class... Ts>
auto gcd(const Ts&... ts) noexcept
{
	return gcd_helper<Ts...>::apply(ts...);
}

}

template <class... Ts>
auto gcd(const Ts&... ts) noexcept
{
	return detail::gcd_helper<Ts...>::apply(ts...);
}

//static inline void
//y3(int u, int v)
//{
//	if (u == 0) {
//		cc::println("Done: {0}.\n", u);
//		return;
//	}
//	if (v == 0) {
//		cc::println("Done: {0}.\n", v);
//		return;
//	}
//
//	int k = ctz(u | v);
//	u >>= k;
//	v >>= k;
//
//	// `u` and `v` are both odd.
//	
//	int u1 = 1, u2 = 0, u3 = u;
//	int v1 = 0, v2 = 1, v3 = v;
//	int c = 0;
//
//	do {
//		do {
//			// Check whether using `ctz` instead of right shifts by
//			// one actually helps.
//			std::tie(v1, v2, v3) = std::make_tuple(v1 + v, v2 - u, v3);
//			int z = ctz(v1 | v2 | v3);
//			std::tie(v1, v2, v3) = std::make_tuple(v1 >> z, v2 >> z, v3 >> z);
//		}
//		while ((v3 & 1) == 0);
//
//		// `v3` is now odd.
//
//		/*
//		while ((v3 & 1) == 0) {
//			unsigned z = ctz(v1 | v2);
//			if (z > 0) {
//				v1 /= 2;
//				v2 /= 2;
//				v3 /= 2;
//			}
//			else {
//				v1 = (v1 + v) / 2;
//				v2 = (v2 - u) / 2;
//				v3 = v3 / 2;
//			}
//		}
//		*/
//
//		auto t = std::make_tuple(v1, v2, v3);
//		std::tie(v1, v2, v3) = std::make_tuple(u1 - v1, u2 - v2, u3 - v3);
//		std::tie(u1, u2, u3) = t;
//
//		// We need this check in order to guarantee that `v3` gets
//		// smaller as we continue to iterate. If `v3` becomes negative
//		// as a result of the subtraction, then the `v3` will get larger
//		// after the subtraction and may not converge.
//		if (v3 < 0) {
//			std::tie(v1, v2, v3) = std::make_tuple(-v1, -v2, -v3);
//		}
//
//		++c;
//		//cc::println("(u1, u2, u3) = ({0}, {1}, {2})", u1, u2, u3);
//		cc::println("E (v1, v2, v3) = ({0}, {1}, {2})", v1, v2, v3);
//	}
//	while (v3 != 0);
//
//	cc::println("Done: ({0}, {1}, {2}).", u1, u2, u3 << k);
//	cc::println("Iterations: {0}.\n", c);
//}

}

#endif

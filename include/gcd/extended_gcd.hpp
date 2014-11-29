/*
** File Name: extended_gcd.hpp
** Author:    Aditya Ramesh
** Date:      11/29/2014
** Contact:   _@adityaramesh.com
*/

#ifndef ZEAC9DEF5_628E_42B9_91D4_6A6C73246875
#define ZEAC9DEF5_628E_42B9_91D4_6A6C73246875

#include <array>
#include <tuple>
#include <type_traits>
#include <boost/range.hpp>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/copy.hpp>

namespace gcd {
namespace detail {

/*
** See `notes/extended_gcd.md` for details.
*/
template <class T>
auto extended_euclid_gcd(const T& a, const T& b) noexcept ->
std::tuple<T, T, T>
{
	using std::get;
	using std::tie;
	using std::make_tuple;

	if (b > a) {
		auto r = extended_euclid_gcd(b, a);
		return make_tuple(get<1>(r), get<0>(r), get<2>(r));
	}
	if (b == 0) {
		return make_tuple(a, 1, 0);
	}

	auto p = a;
	auto q = b;
	auto u1 = T{1};
	auto u2 = T{0};

	for (;;) {
		tie(p, q) = make_tuple(q, p % q);
		if (q == 0) {
			break;
		}
		tie(u1, u2) = make_tuple(u2 - (p / q) * u1, u1);
	}
	return make_tuple(u2, (p - u2 * a) / b, p);
}

/*
** TODO: Understand and implement extended binary GCD.
*/

}

/*
** Given a vector of integers $(x_1, \ldots, x_n)$, computes a vector of
** multipliers $(a_1, \ldots, a_n)$ such that
** \[
** 	a_1 x_1 + \cdots + a_n x_n = \gcd(x_1, \ldots, x_n).
** \]
**
** Requirements:
** - `InputRange` must be a single-pass range.
** - `OutputIterator` must be a random access output iterator.
*/
template <class InputRange, class OutputIterator>
auto extended_gcd(const InputRange& input_range, OutputIterator coeffs)
noexcept
{
	using std::tie;
	using detail::extended_euclid_gcd;
	using integer = typename boost::range_value<InputRange>::type;
	assert(input_range.size() > 1);

	auto u = integer{0};
	auto cur_gcd = integer{0};
	auto inputs = input_range.begin();
	tie(coeffs[0], coeffs[1], cur_gcd) = extended_euclid_gcd(inputs[0], inputs[1]);

	for (auto i = size_t{2}; i != input_range.size(); ++i) {
		std::tie(u, coeffs[i], cur_gcd) = extended_euclid_gcd(cur_gcd, inputs[i]);
		for (auto j = size_t{0}; j != i; ++j) {
			coeffs[j] *= u;
		}
	}
	return cur_gcd;
}

template <class T, class... Ts>
auto extended_gcd(const T& t, const Ts&... ts) noexcept
{
	using std::get;
	auto src = std::array<T, sizeof...(Ts) + 1>{t, ts...};
	auto dst = std::tuple<T, Ts..., T>{};

	/*
	** Yes, this is a nasty hack, undefined behavior, etc. If you have a
	** clean alternative that does not involve redundant copying, then
	** please suggest it.
	*/
	get<sizeof...(Ts) + 1>(dst) = extended_gcd(src, (T*)&get<0>(dst));
	return dst;
}

}

#endif

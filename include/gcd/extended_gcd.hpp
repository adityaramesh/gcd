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
#include <gcd/integer_traits.hpp>

namespace gcd {
namespace detail {

/*
** See `notes/extended_gcd.md` for details.
**
** A note on signedness: the paper `references/multiplier_upper_bound.pdf` shows
** that there is an optimal time and optimal space extended GCD algorithm which,
** when applied to integers $a_1, \ldots, a_n$, yields multipliers whose sizes
** are bounded above by $\max(a_1, \ldots, a_n) / 2$. Since the extended
** Euclidean algorithm yields a minimal pair of Bezout ceofficients, it is safe
** for us to store the signed coefficients in a data type with the same size as
** `T`.
*/
template <class T>
auto extended_euclid_gcd(const T& a, const T& b) noexcept ->
std::tuple<make_signed<T>, make_signed<T>, T>
{
	using std::get;
	using std::tie;
	using std::make_tuple;
	using signed_int = make_signed<T>;

	if (b > a) {
		auto r = extended_euclid_gcd(b, a);
		return make_tuple(get<1>(r), get<0>(r), get<2>(r));
	}
	if (b == 0) {
		return make_tuple(a, 1, 0);
	}

	auto p = a;
	auto q = b;
	auto u1 = signed_int{1};
	auto u2 = signed_int{0};

	for (;;) {
		tie(p, q) = make_tuple(q, p % q);
		if (q == 0) {
			break;
		}
		tie(u1, u2) = make_tuple(u2 - p / q * u1, u1);
	}

	/*
	** We have to be very careful here in order to preserve signedness. Edit
	** with caution!
	*/
	return make_tuple(u2, (signed_int(p) - signed_int(u2 * a)) / signed_int(b), p);
}

/*
** TODO: Understand and implement extended binary GCD.
*/

}

template <class T>
auto extended_gcd(const T& a, const T& b) noexcept
{
	return detail::extended_euclid_gcd(a, b);
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
** - The value type of `OutputIterator` must be at least the same size as that
** of `InputRange`. In addition, if the value type of `InputRange` is unsigned,
** the value type of `OutputIterator` must be signed. These conditions are in
** fact sufficient to ensure that the coefficients produced by the extended
** Euclidean algorithm can be written to `coeffs`.
*/
template <class InputRange, class OutputIterator>
auto extended_gcd(const InputRange& input_range, OutputIterator coeffs)
noexcept
{
	using std::tie;
	using integer = typename boost::range_value<InputRange>::type;
	using output_type = typename std::iterator_traits<OutputIterator>::value_type;

	static_assert(sizeof(output_type) >= sizeof(integer), "");
	static_assert(!(std::is_unsigned<integer>::value &&
		std::is_unsigned<output_type>::value), "");
	assert(input_range.size() > 1);

	auto u = integer{0};
	auto cur_gcd = integer{0};
	auto inputs = input_range.begin();
	tie(coeffs[0], coeffs[1], cur_gcd) = extended_gcd(inputs[0], inputs[1]);

	for (auto i = size_t{2}; i != input_range.size(); ++i) {
		std::tie(u, coeffs[i], cur_gcd) = extended_gcd(cur_gcd, inputs[i]);
		for (auto j = size_t{0}; j != i; ++j) {
			coeffs[j] *= u;
		}
	}
	return cur_gcd;
}

template <
	class T, class... Ts,
	typename std::enable_if_t<
		std::is_integral<T>::value && (sizeof...(Ts) > 1), int
	> = 0
>
auto extended_gcd(const T& t, const Ts&... ts) noexcept
{
	using std::get;
	using signed_int = make_signed<T>;
	auto src = std::array<T, sizeof...(Ts) + 1>{t, ts...};
	auto dst = std::tuple<make_signed<T>, make_signed<Ts>..., T>{};

	/*
	** Yes, this is a nasty hack, undefined behavior, etc. If you have a
	** clean alternative that does not involve redundant copying, then
	** please tell me.
	*/
	get<sizeof...(Ts) + 1>(dst) = extended_gcd(src, (signed_int*)&get<0>(dst));
	return dst;
}

}

#endif

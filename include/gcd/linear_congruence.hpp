/*
** File Name: linear_congruence.hpp
** Author:    Aditya Ramesh
** Date:      11/29/2014
** Contact:   _@adityaramesh.com
*/

#ifndef ZEA6D0C63_0D72_4F81_B2B0_95841C91296F
#define ZEA6D0C63_0D72_4F81_B2B0_95841C91296F

#include <boost/range.hpp>
#include <boost/optional.hpp>
#include <gcd/gcd.hpp>
#include <gcd/extended_gcd.hpp>
#include <gcd/congruence_class.hpp>

namespace gcd {

template <
	class T,
	typename std::enable_if_t<std::is_integral<T>::value, int> = 0
>
auto solve_linear_congruence(const T& a, const T& b, const T& mod)
noexcept -> boost::optional<congruence_class<make_signed<T>>>
{
	using std::get;
	using signed_int = make_signed<T>;
	static const auto _ = std::ignore;
	assert(mod > 0);

	auto r = signed_int{};
	auto gcd = T{};
	std::tie(r, _, gcd) = extended_gcd(a, mod);

	if (b % gcd != 0) return boost::none;
	auto e = signed_int(b / gcd);
	return congruence_class<signed_int>{e * r, mod};
}

template <class IR1, class IR2, class IR3>
auto solve_linear_congruences(
	const IR1& a_range,
	const IR2& b_range,
	const IR3& mods_range
) noexcept -> boost::optional<
	congruence_class<make_signed<
		typename boost::range_value<IR1>::type
	>>
>
{
	using ir1_type = typename boost::range_value<IR1>::type;
	using ir2_type = typename boost::range_value<IR2>::type;
	using ir3_type = typename boost::range_value<IR3>::type;

	static_assert(std::is_same<ir1_type, ir2_type>::value, "");
	static_assert(std::is_same<ir2_type, ir3_type>::value, "");
	assert(a_range.size() > 0);
	assert(a_range.size() == b_range.size());
	assert(b_range.size() == mods_range.size());

	using integer = ir1_type;
	using signed_int = make_signed<ir1_type>;
	static const auto _ = std::ignore;
	auto a = a_range.begin();
	auto b = b_range.begin();
	auto mods = mods_range.begin();

	auto c = solve_linear_congruence(a[0], b[0], mods[0]);
	if (!c) return boost::none;
	auto m = mods[0];
	auto x = c->representative();

	for (auto i = size_t{1}; i != a_range.size(); ++i) {
		c = solve_linear_congruence(a[i] * m, b[i] - a[i] * x, mods[i]);
		if (!c) return boost::none;
		x += c->representative() * m;
		m = lcm(m, mods[i]);
	}
	return congruence_class<signed_int>{x, m};
}

template <class T>
auto solve_linear_congruences(
	const std::initializer_list<T>& a,
	const std::initializer_list<T>& b,
	const std::initializer_list<T>& mods
) noexcept
{
	return solve_linear_congruences(
		boost::make_iterator_range(a.begin(), a.end()),
		boost::make_iterator_range(b.begin(), b.end()),
		boost::make_iterator_range(mods.begin(), mods.end())
	);
}

}

#endif

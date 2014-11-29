/*
** File Name: solution_family.hpp
** Author:    Aditya Ramesh
** Date:      11/29/2014
** Contact:   _@adityaramesh.com
*/

#ifndef ZDD6B0086_ACD6_4842_BF6D_E79381C8767B
#define ZDD6B0086_ACD6_4842_BF6D_E79381C8767B

namespace gcd {

template <class T>
class solution_family
{
	T m_x0;
	T m_y0;
	T m_u;
	T m_v;
public:
	explicit solution_family(
		const T& x0, const T& y0,
		const T& u, const T& v
	) noexcept : m_x0{x0}, m_y0{y0}, m_u{u}, m_v{v} {}

	auto operator()(const T& n)
	const noexcept
	{
		return std::make_tuple(
			m_x0 + n * m_u,
			m_y0 + n * m_v
		);
	}

	auto instance() const noexcept
	{
		return std::make_tuple(m_x0, m_y0);
	}

	auto parameters() const noexcept
	{
		return std::make_tuple(m_u, m_v);
	}
};

template <class Char, class Traits, class T>
std::basic_ostream<Char, Traits>&
operator<<(std::basic_ostream<Char, Traits>& os, const solution_family<T>& s)
noexcept
{
	using std::abs;
	using std::get;
	auto init = s.instance();
	auto params = s.parameters();

	os << "(x(n), y(n)) = ";
	if (get<0>(params) > 0) {
		os << "(" << get<0>(init) << " + " << get<0>(params) << " * n, ";
	}
	else {
		os << "(" << get<0>(init) << " - " << -get<0>(params) << " * n, ";
	}

	if (get<1>(params) > 0) {
		os << get<1>(init) << " + " << get<1>(params) << " * n)";
	}
	else {
		os << get<1>(init) << " - " << -get<1>(params) << " * n)";
	}
	return os;
}

}

#endif

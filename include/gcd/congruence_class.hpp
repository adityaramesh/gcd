/*
** File Name: congruence_class.hpp
** Author:    Aditya Ramesh
** Date:      11/29/2014
** Contact:   _@adityaramesh.com
*/

#ifndef ZAB135C67_C490_4769_91D7_B3C5522CDBFA
#define ZAB135C67_C490_4769_91D7_B3C5522CDBFA

namespace gcd {

template <class T>
class congruence_class
{
	T m_rep;
	T m_mod;
public:
	explicit congruence_class(const T& rep, const T& mod)
	noexcept : m_rep{rep}, m_mod{mod} {}

	auto representative() const noexcept
	{
		return m_rep;
	}

	auto modulus() const noexcept
	{
		return m_mod;
	}
};

template <class T>
auto canonical_representative(const congruence_class<T>& c)
noexcept
{
	const auto r = c.representative();
	if (r >= 0) {
		return r % c.modulus();
	}
	else {
		return c.modulus() - (-r) % c.modulus();
	}
}

template <class Char, class Traits, class T>
std::basic_ostream<Char, Traits>&
operator<<(std::basic_ostream<Char, Traits>& os, const congruence_class<T>& c)
noexcept
{
	return os << canonical_representative(c) << " (mod " << c.modulus()
		<< ")";
}

}

#endif

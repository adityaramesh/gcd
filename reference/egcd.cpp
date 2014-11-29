/*
** File Name:	egcd.cpp
** Author:	Aditya Ramesh
** Date:	08/21/2013
** Contact:	_@adityaramesh.com
*/

#include <cmath>
#include <cstdlib>
#include <tuple>
#include <ccbase/tuple.hpp>
#include <ccbase/format.hpp>
#include <ccbase/platform.hpp>

static CC_ALWAYS_INLINE int
ctz(unsigned x)
{
	return __builtin_ctz(x);
}

/*
** Extended Euclid's Algorithm. See notes for explanation.
*/

static CC_ALWAYS_INLINE std::tuple<int, int, int>
egcd_1(const int a, const int b)
{
	using std::make_tuple;
	using std::tie;

	if (b > a) {
		return egcd_1(b, a);
	}
	if (b == 0) {
		return make_tuple(a, 1, 0);
	}

	auto p = a;
	auto q = b;
	auto u = 1;
	auto v = 0;

	for (;;) {
		tie(p, q) = make_tuple(q, p % q);
		if (q == 0) {
			break;
		}
		tie(u, v) = make_tuple(v - (p / q) * u, u);
	}
	return make_tuple(v, (p - v * a) / b, p);
}

/*
** Extended Stein's Algorithm. TODO: adapt from reference implementation.
*/

//static CC_ALWAYS_INLINE std::tuple<int, int, int>
//egcd_2(const int a, const int b)
//{
//	
//}

int main(int, char**)
{

}

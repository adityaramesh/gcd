/*
** File Name:	gcd.cpp
** Author:	Aditya Ramesh
** Date:	08/21/2013
** Contact:	_@adityaramesh.com
*/

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <random>
#include <tuple>
#include <ccbase/format.hpp>
#include <ccbase/platform.hpp>

static CC_ALWAYS_INLINE int
ctz(unsigned x)
{
	return __builtin_ctz(x);
}

/*
** Euclid's Algorithm.
*/

static CC_ALWAYS_INLINE unsigned
gcd_1(unsigned a, unsigned b)
{
	if (b > a) {
		std::swap(a, b);
	}
	if (b == 0) {
		return a;
	}
	b = a % b;

	while (b != 0) {
		std::tie(a, b) = std::make_tuple(b, a % b);
	}
	return a;
}

/*
** Stein's Algorithm (naive implementation).
*/

static CC_ALWAYS_INLINE unsigned
gcd_2(unsigned a, unsigned b)
{
	// If `a` or `b` are zero, we will get infinite loops.
	if (a == 0) {
		return b;
	}
	if (b == 0) {
		return a;
	}

	// Shift out any common power-of-two factors. This works because if
	// $c|a$ and $c|b$, then $\gcd(a,b) = c \cdot gcd(a/c,b/c)$.
	auto s = unsigned{0};
	while (((a | b) & 1) == 0) {
		a >>= 1;
		b >>= 1;
		++s;
	}

	// Ensure that `a` is odd until the end of the procedure. This works
	// because if $c|a$ but $c \nmid b$, then $\gcd(a,b) = \gcd(a / c, b)$.
	while ((a & 1) == 0) {
		a >>= 1;
	}

	do {
		// Ensure that `b` is odd.
		while ((b & 1) == 0) {
			b >>= 1;
		}

		if (a > b) {
			std::swap(a, b);
		}

		// We want to guarantee that `a` remains odd, so we perform the
		// subtraction on `b`. If we had performed the subtraction on
		// `a` instead, then we would again have to iterate dividing `a`
		// by two until ascertain that it is odd. This works because if
		// $a$ and $b$ are odd with $b \geq a$, then $\gcd(a,b) =
		// \gcd(a, b - a)$. Since $b - a$ is even, we have $\gcd(a, b -
		// a) = \gcd(a, (b - a)/2)$.
		b = b - a;
	}
	while (b != 0);
	return a << s;
}

/*
** Stein's Algorithm (less naive implementation).
*/

static CC_ALWAYS_INLINE unsigned
gcd_3(unsigned a, unsigned b)
{
	if (a == 0) {
		return b;
	}
	if (b == 0) {
		return a;
	}

	auto s = unsigned{ctz(a | b)};
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

int main(int argc, char** argv)
{
	
}

/*
** File Name:	gcd.cpp
** Author:	Aditya Ramesh
** Date:	08/21/2013
** Contact:	_@adityaramesh.com
**
** On my machine, running the benchmark reports the following timings.
** - `gcd_1`: 0.131 +- 0.001 seconds
** - `gcd_2`: 0.468 +- 0.001 seconds
** - `gcd_3`: 0.082 +- 0.001 seconds
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
	// If either `a` or `b` is zero, we will get an infinite loop.
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
		// by two to ascertain that it is odd. This works because if $a$
		// and $b$ are odd with $b \geq a$, then $\gcd(a,b) = \gcd(a, b
		// - a)$. Since $b - a$ is even, we have $\gcd(a, b - a) =
		// \gcd(a, (b - a)/2)$.
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

int main(int, char**)
{
	using namespace std::chrono;
	static constexpr auto n = 10000000u;
	auto t1 = high_resolution_clock::now();
	auto buf = std::unique_ptr<unsigned[]>{new unsigned[n]};
	std::random_device dev{};

	/*
	** This usefulness of this benchmark is questionable, because most pairs
	** of numbers produced by uniformly sampling will be coprime. Does this
	** reflect real-world usage?
	*/
	auto dist = std::uniform_int_distribution<unsigned>{0, 100};
	std::generate(buf.get(), buf.get() + n, [&]() { return dist(dev); });
	auto t2 = high_resolution_clock::now();
	auto t = duration_cast<duration<double>>(t2 - t1).count();
	cc::println("Time elapsed initializing input: $0 seconds.", t);

	t1 = high_resolution_clock::now();
	auto s = unsigned{0};
	for (unsigned i{0}; i != n; i += 2) {
		s += gcd_1(buf[i], buf[i + 1]);
	}
	t2 = high_resolution_clock::now();
	t = duration_cast<duration<double>>(t2 - t1).count();
	cc::println("Time elapsed for gcd_1: $0 seconds.", t);
	cc::println("Sum: $0.", s);

	t1 = high_resolution_clock::now();
	s = 0;
	for (unsigned i{0}; i != n; i += 2) {
		if (gcd_1(buf[i], buf[i + 1]) != gcd_2(buf[i], buf[i + 1])) {
			cc::println("$0 $1 $2 $3", buf[i], buf[i + 1], gcd_1(buf[i], buf[i + 1]), gcd_2(buf[i], buf[i + 1]));
		}
		s += gcd_2(buf[i], buf[i + 1]);
	}
	t2 = high_resolution_clock::now();
	t = duration_cast<duration<double>>(t2 - t1).count();
	cc::println("Time elapsed for gcd_2: $0 seconds.", t);
	cc::println("Sum: $0.", s);

	t1 = high_resolution_clock::now();
	s = 0;
	for (unsigned i{0}; i != n; i += 2) {
		s += gcd_3(buf[i], buf[i + 1]);
	}
	t2 = high_resolution_clock::now();
	t = duration_cast<duration<double>>(t2 - t1).count();
	cc::println("Time elapsed for gcd_3: $0 seconds.", t);
	cc::println("Sum: $0.", s);
}

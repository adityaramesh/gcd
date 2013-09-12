/*
** File Name:	y.cpp
** Author:	Aditya Ramesh
** Date:	07/11/2013
** Contact:	_@adityaramesh.com
*/

#include <cmath>
#include <cstdlib>
#include <tuple>
#include <ccbase/format.hpp>

static inline int
ctz(unsigned x) 
{
	return __builtin_ctz(x);
}

static inline unsigned
gcd_3(unsigned a, unsigned b)
{
	if (a == 0) {
		return b;
	}
	if (b == 0) {
		return a;
	}

	unsigned s = ctz(a | b);
	a >>= ctz(a);
	std::cout << a << " " << b << std::endl;

	do {
		if (ctz(b) > 0) {
			cc::println("{0} = {1} / {2}", b >> ctz(b), b, std::pow(2, ctz(b)));
		}
		b >>= ctz(b);
		if (a > b) {
			std::swap(a, b);
		}
		cc::println("{0} = {1} - {2}", b - a, b, a);
		b = b - a;
	}
	while (b != 0);

	cc::println("Done: {0}\n", a << s);
	return a << s;
}

/*
** XXX: Loops forever if either u or v is zero.
*/

static inline
void y1(int u, int v)
{
	int u1, u2, u3;
	int v1, v2, v3;
	int t1, t2, t3;
	int k = ctz(u | v);
	u >>= k;
	v >>= k;
	
	int c = 0;

	std::tie(u1, u2, u3) = std::make_tuple(1, 0, u);
	std::tie(v1, v2, v3) = std::make_tuple(v, 1 - u, v);
	if ((u & 1) == 0) {
		std::tie(t1, t2, t3) = std::make_tuple(1, 0, u);
	}
	else {
		std::tie(t1, t2, t3) = std::make_tuple(0, -1, -v);
	}

	//cc::println("Y2");
	//cc::println("(u1, u2, u3) = ({0}, {1}, {2})", u1, u2, u3);
	//cc::println("(v1, v2, v3) = ({0}, {1}, {2})", v1, v2, v3);
	//cc::println("(t1, t2, t3) = ({0}, {1}, {2})\n", t1, t2, t3);

	do {
		cc::println("A (t1, t2, t3) = ({0}, {1}, {2})", t1, t2, t3);
		while ((t3 & 1) == 0) {
			unsigned t = ctz(t1 | t2);
			if (t > 0) {
				t1 /= 2;
				t2 /= 2;
				t3 /= 2;
			}
			else {
				t1 = (t1 + v) / 2;
				t2 = (t2 - u) / 2;
				t3 = t3 / 2;
			}
		}
		cc::println("B (t1, t2, t3) = ({0}, {1}, {2})", t1, t2, t3);
		//cc::println("Y3--Y4");
		//cc::println("(t1, t2, t3) = ({0}, {1}, {2})\n", t1, t2, t3);

		if (t3 > 0) {
			std::tie(u1, u2, u3) = std::make_tuple(t1, t2, t3);
		}
		else {
			std::tie(v1, v2, v3) = std::make_tuple(v - t1, -u - t2, -t3);
		}
		//cc::println("Y5");
		//cc::println("(u1, u2, u3) = ({0}, {1}, {2})", u1, u2, u3);
		//cc::println("(v1, v2, v3) = ({0}, {1}, {2})\n", v1, v2, v3);

		std::tie(t1, t2, t3) = std::make_tuple(u1 - v1, u2 - v2, u3 - v3);
		if (t1 <= 0) {
			std::tie(t1, t2) = std::make_tuple(t1 + v, t2 - u);
		}

		//cc::println("Y6");
		cc::println("E (t1, t2, t3) = ({0}, {1}, {2})", t1, t2, t3);
		++c;
	}
	while (t3 != 0);

	cc::println("Done: ({0}, {1}, {2}).", u1, u2, u3 << k);
	cc::println("Iterations: {0}.\n", c);
}

void y2(int u, int v)
{
	int u1, u2, u3;
	int v1, v2, v3;
	int t1, t2, t3;
	int k = ctz(u | v);
	int c = 0;

	std::tie(u1, u2, u3) = std::make_tuple(1, 0, u);
	std::tie(v1, v2, v3) = std::make_tuple(0, 1, v);
	if ((u & 1) == 0) {
		std::tie(t1, t2, t3) = std::make_tuple(1, 0, u);
	}
	else {
		std::tie(t1, t2, t3) = std::make_tuple(0, 1, v);
	}

	cc::println("Y2");
	cc::println("(u1, u2, u3) = ({0}, {1}, {2})", u1, u2, u3);
	cc::println("(v1, v2, v3) = ({0}, {1}, {2})", v1, v2, v3);
	cc::println("(t1, t2, t3) = ({0}, {1}, {2})\n", t1, t2, t3);

	do {
		while ((t3 & 1) == 0) {
			unsigned t = ctz(t1 | t2);
			if (t > 0) {
				t1 /= 2;
				t2 /= 2;
				t3 /= 2;
			}
			else {
				t1 = (t1 + v) / 2;
				t2 = (t2 - u) / 2;
				t3 = t3 / 2;
			}
		}
		cc::println("Y3--Y4");
		cc::println("(t1, t2, t3) = ({0}, {1}, {2})\n", t1, t2, t3);

		if (t3 > 0) {
			std::tie(u1, u2, u3) = std::make_tuple(t1, t2, t3);
		}
		else {
			std::tie(v1, v2, v3) = std::make_tuple(-t1, -t2, -t3);
		}
		cc::println("Y5");
		cc::println("(u1, u2, u3) = ({0}, {1}, {2})", u1, u2, u3);
		cc::println("(v1, v2, v3) = ({0}, {1}, {2})\n", v1, v2, v3);

		std::tie(t1, t2, t3) = std::make_tuple(u1 - v1, u2 - v2, u3 - v3);
		//if (t1 <= 0) {
		//	std::tie(t1, t2) = std::make_tuple(t1 + v, t2 - u);
		//}

		cc::println("Y6");
		cc::println("(t1, t2, t3) = ({0}, {1}, {2})\n", t1, t2, t3);
		++c;
	}
	while (t3 != 0);

	cc::println("Done.");
	cc::println("(u1, u2, u3) = ({0}, {1}, {2})", u1, u2, u3);
	cc::println("Iterations: {0}.\n", c);
}

static inline void
y3(int u, int v)
{
	if (u == 0) {
		cc::println("Done: {0}.\n", u);
		return;
	}
	if (v == 0) {
		cc::println("Done: {0}.\n", v);
		return;
	}

	int k = ctz(u | v);
	u >>= k;
	v >>= k;

	// `u` and `v` are both odd.
	
	int u1 = 1, u2 = 0, u3 = u;
	int v1 = 0, v2 = 1, v3 = v;
	int c = 0;

	do {
		do {
			// Check whether using `ctz` instead of right shifts by
			// one actually helps.
			std::tie(v1, v2, v3) = std::make_tuple(v1 + v, v2 - u, v3);
			int z = ctz(v1 | v2 | v3);
			std::tie(v1, v2, v3) = std::make_tuple(v1 >> z, v2 >> z, v3 >> z);
		}
		while ((v3 & 1) == 0);

		// `v3` is now odd.

		/*
		while ((v3 & 1) == 0) {
			unsigned z = ctz(v1 | v2);
			if (z > 0) {
				v1 /= 2;
				v2 /= 2;
				v3 /= 2;
			}
			else {
				v1 = (v1 + v) / 2;
				v2 = (v2 - u) / 2;
				v3 = v3 / 2;
			}
		}
		*/

		auto t = std::make_tuple(v1, v2, v3);
		std::tie(v1, v2, v3) = std::make_tuple(u1 - v1, u2 - v2, u3 - v3);
		std::tie(u1, u2, u3) = t;

		// We need this check in order to guarantee that `v3` gets
		// smaller as we continue to iterate. If `v3` becomes negative
		// as a result of the subtraction, then the `v3` will get larger
		// after the subtraction and may not converge.
		if (v3 < 0) {
			std::tie(v1, v2, v3) = std::make_tuple(-v1, -v2, -v3);
		}

		++c;
		//cc::println("(u1, u2, u3) = ({0}, {1}, {2})", u1, u2, u3);
		cc::println("E (v1, v2, v3) = ({0}, {1}, {2})", v1, v2, v3);
	}
	while (v3 != 0);

	cc::println("Done: ({0}, {1}, {2}).", u1, u2, u3 << k);
	cc::println("Iterations: {0}.\n", c);
}

static inline void
y4(int u, int v)
{
	if (u == 0) {
		cc::println("Done: {0}.\n", u);
		return;
	}
	if (v == 0) {
		cc::println("Done: {0}.\n", v);
		return;
	}

	int k = ctz(u | v);
	u >>= k;
	v >>= k;

	// `u` and `v` are both odd.
	
	int c = 0;
	int u1, u2, u3;
	int v1, v2, v3;

	if ((u & 1) == 0) {
		u1 = v;
		u2 = 1 - u;
		u3 = v;
		v1 = 1;
		v2 = 0;
		v3 = u;
	}
	else {
		u1 = 1;
		u2 = 0;
		u3 = u;
		v1 = 0;
		v2 = -1;
		v3 = -v;
	}

	do {
		cc::println("A (v1, v2, v3) = ({0}, {1}, {2})", v1, v2, v3);
		//do {
		//	// Check whether using `ctz` instead of right shifts by
		//	// one actually helps.
		//	std::tie(v1, v2, v3) = std::make_tuple(v1 + v, v2 - u, v3);
		//	int z = ctz(v1 | v2 | v3);
		//	std::tie(v1, v2, v3) = std::make_tuple(v1 >> z, v2 >> z, v3 >> z);
		//}
		//while ((v3 & 1) == 0);

		// `v3` is now odd.

		do {
			if (((v1 | v2) & 1) == 0) {
				v1 /= 2;
				v2 /= 2;
				v3 /= 2;
			}
			else {
				v1 = (v1 + v) / 2;
				v2 = (v2 - u) / 2;
				v3 = v3 / 2;
			}
		}
		while ((v3 & 1) == 0);

		cc::println("B (v1, v2, v3) = ({0}, {1}, {2})", v1, v2, v3);

		// We need this check in order to guarantee that `v3` gets
		// smaller as we continue to iterate. If `v3` becomes negative
		// as a result of the subtraction, then the `v3` will get larger
		// after the subtraction and may not converge.
		if (v3 < 0) {
			std::tie(v1, v2, v3) = std::make_tuple(v - v1, -u - v2, -v3);
		}

		auto t = std::make_tuple(v1, v2, v3);
		std::tie(v1, v2, v3) = std::make_tuple(u1 - v1, u2 - v2, u3 - v3);
		std::tie(u1, u2, u3) = t;
		
		if (v1 <= 0) {
			std::tie(v1, v2) = std::make_tuple(v1 + v, v2 - u);
		}

		++c;
		//cc::println("(u1, u2, u3) = ({0}, {1}, {2})", u1, u2, u3);
		cc::println("E (v1, v2, v3) = ({0}, {1}, {2})", v1, v2, v3);
	}
	while (v3 != 0);

	cc::println("Done: ({0}, {1}, {2}).", u1, u2, u3 << k);
	cc::println("Iterations: {0}.\n", c);
}

int main(int argc, char** argv)
{
	gcd_3(std::atoi(argv[1]), std::atoi(argv[2]));
	y1(std::atoi(argv[1]), std::atoi(argv[2]));
	y3(std::atoi(argv[1]), std::atoi(argv[2]));
	y4(std::atoi(argv[1]), std::atoi(argv[2]));
}

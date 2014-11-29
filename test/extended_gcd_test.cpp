/*
** File Name: extended_gcd_test.cpp
** Author:    Aditya Ramesh
** Date:      11/29/2014
** Contact:   _@adityaramesh.com
*/

#include <array>
#include <ccbase/format.hpp>
#include <gcd/extended_gcd.hpp>

int main()
{
	cc::println(gcd::extended_gcd(4096u, 260u, 488u, 748u));

	auto in = std::array<int, 4>{4096u, 260u, 488u, 748u};
	auto out = std::array<int, 4>{};
	auto gcd = gcd::extended_gcd(in, out.begin());
	cc::println("$1 $2", out, gcd);
}

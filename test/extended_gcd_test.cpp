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
	auto arr = std::array<int, 3>{6, 12, 16};
	auto out = std::array<int, 3>{};
	auto gcd = gcd::extended_gcd(arr, out.begin());
	cc::println("$1 $2 $3 $4", out[0], out[1], out[2], gcd);
	cc::println(gcd::extended_gcd(6, 12, 16));
}

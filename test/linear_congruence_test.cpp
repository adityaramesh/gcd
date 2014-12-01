/*
** File Name: linear_congruence_test.cpp
** Author:    Aditya Ramesh
** Date:      11/29/2014
** Contact:   _@adityaramesh.com
*/

#include <array>
#include <ccbase/format.hpp>
#include <gcd/linear_congruence.hpp>

int main()
{
	cc::println(*gcd::solve_linear_congruence(0, 6, 3));
	cc::println(*gcd::solve_linear_congruence(3, 5, 7));
	cc::println(*gcd::solve_linear_congruences(
		{1, 1, 1}, {3, 7, 4}, {8, 12, 15}
	));
}

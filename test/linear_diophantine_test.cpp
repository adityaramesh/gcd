/*
** File Name: linear_diophantine_test.cpp
** Author:    Aditya Ramesh
** Date:      11/29/2014
** Contact:   _@adityaramesh.com
*/

#include <array>
#include <ccbase/format.hpp>
#include <gcd/linear_diophantine.hpp>

int main()
{
	cc::println(*gcd::solve_lde(2, 5, 3));
}

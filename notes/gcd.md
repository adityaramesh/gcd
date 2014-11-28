<!--
  ** File Name: gcd.md
  ** Author:    Aditya Ramesh
  ** Date:      11/28/2014
  ** Contact:   _@adityaramesh.com
-->

# Euclid's GCD Algorithm

This algorithm is based on the simple observation that, for any two integers $a$
and $b$ such that $b \geq a$, we have $\gcd(a, b) = \gcd(b, a \mod b)$. This
result is a simple consequence of the division theorem, which in our case gives
\[
	a = qb + r,
\]
where $q \in \integers{1}$ and $r \in [0, b)$. From this equation, it is clear
that any common divisor of $b$ and $r$ is a common divisor of $a$. Since $a - qb
= r$, any common divisor of $a$ and $b$ is also a divisor of $r$. It follows
that the set of common divisors of $a$ and $b$ is the same as the set of common
divisors of $b$ and $r$. Therefore
\[
	\gcd(a, b) = \gcd(b, r) = \gcd(b, b \mod a).
\]

The Euclidean algorithm works by repeatedly applying division until we get a
remainder of zero:
\begin{align}
	a &= q_1 b + r_1 \\
	b &= q_2  r_1 + r_2 \\
	&\vdots
	r_{n - 3} &= q_{n - 1} r_{n - 2} + r_{n - 1} \\
	r_{n - 2} &= q_n r_{n - 1} + r_n,
\end{align}
where $r_n = 0$. These equations correpond to the sequence of computations
\[
	\gcd(a, b) = \gcd(b, r_1) = \hdots = \gcd(r_{n - 2}, r_{n - 1}) =
	\gcd(r_{n - 1}, 0) = r_{n - 1},
\]
so the GCD is given by $r_{n - 1}$.

# Binary GCD

Binary GCD, also known as Stein's algorithm, works by dividing by powers of two,
and is more efficient than Euclid's algorithm on computers. It is based on the
following three observations, all of which are consequences of basic properties
of the GCD. Let $a, b \in \integers{1}$ such that $a \geq b$.

1. If $a$ and $b$ are both even, then $\gcd(a, b) = 2 \gcd(a / 2, b / 2)$.
2. If $a$ is even and $b$ is odd, then $\gcd(a, b) = 2 \gcd(a / 2, b)$.
3. If $a$ and $b$ are both odd, then $\gcd(a, b) = \gcd((a - b) / 2, b)$.

The implementation of binary GCD in `gcd.hpp` should now be clear.

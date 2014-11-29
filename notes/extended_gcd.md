<!--
  ** File Name:	extended_gcd.md
  ** Author:	Aditya Ramesh
  ** Date:	09/12/2013
  ** Contact:	_@adityaramesh.com
-->

# Extended Euclidean Algorithm

## Motivation

Let $a, b \in \integers{1}$. The extended Euclidean algorithm computes
multipliers $u$ and $v$ such that
\[
	au + bv = \gcd(a, b).
\]
The algorithm is based on the observation that the $i$th step of the regular
Euclidean algorithm expresses $r_i$ as an integer linear combination of $a$ and
$b$. To see why, note that the $i$th step computes $q_i$ and $r_i$ such that
\[
	r_{i - 2} = q_i r_{i - 1} + r_i,
\]
or
\[
	r_i = r_{i - 2} - q_i r_{i - 1}.
\]
Using information from previous iterations, we can express $r_{i - 2}$ and $r_{i
- 1}$ in terms of $a$ and $b$. Thus the RHS of previous equation can be
expressed as an integer linear combination of $a$ and $b$. The penultimate step
of the algorithm computes
\[
	r_{n - 3} = q_{n - 1} r_{n - 2} + r_{n - 1}.
\]
Since $r_{n - 1} = \gcd(a, b)$, we can express $\gcd(a, b)$ as an integer linear
combination of $a$ and $b$.

## Derivation

As we iterate, we compute

	a         = q_1 b   + r_1
	b         = q_2 r_1 + r_2
	...
	r_{i - 2} = q_i r_{i - 1} + r_i,
	...
	r_{n - 2} = q_n r_{n - 1} + 0,

after which the algorithm terminates. For any iteration $i
\geq 2$, we have

	r_i = r_{i - 2} - q_i r_{i - 1}.	            (1)

From the previous iteration, we have

	r_{i - 1} = u_1 * a + v_1 * b,		            (2)

and from the one before,

	r_{i - 2} = u_2 * a + v_2 * b.		            (3)

Substituting (2) and (3) into (1), we get

	r_i = (u_2 a + v_2 b) - (q_i u_1 a + q_i v_1 b).    (4)

We only need to track either $(u_1, u_2)$ or $(v_1, v_2)$, since we can compute
the other mulitiplier after the algorithm terminates by using Bezout's identity,
which gives

	u_1 a + v_1 b = gcd(a, b).

Suppose that we choose to track $(u_1, u_2)$. At each iteration, we must set
$u_1$, the multiplier associated with $a$ from the previous iteration, to the
multiplier associated with $a$ from the current iteration. Similarly, we must
update $u_2$, the multiplier associated with $a$ from two iterations ago, to the
multiplier associated with $a$ from one iteration ago.

The update for $u_1$ is given by (4); to update $u_2$, we simply set it to the
previous value of $u_1$. Thus, the update for $(u_1, u_2)$ is given by

	(u_1, u_2) <- (u_2 - q_i u_1, u_1).

## Initialization

Without loss of generality, assume that $a > b$. Then the first equation will be
of the form

	r_1 = a - q_1 b.

We can simplify computations by choosing to track $u_1$ and $u_2$, the
coefficients associated with $a$, because we will always begin with $u_2 = 1$
(since we are dividing b into a). The coefficient of $a$ in this equation is
one, so we choose $u_1 = 1$.

## Convergence

As the algorithm iterates, we trace through the recurrence equations of the form

	r_i       = r_{i - 2} - q_i r_{i - 1}
	r_{i + 1} = r_{i - 1} - q_{i + 1} r_i.

At iteration $i$, $u_1$ is the multiplier associated with $a$ from two
iterations ago, and $u_2$ is the multiplier associated with $a$ from one
iteration ago. Convergence of this algorithm follows from convergence of the
standard Euclid GCD algorithm. At the last iteration, we have $r_n = 0$ and we
terminate.

## Generalizing to Multiple Variables

Given integers $x_1, \ldots, x_n$, suppose that we wish to determine integral
coefficients $a_1, \ldots, a_n$ such that
\[
	a_1 x_1 + \ldots a_n x_n = gcd(a_1, \ldots, a_n).
\]
The easily-verified identity
\[
	\gcd(\gcd(a_1, \ldots, a_i), a_{i + 1}) = \gcd(a_1, \ldots, a_{i + 1})
\]
allows us to decompose this problem in $n$ variables into a series of problems
involving only two variables. First

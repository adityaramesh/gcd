<!--
  ** File Name:	extended_gcd.md
  ** Author:	Aditya Ramesh
  ** Date:	09/12/2013
  ** Contact:	_@adityaramesh.com
-->

# Extended Euclid's Algorithm

## Motivation

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
the other mulitiplier after the algorithm terminates by using the identity

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
(since we are dividing b into a).  In order to make the first iteration work, we
are forced to pick $u_1 = 0$.

## Convergence

As the algorithm iterates, we trace through the recurrence equations of the form

	r_i       = r_{i - 2} - q_i r_{i - 1}
	r_{i + 1} = r_{i - 1} - q_{i + 1} r_i.

At iteration $i$, $u_1$ is the multiplier associated with $a$ from two
iterations ago, and $u_2$ is the multiplier associated with $a$ from one
iteration ago. Convergence of this algorithm follows from convergence of the
standard Euclid GCD algorithm. At the last iteration, we have $r_n = 0$ and we
terminate.

/*
 * dt_int.c -- checked integers (Unit 5, Section A).
 *
 * Signed overflow in C is undefined behavior, not wraparound. That word matters
 * more than it looks: the compiler is entitled to assume it never happens, so
 * `if (a + b < a)` as an overflow test can be deleted outright by the optimizer,
 * because the only way it could be true is a path the standard says cannot
 * exist. Compute the answer first and inspect it afterward and you have already
 * lost.
 *
 * So the check has to come before the arithmetic, phrased in operands that are
 * definitely in range. For addition: if b is positive, overflow means
 * a > LLONG_MAX - b. If b is negative, underflow means a < LLONG_MIN - b.
 * Both right-hand sides are computable without overflowing.
 *
 * Multiplication has more cases, including the one that catches people:
 * LLONG_MIN / -1 is itself an overflow, so a division-based check needs that
 * pair handled separately.
 *
 * These stubs compute nothing and report overflow for everything, so the
 * normal/ cases fail until you write them.
 */

#include "dt.h"

#include <limits.h>

dt_status dt_int_add(long long a, long long b, long long *out)
{
    /* TODO: detect overflow before adding, then write the sum to *out. */
    (void)a;
    (void)b;
    (void)out;
    return DT_ERR_OVERFLOW;
}

dt_status dt_int_sub(long long a, long long b, long long *out)
{
    /* TODO: subtraction is not addition of a negation. -LLONG_MIN does not
       exist, so `dt_int_add(a, -b, out)` is wrong for b == LLONG_MIN. */
    (void)a;
    (void)b;
    (void)out;
    return DT_ERR_OVERFLOW;
}

dt_status dt_int_mul(long long a, long long b, long long *out)
{
    /* TODO: handle zero first, then the LLONG_MIN with -1 pair, then the
       general case. */
    (void)a;
    (void)b;
    (void)out;
    return DT_ERR_OVERFLOW;
}

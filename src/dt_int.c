/*
 * dt_int.c -- checked integers (Unit 5, Section A).
 *
 * In C, signed integer overflow is undefined behavior. The standard says
 * nothing about what the program does, so the compiler may assume overflow
 * never happens. A check written after the arithmetic can be deleted by the
 * optimizer for that reason:
 *
 *     long long sum = a + b;
 *     if (sum < a) return DT_ERR_OVERFLOW;   // may be removed
 *
 * So check first, using values that cannot overflow by themselves. For
 * addition, if b is positive, the sum is too large when a > LLONG_MAX - b. If
 * b is negative, the sum is too small when a < LLONG_MIN - b. Both of those
 * subtractions are safe.
 *
 * Multiplication has more cases. Watch LLONG_MIN with -1. That product
 * overflows, and so does the division LLONG_MIN / -1 that a division-based
 * check would compute.
 *
 * These stubs report overflow for every input, so the normal/ cases fail until
 * you write them.
 */

#include "dt.h"

#include <limits.h>

dt_status dt_int_add(long long a, long long b, long long *out)
{
    /* TODO: check for overflow, then write the sum to *out. */
    (void)a;
    (void)b;
    (void)out;
    return DT_ERR_OVERFLOW;
}

dt_status dt_int_sub(long long a, long long b, long long *out)
{
    /* TODO: subtraction is not addition of a negation. -LLONG_MIN does not
       exist, so dt_int_add(a, -b, out) gives the wrong answer when b is
       LLONG_MIN. */
    (void)a;
    (void)b;
    (void)out;
    return DT_ERR_OVERFLOW;
}

dt_status dt_int_mul(long long a, long long b, long long *out)
{
    /* TODO: handle zero first, then LLONG_MIN with -1, then the rest. */
    (void)a;
    (void)b;
    (void)out;
    return DT_ERR_OVERFLOW;
}

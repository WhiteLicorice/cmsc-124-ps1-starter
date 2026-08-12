/*
 * dt_array.c -- array descriptors (Unit 5, Section D).
 *
 * In C the index is also the offset, because the lower bound is always 0. That
 * hides a step. Ada, Fortran, and Pascal let you declare an array over 1..10,
 * or over -5..5, and then the index and the offset are different:
 *
 *     offset = index - lower_bound
 *
 * Once you write that subtraction, the lower bound becomes data the access
 * function reads, which is the job of a run-time descriptor.
 *
 * The bounds check has two ends. Everyone remembers the upper end. Forgetting
 * the lower end is quieter and worse. A negative index reads backwards out of
 * the allocation, into memory that is usually readable and never yours.
 */

#include "dt.h"

#include <stdlib.h>

struct dt_array {
    dt_value *elements;
    size_t    length;
    long long lower_bound;
};

dt_array *dt_array_new(size_t length, long long lower_bound)
{
    /* TODO: allocate the descriptor and `length` elements, set every element
       to dt_value_nil(), and store the bound. A length of 0 is legal and must
       not return NULL, since NULL here means the allocation failed. */
    (void)length;
    (void)lower_bound;
    return NULL;
}

void dt_array_free(dt_array *a)
{
    /* TODO: free the elements, then the descriptor. Do not free the values
       inside. The driver's environment owns those. */
    (void)a;
}

size_t dt_array_len(const dt_array *a)
{
    (void)a;
    return 0;
}

long long dt_array_lower_bound(const dt_array *a)
{
    (void)a;
    return 0;
}

dt_status dt_array_get(const dt_array *a, long long index, dt_value *out)
{
    /* TODO: reject index < lower_bound and index >= lower_bound + length, then
       read elements[index - lower_bound]. Compute the offset only after the
       check passes. */
    (void)a;
    (void)index;
    (void)out;
    return DT_ERR_RANGE;
}

dt_status dt_array_set(dt_array *a, long long index, dt_value v)
{
    /* TODO: same check, then the write. Write the check once as a helper and
       call it from both functions. Two copies will drift apart. */
    (void)a;
    (void)index;
    (void)v;
    return DT_ERR_RANGE;
}

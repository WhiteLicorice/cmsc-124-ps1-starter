/*
 * dt_array.c -- array descriptors (Unit 5, Section D).
 *
 * A C array's index is its offset, because C fixes the lower bound at 0. That
 * coincidence hides a step. Ada, Fortran, and Pascal let you declare an array
 * over 1..10, or over -5..5, and then the index is not the offset any more:
 *
 *     offset = index - lower_bound
 *
 * Write that subtraction out and the descriptor stops being decoration. The
 * lower bound is now data the access function reads, which is exactly what a
 * run-time descriptor is for.
 *
 * The bounds check has two ends. Off-by-one on the upper end is the famous
 * mistake; forgetting the lower end entirely is the one that lets a negative
 * index walk backwards out of the allocation, which is worse and quieter.
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
    /* TODO: allocate the descriptor and `length` elements, initialise every
       element to dt_value_nil(), and record the bound. A length of 0 is legal
       and must not return NULL, since NULL means allocation failure here. */
    (void)length;
    (void)lower_bound;
    return NULL;
}

void dt_array_free(dt_array *a)
{
    /* TODO: free the elements and the descriptor. Do not free the values
       inside; the driver's environment owns those. */
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
    /* TODO: reject index < lower_bound and index >= lower_bound + length,
       then read elements[index - lower_bound]. Compute the offset only after
       the check passes. */
    (void)a;
    (void)index;
    (void)out;
    return DT_ERR_RANGE;
}

dt_status dt_array_set(dt_array *a, long long index, dt_value v)
{
    /* TODO: the same check, then the write. Write the check once as a helper
       and call it from both, or the two will drift apart. */
    (void)a;
    (void)index;
    (void)v;
    return DT_ERR_RANGE;
}

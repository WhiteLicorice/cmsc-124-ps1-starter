/*
 * dt_array.c -- array descriptors (Unit 5, Section D).
 *
 * Built-in C arrays use offsets that start at 0. Ada, Fortran, and Pascal can
 * use bounds such as 1..10 or -5..5. Then the index and offset differ:
 *
 *     offset = index - lower_bound
 *
 * Once you write that subtraction, the lower bound becomes data the access
 * function reads, which is the job of a run-time descriptor. The mathematical
 * difference can exceed long long, so do not perform that signed subtraction
 * until you know its result is representable.
 *
 * The bounds check has two ends. Everyone remembers the upper end. Forgetting
 * the lower end is quieter and worse. A negative index reads backwards out of
 * the allocation. That access has undefined behavior.
 */

#include "dt.h"

#include <stdlib.h>

struct dt_array {
    dt_value *elements;
    size_t    length;
    long long lower_bound;
};

/*
 * dt_array_new: build an array of `length` elements, every one set to nil, and
 * indices starting at `lower_bound`. A length of 0 is legal and is not a
 * failure. Returns NULL when the index range or allocation size cannot be
 * represented, or when an allocation fails.
 */
dt_array *dt_array_new(size_t length, long long lower_bound)
{
    /* TODO: allocate the descriptor and `length` elements, set every element
       to dt_value_nil(), and store the bound. A length of 0 is legal and must
       not return NULL. Reject a nonempty range whose final index cannot fit in
       long long. Also reject length * sizeof(dt_value) when it exceeds SIZE_MAX.
       dt_array_new(3, 0)   -> three nil elements, indices 0, 1, 2
       dt_array_new(3, -1)  -> three nil elements, indices -1, 0, 1
       dt_array_new(0, 0)   -> a real empty array, never NULL
       cases/normal/array_basics.case, cases/boundary/array_empty.case,
       cases/boundary/array_negative_lower_bound.case */
    (void)length;
    (void)lower_bound;
    return NULL;
}

/*
 * dt_array_free: release the elements and the descriptor. Accepts NULL and does
 * nothing then. The array owns its element block. It only borrows any runtime
 * objects named by the dt_value elements.
 */
void dt_array_free(dt_array *a)
{
    /* TODO: free the elements, then the descriptor. Do not free the values
       inside. The driver's environment owns those runtime objects.
       an array holding a string  -> the element block goes, the string stays
       dt_array_free(NULL)        -> returns, having done nothing */
    (void)a;
}

/*
 * dt_array_len: how many elements the array holds. This reads a field, so it
 * takes the same time no matter how long the array is.
 */
size_t dt_array_len(const dt_array *a)
{
    /* TODO: read the field. The length does not depend on the lower bound.
       after `arr new a 3 0`:   dt_array_len(a) -> 3
       after `arr new a 3 -1`:  dt_array_len(a) -> 3, the same three elements
       after `arr new a 0 0`:   dt_array_len(a) -> 0
       cases/normal/array_basics.case, cases/boundary/array_empty.case */
    (void)a;
    return 0;
}

/*
 * dt_array_lower_bound: the index the array's indices start from. A lower
 * bound of 1 means element 0 sits at storage offset 0 but is called index 1.
 */
long long dt_array_lower_bound(const dt_array *a)
{
    /* TODO: read the field the constructor stored. This is the value dt_array_get
       subtracts, so returning 0 unconditionally makes every non-zero bound wrong.
       after `arr new a 3 -1`:  dt_array_lower_bound(a) -> -1
       after `arr new a 3 1`:   dt_array_lower_bound(a) -> 1
       cases/boundary/array_negative_lower_bound.case,
       cases/boundary/array_lower_bound_one.case */
    (void)a;
    return 0;
}

/*
 * dt_array_get: write the element at `index` to *out. Returns DT_ERR_RANGE when
 * the index is below the lower bound or past the upper end, and leaves *out
 * alone then.
 */
dt_status dt_array_get(const dt_array *a, long long index, dt_value *out)
{
    /* TODO: reject an index below the lower bound. Then compute the nonnegative
       distance without signed overflow and reject it when it is at least the
       length. Convert that checked distance to size_t for the element offset.
       an array over -1..1:
         dt_array_get(a, -1, &out)  -> DT_OK, offset 0
         dt_array_get(a,  1, &out)  -> DT_OK, offset 2
         dt_array_get(a,  2, &out)  -> DT_ERR_RANGE, *out untouched
         dt_array_get(a, -2, &out)  -> DT_ERR_RANGE, the quiet end
       cases/boundary/array_index_above_upper.case,
       cases/boundary/array_index_below_lower.case,
       cases/boundary/array_full_range_index.case */
    (void)a;
    (void)index;
    (void)out;
    return DT_ERR_RANGE;
}

/*
 * dt_array_set: replace the element at `index` with v. Returns DT_ERR_RANGE
 * when the index is outside the array, and changes nothing then. The old value
 * is not freed, for the same ownership reason as dt_array_free.
 */
dt_status dt_array_set(dt_array *a, long long index, dt_value v)
{
    /* TODO: same check, then the write. Write the check once as a helper and
       call it from both functions. Two copies will drift apart.
       an array over -1..1:
         dt_array_set(a, -1, dt_value_int(10))  -> DT_OK, offset 0 holds 10
         dt_array_set(a,  2, dt_value_int(10))  -> DT_ERR_RANGE, nothing changes
       cases/normal/array_basics.case, cases/boundary/array_negative_lower_bound.case */
    (void)a;
    (void)index;
    (void)v;
    return DT_ERR_RANGE;
}

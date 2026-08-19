/*
 * dt_tuple.c -- tuples (Unit 5, Section G).
 *
 * A tuple is a record with numbered parts. Numbering costs you meaning.
 * person.age says what it holds and person[1] does not. So tuples suit small
 * temporary groupings, such as a function returning two values.
 *
 * What you get back is that a tuple needs no declaration. You build it from
 * its parts and read it by position.
 *
 * There is no dt_tuple_set. The arity and the contents are fixed when the tuple
 * is built. That is deliberate.
 */

#include "dt.h"

#include <stdlib.h>

struct dt_tuple {
    dt_value values[DT_TUPLE_MAX_ARITY];
    size_t   arity;
};

/*
 * dt_tuple_new: build a tuple holding the first `count` values, in order. A
 * count of 0 is the empty tuple and is legal. Returns NULL when the count is
 * over DT_TUPLE_MAX_ARITY, or when an allocation fails.
 */
dt_tuple *dt_tuple_new(const dt_value *values, size_t count)
{
    /* TODO: return NULL when count is over DT_TUPLE_MAX_ARITY, and copy the
       values otherwise. A count of 0 is the empty tuple and is legal.
       {1, "two"}  -> a tuple of arity 2 that prints as (1, "two")
       count 0     -> the empty tuple, which prints as (), never NULL
       count 9     -> NULL, since DT_TUPLE_MAX_ARITY is 8
       cases/normal/tuple_basics.case, cases/capacity/tuple_max_arity.case,
       cases/capacity/tuple_over_arity.case */
    (void)values;
    (void)count;
    return NULL;
}

/*
 * dt_tuple_free: release the tuple. Accepts NULL and does nothing then. The
 * values inside belong to the environment and are not freed.
 */
void dt_tuple_free(dt_tuple *t)
{
    /* TODO: release the tuple. The values inside belong to the environment, so
       leave them alone, the same rule dt_array_free follows.
       a tuple holding a string  -> the tuple goes, the string stays
       dt_tuple_free(NULL)       -> returns, having done nothing */
    (void)t;
}

/*
 * dt_tuple_arity: how many parts the tuple has. This reads a field, so it takes
 * the same time no matter how many parts there are.
 */
size_t dt_tuple_arity(const dt_tuple *t)
{
    /* TODO: read the field the constructor stored. There is no dt_tuple_set, so
       this number never changes after construction.
       after `tup new pair 1 "two"`:  dt_tuple_arity(pair) -> 2
       after `tup new empty`:         dt_tuple_arity(empty) -> 0
       cases/normal/tuple_basics.case */
    (void)t;
    return 0;
}

/*
 * dt_tuple_at: write the part at position `index` to *out. Positions start at
 * 0. Returns DT_ERR_RANGE when the index is at or past the arity, and leaves
 * *out alone then.
 */
dt_status dt_tuple_at(const dt_tuple *t, size_t index, dt_value *out)
{
    /* TODO: DT_ERR_RANGE at or past the arity. Positions start at 0.
       for the tuple (1, "two"):
         dt_tuple_at(t, 0, &out)  -> DT_OK, *out is the integer 1
         dt_tuple_at(t, 2, &out)  -> DT_ERR_RANGE, *out untouched
       cases/normal/tuple_basics.case, cases/boundary/tuple_index_past_arity.case */
    (void)t;
    (void)index;
    (void)out;
    return DT_ERR_RANGE;
}

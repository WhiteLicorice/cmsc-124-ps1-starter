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
       values otherwise. A count of 0 is the empty tuple and is legal. */
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
    (void)t;
}

/*
 * dt_tuple_arity: how many parts the tuple has. This reads a field, so it takes
 * the same time no matter how many parts there are.
 */
size_t dt_tuple_arity(const dt_tuple *t)
{
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
    /* TODO: DT_ERR_RANGE at or past the arity. Positions start at 0. */
    (void)t;
    (void)index;
    (void)out;
    return DT_ERR_RANGE;
}

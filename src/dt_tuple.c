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

dt_tuple *dt_tuple_new(const dt_value *values, size_t count)
{
    /* TODO: return NULL when count is over DT_TUPLE_MAX_ARITY, and copy the
       values otherwise. A count of 0 is the empty tuple and is legal. */
    (void)values;
    (void)count;
    return NULL;
}

void dt_tuple_free(dt_tuple *t)
{
    (void)t;
}

size_t dt_tuple_arity(const dt_tuple *t)
{
    (void)t;
    return 0;
}

dt_status dt_tuple_at(const dt_tuple *t, size_t index, dt_value *out)
{
    /* TODO: DT_ERR_RANGE at or past the arity. Positions start at 0. */
    (void)t;
    (void)index;
    (void)out;
    return DT_ERR_RANGE;
}

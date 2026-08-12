/*
 * dt_tuple.c -- tuples (Unit 5, Section G).
 *
 * A tuple is a record whose fields are numbered instead of named. That sounds
 * like a small change and it costs exactly one thing: meaning. `person.age`
 * says what it holds and `person[1]` does not, which is why tuples suit small
 * temporary groupings, a function returning two things, and little else.
 *
 * What they buy back is that they need no declaration. You build one from its
 * parts and read it by position, so the type exists only as long as the
 * expression that made it.
 *
 * Arity is fixed at construction. There is no dt_tuple_set here, and that
 * absence is the design, not an oversight.
 */

#include "dt.h"

#include <stdlib.h>

struct dt_tuple {
    dt_value values[DT_TUPLE_MAX_ARITY];
    size_t   arity;
};

dt_tuple *dt_tuple_new(const dt_value *values, size_t count)
{
    /* TODO: NULL when count exceeds DT_TUPLE_MAX_ARITY, otherwise copy the
       values in. A count of 0 is the empty tuple and is legal. */
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

/*
 * dt_enum.c -- enumerations (Unit 5, Section C).
 *
 * C's enum is an integer with nicer spelling. Nothing stops you assigning 47 to
 * a dt_color, and nothing catches it later. Languages that take enumerations
 * seriously keep the value inside its domain and refuse the coercion.
 *
 * You cannot change what C's enum does, but you can put the domain check in the
 * one place every read goes through, which is what these three functions are.
 */

#include "dt.h"

#include <string.h>

static const char *const COLOR_NAMES[] = { "RED", "GREEN", "BLUE" };

bool dt_enum_is_valid(int ordinal)
{
    /* TODO: inside [0, DT_COLOR_COUNT). Both ends. */
    (void)ordinal;
    (void)COLOR_NAMES; /* delete this line once you use the table below */
    return false;
}

dt_status dt_enum_name(int ordinal, const char **out)
{
    /* TODO: DT_ERR_RANGE outside the domain, otherwise the name.
       Indexing COLOR_NAMES before the check is the bug this exists to teach. */
    (void)ordinal;
    (void)out;
    return DT_ERR_RANGE;
}

dt_status dt_enum_from_name(const char *name, int *out)
{
    /* TODO: linear search over COLOR_NAMES; DT_ERR_RANGE when nothing matches.
       A name is not an integer, so there is no numeric fallback here. */
    (void)name;
    (void)out;
    return DT_ERR_RANGE;
}

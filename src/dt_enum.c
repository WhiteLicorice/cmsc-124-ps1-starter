/*
 * dt_enum.c -- enumerations (Unit 5, Section C).
 *
 * A C enum is an integer with nicer names. Nothing stops you from storing 47
 * in a dt_color, and nothing catches it later. Languages that treat
 * enumerations as their own type, such as Ada, Java, and Rust, keep the value
 * inside the set and refuse to convert it to an integer.
 *
 * You cannot change what C does. You can put the check in the one place every
 * read passes through, which is what these three functions are.
 */

#include "dt.h"

#include <string.h>

static const char *const COLOR_NAMES[] = { "RED", "GREEN", "BLUE" };

bool dt_enum_is_valid(int ordinal)
{
    /* TODO: true when the ordinal is at least 0 and less than DT_COLOR_COUNT.
       Check both ends. */
    (void)ordinal;
    (void)COLOR_NAMES; /* delete this line once you use the table below */
    return false;
}

dt_status dt_enum_name(int ordinal, const char **out)
{
    /* TODO: return DT_ERR_RANGE when the ordinal is outside the set, and the
       name otherwise. Indexing COLOR_NAMES before the check is the bug this
       function exists to prevent. */
    (void)ordinal;
    (void)out;
    return DT_ERR_RANGE;
}

dt_status dt_enum_from_name(const char *name, int *out)
{
    /* TODO: search COLOR_NAMES and return DT_ERR_RANGE when nothing matches.
       A name is not a number, so there is no numeric fallback here. */
    (void)name;
    (void)out;
    return DT_ERR_RANGE;
}

/*
 * dt_enum.c -- enumerations (Unit 5, Section C).
 *
 * A C enumeration type is compatible with an integer type and uses named
 * enumerators. A dt_color can still hold 47. This module instead accepts only
 * the three declared color ordinals. Other languages place different
 * restrictions on creating enumeration values from arbitrary integers.
 *
 * You cannot change what C does. You can put the check in the one place every
 * read passes through, which is what these three functions are.
 */

#include "dt.h"

#include <string.h>

static const char *const COLOR_NAMES[] = { "RED", "GREEN", "BLUE" };

/*
 * dt_enum_is_valid: true when the ordinal is one of the values in the set.
 * C lets you store any integer in an enum. This function refuses the integers
 * the set does not contain.
 */
bool dt_enum_is_valid(int ordinal)
{
    /* TODO: true when the ordinal is at least 0 and less than DT_COLOR_COUNT.
       Check both ends.
       dt_enum_is_valid(0)   -> true, RED
       dt_enum_is_valid(2)   -> true, BLUE
       dt_enum_is_valid(3)   -> false, one past the set
       dt_enum_is_valid(-1)  -> false, the end people forget */
    (void)ordinal;
    (void)COLOR_NAMES; /* delete this line once you use the table below */
    return false;
}

/*
 * dt_enum_name: write the name of the ordinal's value to *out. Returns
 * DT_ERR_RANGE when the ordinal is outside the set, and leaves *out alone then.
 */
dt_status dt_enum_name(int ordinal, const char **out)
{
    /* TODO: return DT_ERR_RANGE when the ordinal is outside the set, and the
       name otherwise. Indexing COLOR_NAMES before the check is the bug this
       function exists to prevent.
       dt_enum_name(0, &out)  -> DT_OK, *out = "RED"
       dt_enum_name(2, &out)  -> DT_OK, *out = "BLUE"
       dt_enum_name(3, &out)  -> DT_ERR_RANGE, *out untouched
       cases/normal/enum_names.case */
    (void)ordinal;
    (void)out;
    return DT_ERR_RANGE;
}

/*
 * dt_enum_from_name: find the name in the set and write its ordinal to *out.
 * Returns DT_ERR_RANGE when no value has that name. A name is not a number, so
 * there is no numeric fallback here.
 */
dt_status dt_enum_from_name(const char *name, int *out)
{
    /* TODO: search COLOR_NAMES and return DT_ERR_RANGE when nothing matches.
       A name is not a number, so there is no numeric fallback here.
       dt_enum_from_name("GREEN", &out)   -> DT_OK, out = 1
       dt_enum_from_name("PURPLE", &out)  -> DT_ERR_RANGE, out untouched
       dt_enum_from_name("1", &out)       -> DT_ERR_RANGE, since "1" is not a name
       cases/normal/enum_names.case */
    (void)name;
    (void)out;
    return DT_ERR_RANGE;
}

/*
 * dt_value.c -- the discriminated union (Unit 5, Section I).
 *
 * The constructors below are given. They are boilerplate and there is nothing
 * to learn from retyping them.
 *
 * The three checked readers at the bottom are yours. Each one confirms the tag
 * before it reads the payload. That confirmation is the entire difference
 * between a free union, which will happily reinterpret the bits of a pointer as
 * an integer, and a discriminated union, which will not.
 *
 * They refuse every read until you write them, so every `as` command in the
 * public corpus fails with exit 70. Resist the shortcut of returning the
 * payload unconditionally: `as str 42` would then hand the printer an integer
 * wearing a pointer's clothes, and what happens next is undefined behavior
 * rather than a wrong answer.
 */

#include "dt.h"

dt_value dt_value_nil(void)
{
    dt_value v = { .tag = DT_NIL, .as = { .integer = 0 } };
    return v;
}

dt_value dt_value_int(long long n)
{
    dt_value v = { .tag = DT_INT, .as = { .integer = n } };
    return v;
}

dt_value dt_value_enum(int ordinal)
{
    dt_value v = { .tag = DT_ENUM, .as = { .ordinal = ordinal } };
    return v;
}

dt_value dt_value_str(dt_str *s)
{
    dt_value v = { .tag = DT_STR, .as = { .string = s } };
    return v;
}

dt_value dt_value_array(dt_array *a)
{
    dt_value v = { .tag = DT_ARRAY, .as = { .array = a } };
    return v;
}

dt_value dt_value_map(dt_map *m)
{
    dt_value v = { .tag = DT_MAP, .as = { .map = m } };
    return v;
}

dt_value dt_value_record(dt_record *r)
{
    dt_value v = { .tag = DT_RECORD, .as = { .record = r } };
    return v;
}

dt_value dt_value_tuple(dt_tuple *t)
{
    dt_value v = { .tag = DT_TUPLE, .as = { .tuple = t } };
    return v;
}

dt_value dt_value_list(dt_list *l)
{
    dt_value v = { .tag = DT_LIST, .as = { .list = l } };
    return v;
}

dt_value dt_value_ref(dt_ref *p)
{
    dt_value v = { .tag = DT_REF, .as = { .ref = p } };
    return v;
}

/* ------------------------------------------------------------ your work */

dt_status dt_value_as_int(dt_value v, long long *out)
{
    /* TODO: on DT_INT, write v.as.integer to *out and return DT_OK.
       On anything else, return DT_ERR_TAG and leave *out alone. */
    (void)v;
    (void)out;
    return DT_ERR_TAG;
}

dt_status dt_value_as_enum(dt_value v, int *out)
{
    /* TODO: the same shape, for DT_ENUM and v.as.ordinal. */
    (void)v;
    (void)out;
    return DT_ERR_TAG;
}

dt_status dt_value_as_str(dt_value v, dt_str **out)
{
    /* TODO: the same shape, for DT_STR and v.as.string. */
    (void)v;
    (void)out;
    return DT_ERR_TAG;
}

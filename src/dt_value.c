/*
 * dt_value.c -- the discriminated union (Unit 5, Section I).
 *
 * The constructors below are written for you. They are boilerplate and there
 * is nothing to learn from retyping them.
 *
 * The three readers at the bottom are yours. Each one checks the tag before it
 * reads the payload. That check is the difference between a free union, which
 * will happily read the bits of a pointer as an integer, and a discriminated
 * union, which will not.
 *
 * They refuse every read until you write them, so every `as` command in the
 * corpus fails with exit 70.
 *
 * Do not take the shortcut of returning the payload without checking. Then
 * `as str 42` hands the printer an integer where a pointer belongs, and the
 * program has undefined behavior rather than a wrong answer.
 */

#include "dt.h"

/* dt_value_nil: the empty value, tagged DT_NIL. Given, complete. */
dt_value dt_value_nil(void)
{
    dt_value v = { .tag = DT_NIL, .as = { .integer = 0 } };
    return v;
}

/* dt_value_int: an integer value, tagged DT_INT. Given, complete. */
dt_value dt_value_int(long long n)
{
    dt_value v = { .tag = DT_INT, .as = { .integer = n } };
    return v;
}

/* dt_value_enum: an enumeration value, tagged DT_ENUM. Given, complete. */
dt_value dt_value_enum(int ordinal)
{
    dt_value v = { .tag = DT_ENUM, .as = { .ordinal = ordinal } };
    return v;
}

/* dt_value_str: a string value, tagged DT_STR. Given, complete. */
dt_value dt_value_str(dt_str *s)
{
    dt_value v = { .tag = DT_STR, .as = { .string = s } };
    return v;
}

/* dt_value_array: an array value, tagged DT_ARRAY. Given, complete. */
dt_value dt_value_array(dt_array *a)
{
    dt_value v = { .tag = DT_ARRAY, .as = { .array = a } };
    return v;
}

/* dt_value_map: an associative array value, tagged DT_MAP. Given, complete. */
dt_value dt_value_map(dt_map *m)
{
    dt_value v = { .tag = DT_MAP, .as = { .map = m } };
    return v;
}

/* dt_value_record: a record value, tagged DT_RECORD. Given, complete. */
dt_value dt_value_record(dt_record *r)
{
    dt_value v = { .tag = DT_RECORD, .as = { .record = r } };
    return v;
}

/* dt_value_tuple: a tuple value, tagged DT_TUPLE. Given, complete. */
dt_value dt_value_tuple(dt_tuple *t)
{
    dt_value v = { .tag = DT_TUPLE, .as = { .tuple = t } };
    return v;
}

/* dt_value_list: a list value, tagged DT_LIST. Given, complete. */
dt_value dt_value_list(dt_list *l)
{
    dt_value v = { .tag = DT_LIST, .as = { .list = l } };
    return v;
}

/* dt_value_ref: a reference value, tagged DT_REF. Given, complete. */
dt_value dt_value_ref(dt_ref *p)
{
    dt_value v = { .tag = DT_REF, .as = { .ref = p } };
    return v;
}

/* ------------------------------------------------------------ your work */

/*
 * dt_value_as_int: when v holds an integer, write it to *out and return DT_OK.
 * Otherwise return DT_ERR_TAG and leave *out alone. This is the tag check the
 * union exists for.
 */
dt_status dt_value_as_int(dt_value v, long long *out)
{
    /* TODO: if v.tag is DT_INT, write v.as.integer to *out and return DT_OK.
       Otherwise return DT_ERR_TAG and leave *out alone.
       dt_value_as_int(dt_value_int(42), &out)  -> DT_OK, out = 42
       dt_value_as_int(dt_value_str(s), &out)   -> DT_ERR_TAG, out untouched
       cases/normal/union_readers.case, cases/tag/as_int_on_string.case */
    (void)v;
    (void)out;
    return DT_ERR_TAG;
}

/*
 * dt_value_as_enum: same idea as dt_value_as_int, for an enumeration and its
 * ordinal.
 */
dt_status dt_value_as_enum(dt_value v, int *out)
{
    /* TODO: same idea, for DT_ENUM and v.as.ordinal.
       dt_value_as_enum(dt_value_enum(2), &out)  -> DT_OK, out = 2, which is BLUE
       dt_value_as_enum(dt_value_nil(), &out)    -> DT_ERR_TAG, out untouched
       cases/normal/union_readers.case, cases/tag/as_enum_on_nil.case */
    (void)v;
    (void)out;
    return DT_ERR_TAG;
}

/*
 * dt_value_as_str: same idea as dt_value_as_int, for a string and its pointer.
 */
dt_status dt_value_as_str(dt_value v, dt_str **out)
{
    /* TODO: same idea, for DT_STR and v.as.string.
       dt_value_as_str(dt_value_str(s), &out)  -> DT_OK, *out is s
       dt_value_as_str(dt_value_int(42), &out) -> DT_ERR_TAG, *out untouched, and
                                                  this refusal is what stops the
                                                  printer reading 42 as an address
       cases/normal/union_readers.case, cases/tag/as_str_on_int.case */
    (void)v;
    (void)out;
    return DT_ERR_TAG;
}

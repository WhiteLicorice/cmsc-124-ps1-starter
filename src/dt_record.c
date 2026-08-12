/*
 * dt_record.c -- records (Unit 5, Section F).
 *
 * A record's fields are selected by name, and in a compiled language that name
 * is gone by run time: the compiler knows every field and its offset, so
 * `employee.salary` becomes an addition it can compute while compiling.
 *
 * Here the offset table is visible, which is the only real difference. You hold
 * the field names in an array, and looking one up is a search that finds an
 * index. A production record would not do that search at run time. Building it
 * this way is what makes the table something you can point at.
 *
 * A name the record never declared is DT_ERR_FIELD. It does not quietly become
 * a new field, which is the line between a record and an associative array.
 */

#include "dt.h"

#include <stdlib.h>
#include <string.h>

struct dt_record {
    char    *names[DT_RECORD_MAX_FIELDS];
    dt_value values[DT_RECORD_MAX_FIELDS];
    size_t   count;
};

dt_record *dt_record_new(const char **field_names, size_t field_count)
{
    /* TODO: reject more than DT_RECORD_MAX_FIELDS by returning NULL, copy each
       name, and initialise every field to dt_value_nil(). */
    (void)field_names;
    (void)field_count;
    return NULL;
}

void dt_record_free(dt_record *r)
{
    /* TODO: free the copied names and the record. */
    (void)r;
}

size_t dt_record_field_count(const dt_record *r)
{
    (void)r;
    return 0;
}

dt_status dt_record_field_name(const dt_record *r, size_t index, const char **out)
{
    /* TODO: declaration order, DT_ERR_RANGE past the end. The printer walks
       this, so the order it returns is the order a record prints in. */
    (void)r;
    (void)index;
    (void)out;
    return DT_ERR_RANGE;
}

dt_status dt_record_get(const dt_record *r, const char *field, dt_value *out)
{
    /* TODO: find the index for `field`, DT_ERR_FIELD when there is none. */
    (void)r;
    (void)field;
    (void)out;
    return DT_ERR_FIELD;
}

dt_status dt_record_set(dt_record *r, const char *field, dt_value v)
{
    /* TODO: the same lookup, then the write. Never append a new field. */
    (void)r;
    (void)field;
    (void)v;
    return DT_ERR_FIELD;
}

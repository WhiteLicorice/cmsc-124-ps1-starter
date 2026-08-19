/*
 * dt_record.c -- records (Unit 5, Section F).
 *
 * A record selects its parts by name. In a compiled language the name is gone
 * by run time. The compiler knows every field and its offset, so
 * employee.salary becomes an addition it computes while compiling. There is no
 * search.
 *
 * Here the table of names is visible, which is the only difference. You keep the
 * field names in an array, and looking one up is a search that returns an
 * index. A production record would not search at run time. Building it this way
 * makes the table something you can point at.
 *
 * A name the record does not declare gives DT_ERR_FIELD. It does not become a
 * new field. That refusal is the line between a record and an associative
 * array.
 */

#include "dt.h"

#include <stdlib.h>
#include <string.h>

struct dt_record {
    char    *names[DT_RECORD_MAX_FIELDS];
    dt_value values[DT_RECORD_MAX_FIELDS];
    size_t   count;
};

/*
 * dt_record_new: build a record with the given field names, in the order they
 * are listed, and every field set to nil. Each name is copied. Returns NULL
 * when there are more than DT_RECORD_MAX_FIELDS fields, or when an allocation
 * fails.
 */
dt_record *dt_record_new(const char **field_names, size_t field_count)
{
    /* TODO: return NULL for more than DT_RECORD_MAX_FIELDS, copy each name,
       and set every field to dt_value_nil().
       fields {"name", "age"}       -> a record with two nil fields, in that order
       eight fields                 -> fine, DT_RECORD_MAX_FIELDS is 8
       nine fields                  -> NULL, which the driver reports as DT_ERR_CAPACITY
       cases/normal/record_basics.case, cases/capacity/record_max_fields.case,
       cases/capacity/record_over_fields.case */
    (void)field_names;
    (void)field_count;
    return NULL;
}

/*
 * dt_record_free: free the copied names, then the record. Accepts NULL and does
 * nothing then. The field values belong to the environment and are not freed.
 */
void dt_record_free(dt_record *r)
{
    /* TODO: free the copied names, then the record.
       a record holding a string value  -> the names go, the string stays
       dt_record_free(NULL)             -> returns, having done nothing */
    (void)r;
}

/*
 * dt_record_field_count: how many fields the record has. This reads a field, so
 * it takes the same time no matter how many fields there are.
 */
size_t dt_record_field_count(const dt_record *r)
{
    /* TODO: read the field the constructor stored. A record never grows, so this
       is the same number for the record's whole life.
       after `rec new person name age`:  dt_record_field_count(person) -> 2
       cases/normal/record_basics.case */
    (void)r;
    return 0;
}

/*
 * dt_record_field_name: write the name at position `index` in declaration order
 * to *out. Returns DT_ERR_RANGE when the index is past the end, and leaves
 * *out alone then. This is the order the record prints in.
 */
dt_status dt_record_field_name(const dt_record *r, size_t index, const char **out)
{
    /* TODO: return names in declaration order, or DT_ERR_RANGE past the end.
       The printer walks this, so this order is the order a record prints in.
       after `rec new person name age`:
         dt_record_field_name(person, 0, &out)  -> DT_OK, *out = "name"
         dt_record_field_name(person, 2, &out)  -> DT_ERR_RANGE, *out untouched
       cases/normal/record_basics.case */
    (void)r;
    (void)index;
    (void)out;
    return DT_ERR_RANGE;
}

/*
 * dt_record_get: write the value of the field named `field` to *out. Returns
 * DT_ERR_FIELD when the record has no such field, and leaves *out alone then.
 */
dt_status dt_record_get(const dt_record *r, const char *field, dt_value *out)
{
    /* TODO: find the index for `field`, or DT_ERR_FIELD when there is none.
       after `rec set person age 36`:
         dt_record_get(person, "age", &out)      -> DT_OK, *out is the integer 36
         dt_record_get(person, "salary", &out)   -> DT_ERR_FIELD, *out untouched
       cases/normal/record_basics.case, cases/boundary/record_unknown_field.case */
    (void)r;
    (void)field;
    (void)out;
    return DT_ERR_FIELD;
}

/*
 * dt_record_set: replace the value of the field named `field` with v. Returns
 * DT_ERR_FIELD when the record has no such field, and changes nothing then. A
 * record never grows a field it was not built with.
 */
dt_status dt_record_set(dt_record *r, const char *field, dt_value v)
{
    /* TODO: same lookup, then the write. Never add a new field. Refusing an
       undeclared name is the whole difference between a record and a map.
       after `rec new person name age`:
         dt_record_set(person, "age", dt_value_int(36))     -> DT_OK
         dt_record_set(person, "salary", dt_value_int(1))   -> DT_ERR_FIELD, and
                                                               no field is created
       cases/normal/record_basics.case, cases/boundary/record_unknown_field.case */
    (void)r;
    (void)field;
    (void)v;
    return DT_ERR_FIELD;
}

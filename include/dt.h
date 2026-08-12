/*
 * dt.h -- CMSC 124 Problem Set 1: Data Types
 *
 * This header is fixed. Do not edit it. The driver in src/ is written against
 * exactly these declarations, and the grading corpus drives that driver, so a
 * change here breaks the build rather than earning you points.
 *
 * Your work is the ten .c files in src/ named dt_*.c. Every one of them
 * implements one category from Unit 5 of the syllabus.
 *
 * Two rules run through the whole interface.
 *
 * 1. Every operation that can fail returns dt_status. It never reports failure
 *    through a sentinel value, because there is no integer that is not also a
 *    legal answer for dt_int_add.
 *
 * 2. Containers do not own the values inside them. The driver's environment
 *    owns every named object and frees it at exit. dt_array_free releases the
 *    array's own storage and nothing else. This keeps ownership out of nine
 *    modules so that it can be the entire point of the tenth, dt_ref.
 */

#ifndef DT_H
#define DT_H

#ifdef __cplusplus
#error "CMSC 124 Problem Set 1 is a C17 assignment. Do not compile it as C++."
#endif

#include <stdbool.h>
#include <stddef.h>

/* ------------------------------------------------------------------ status */

/*
 * One status code per way an operation can fail. The driver turns a non-OK
 * status into a diagnostic on stderr and exit code 70. You never print from
 * inside a dt_ module.
 */
typedef enum {
    DT_OK = 0,
    DT_ERR_OVERFLOW,  /* a checked integer operation left the representable range */
    DT_ERR_RANGE,     /* an index fell outside a container's bounds */
    DT_ERR_KEY,       /* an associative-array key was not present */
    DT_ERR_FIELD,     /* a record has no field by that name */
    DT_ERR_TAG,       /* a value was read as the wrong alternative of the union */
    DT_ERR_EMPTY,     /* car or cdr was taken of the empty list */
    DT_ERR_CAPACITY,  /* a fixed-arity structure was given more parts than it holds */
    DT_ERR_RELEASED,  /* an owned reference was read or released after release */
    DT_ERR_LEAK       /* an owned reference was still live when the program ended */
} dt_status;

/* Human-readable name for a status, for the driver's diagnostics. */
const char *dt_status_message(dt_status status);

/* ------------------------------------------------------- the tagged union */

typedef enum {
    DT_NIL = 0,
    DT_INT,
    DT_STR,
    DT_ENUM,
    DT_ARRAY,
    DT_MAP,
    DT_RECORD,
    DT_TUPLE,
    DT_LIST,
    DT_REF
} dt_tag;

typedef struct dt_str    dt_str;
typedef struct dt_array  dt_array;
typedef struct dt_map    dt_map;
typedef struct dt_record dt_record;
typedef struct dt_tuple  dt_tuple;
typedef struct dt_list   dt_list;
typedef struct dt_ref    dt_ref;

/*
 * One value type, ten alternatives, one tag saying which alternative is live.
 * Every container below stores dt_value, so this struct is the thing the other
 * nine modules are made of rather than a tenth topic beside them.
 */
typedef struct {
    dt_tag tag;
    union {
        long long  integer; /* DT_INT  */
        int        ordinal; /* DT_ENUM */
        dt_str    *string;  /* DT_STR  */
        dt_array  *array;   /* DT_ARRAY */
        dt_map    *map;     /* DT_MAP  */
        dt_record *record;  /* DT_RECORD */
        dt_tuple  *tuple;   /* DT_TUPLE */
        dt_list   *list;    /* DT_LIST */
        dt_ref    *ref;     /* DT_REF  */
    } as;
} dt_value;

/* Constructors. These cannot fail, so they return the value directly. */
dt_value dt_value_nil(void);
dt_value dt_value_int(long long n);
dt_value dt_value_enum(int ordinal);
dt_value dt_value_str(dt_str *s);
dt_value dt_value_array(dt_array *a);
dt_value dt_value_map(dt_map *m);
dt_value dt_value_record(dt_record *r);
dt_value dt_value_tuple(dt_tuple *t);
dt_value dt_value_list(dt_list *l);
dt_value dt_value_ref(dt_ref *p);

/* Name of a tag, for diagnostics and for the `tag` command: "int", "str", ... */
const char *dt_tag_name(dt_tag tag);

/*
 * Checked readers. Each one confirms the tag before touching the payload and
 * returns DT_ERR_TAG when the value holds a different alternative. This is the
 * discipline a free union cannot enforce and a discriminated union can.
 */
dt_status dt_value_as_int(dt_value v, long long *out);
dt_status dt_value_as_enum(dt_value v, int *out);
dt_status dt_value_as_str(dt_value v, dt_str **out);

/* ------------------------------------------------------- checked integers */

/*
 * Overflow is a language-level choice. C's signed overflow is undefined
 * behavior, so these detect it before it happens rather than computing a wrong
 * answer and inspecting the wreckage afterward.
 *
 * On DT_ERR_OVERFLOW, *out is left untouched.
 */
dt_status dt_int_add(long long a, long long b, long long *out);
dt_status dt_int_sub(long long a, long long b, long long *out);
dt_status dt_int_mul(long long a, long long b, long long *out);

/* --------------------------------------------------------------- strings */

/*
 * A string that carries its own length instead of hunting for a terminator.
 * The bytes are not required to be NUL-free, and dt_str_len is O(1).
 */
dt_str   *dt_str_new(const char *bytes, size_t length);
void      dt_str_free(dt_str *s);
size_t    dt_str_len(const dt_str *s);
const char *dt_str_bytes(const dt_str *s); /* not NUL-terminated; use with len */
dt_status dt_str_append(dt_str *s, const char *bytes, size_t length);
dt_status dt_str_substr(const dt_str *s, size_t start, size_t length, dt_str **out);
bool      dt_str_eq(const dt_str *a, const dt_str *b);

/* ---------------------------------------------------------- enumerations */

/*
 * A fixed enumeration, named rather than numbered. Ordinals outside the domain
 * are rejected instead of silently coerced to an integer.
 */
typedef enum {
    DT_COLOR_RED = 0,
    DT_COLOR_GREEN,
    DT_COLOR_BLUE,
    DT_COLOR_COUNT
} dt_color;

bool      dt_enum_is_valid(int ordinal);
dt_status dt_enum_name(int ordinal, const char **out);
dt_status dt_enum_from_name(const char *name, int *out);

/* --------------------------------------------------------------- arrays */

/*
 * An array descriptor: element storage plus the lower bound its indices start
 * from. A lower bound of 1 is legal, which is why every access needs the
 * subtraction rather than using the index as the offset.
 */
dt_array *dt_array_new(size_t length, long long lower_bound);
void      dt_array_free(dt_array *a);
size_t    dt_array_len(const dt_array *a);
long long dt_array_lower_bound(const dt_array *a);
dt_status dt_array_get(const dt_array *a, long long index, dt_value *out);
dt_status dt_array_set(dt_array *a, long long index, dt_value v);

/* ---------------------------------------------------- associative arrays */

/*
 * Keys select values, and unlike an array the structure stores its keys.
 * Traversal is in insertion order so that printing a map is deterministic;
 * a deleted key leaves that order, and re-inserting it puts it at the end.
 */
dt_map   *dt_map_new(void);
void      dt_map_free(dt_map *m);
size_t    dt_map_len(const dt_map *m);
dt_status dt_map_put(dt_map *m, const char *key, dt_value v);
dt_status dt_map_get(const dt_map *m, const char *key, dt_value *out);
dt_status dt_map_remove(dt_map *m, const char *key);
/* index-th key in insertion order; DT_ERR_RANGE past the end */
dt_status dt_map_key_at(const dt_map *m, size_t index, const char **out);

/* --------------------------------------------------------------- records */

#define DT_RECORD_MAX_FIELDS 8

/*
 * Fields are selected by name at compile time in a real language; here they are
 * selected by name at run time, which is the same idea with the offset table
 * made visible. A name the record does not declare is DT_ERR_FIELD, not a
 * silently added field.
 */
dt_record *dt_record_new(const char **field_names, size_t field_count);
void       dt_record_free(dt_record *r);
size_t     dt_record_field_count(const dt_record *r);
dt_status  dt_record_field_name(const dt_record *r, size_t index, const char **out);
dt_status  dt_record_get(const dt_record *r, const char *field, dt_value *out);
dt_status  dt_record_set(dt_record *r, const char *field, dt_value v);

/* ---------------------------------------------------------------- tuples */

#define DT_TUPLE_MAX_ARITY 8

/*
 * Positions instead of names. Built once from its parts and read by index
 * afterward, which is the whole difference from a record.
 */
dt_tuple *dt_tuple_new(const dt_value *values, size_t count);
void      dt_tuple_free(dt_tuple *t);
size_t    dt_tuple_arity(const dt_tuple *t);
dt_status dt_tuple_at(const dt_tuple *t, size_t index, dt_value *out);

/* ----------------------------------------------------------------- lists */

/*
 * Cons cells. dt_list_nil() is the empty list and is a null pointer, so an
 * empty list costs nothing. cdr returns the shared tail rather than a copy,
 * which is what makes cons cheap and why two lists can share a suffix.
 */
dt_list  *dt_list_nil(void);
dt_list  *dt_list_cons(dt_value head, dt_list *tail);
void      dt_list_free(dt_list *l); /* frees this one cell, never its tail */
size_t    dt_list_len(const dt_list *l);
dt_status dt_list_car(const dt_list *l, dt_value *out);
dt_status dt_list_cdr(const dt_list *l, dt_list **out);

/* ------------------------------------------------------ owned references */

/*
 * The one module where ownership is the lesson. dt_ref_new allocates a cell
 * holding a copy of the value, and the reference owns that cell. It does not
 * own whatever the value points at: `ref new r @s` aliases the string s, and
 * releasing r frees the cell rather than the string.
 *
 * Reading through a released reference is a dangling read and is caught;
 * releasing twice is caught; a reference never released is a leak, which the
 * driver reports at exit. C detects none of these three for you, which is the
 * point of building the checks by hand.
 */
dt_ref   *dt_ref_new(dt_value v);
dt_status dt_ref_borrow(const dt_ref *p, dt_value *out);
dt_status dt_ref_release(dt_ref *p);
bool      dt_ref_is_released(const dt_ref *p);
void      dt_ref_destroy(dt_ref *p); /* frees the handle itself; driver-only */

#endif /* DT_H */

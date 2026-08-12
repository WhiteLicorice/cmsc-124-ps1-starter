/*
 * dt.h -- CMSC 124 Problem Set 1: Data Types
 *
 * This header is fixed. Do not edit it. The driver in src/ is written against
 * these exact declarations and the grading corpus drives that driver, so a
 * change here breaks the build.
 *
 * Your work is the ten files in src/ named dt_*.c. Each one implements one
 * category from Unit 5 of the syllabus.
 *
 * Two rules run through the whole interface.
 *
 * 1. Every operation that can fail returns dt_status. None of them report
 *    failure with a special return value. There is no integer dt_int_add could
 *    return that would not also be a correct answer.
 *
 * 2. Containers do not own the values inside them. The driver's environment
 *    owns every named object and frees it at exit. dt_array_free releases the
 *    array's own memory and nothing else. That keeps ownership out of nine
 *    modules so that the tenth, dt_ref, can be about ownership alone.
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
 * One code per way an operation can fail. The driver turns any code other than
 * DT_OK into a message on stderr and exit code 70. Your modules never print.
 */
typedef enum {
    DT_OK = 0,
    DT_ERR_OVERFLOW,  /* a checked integer operation left the usable range */
    DT_ERR_RANGE,     /* an index or an ordinal fell outside its bounds */
    DT_ERR_KEY,       /* an associative array has no such key */
    DT_ERR_FIELD,     /* a record has no field with that name */
    DT_ERR_TAG,       /* a value was read as the wrong alternative */
    DT_ERR_EMPTY,     /* car or cdr was taken of the empty list */
    DT_ERR_CAPACITY,  /* a fixed-size structure was given too many parts */
    DT_ERR_RELEASED,  /* a reference was read or released after release */
    DT_ERR_LEAK       /* a reference was still holding memory when the program ended */
} dt_status;

/* The text the driver prints for a status. */
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
 * The value type has ten alternatives and a tag saying which one is in use.
 * Every container below stores dt_value, so this struct is what the other nine
 * modules are built out of.
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

/* Constructors. These cannot fail, so they return the value itself. */
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

/* Name of a tag, for messages and for the `tag` command: "int", "str", ... */
const char *dt_tag_name(dt_tag tag);

/*
 * Checked readers. Each one confirms the tag before it touches the payload and
 * returns DT_ERR_TAG when the value holds a different alternative. A free union
 * cannot enforce this. A discriminated union can.
 */
dt_status dt_value_as_int(dt_value v, long long *out);
dt_status dt_value_as_enum(dt_value v, int *out);
dt_status dt_value_as_str(dt_value v, dt_str **out);

/* ------------------------------------------------------- checked integers */

/*
 * What happens on overflow is a language design decision. C's signed overflow
 * is undefined behavior, so these functions detect it before it happens rather
 * than computing a wrong answer and checking afterward.
 *
 * When the result is DT_ERR_OVERFLOW, *out is not written.
 */
dt_status dt_int_add(long long a, long long b, long long *out);
dt_status dt_int_sub(long long a, long long b, long long *out);
dt_status dt_int_mul(long long a, long long b, long long *out);

/* --------------------------------------------------------------- strings */

/*
 * A string that stores its own length. The bytes may include a zero, and
 * dt_str_len takes the same time no matter how long the string is.
 */
dt_str   *dt_str_new(const char *bytes, size_t length);
void      dt_str_free(dt_str *s);
size_t    dt_str_len(const dt_str *s);
const char *dt_str_bytes(const dt_str *s); /* no terminator, so pair it with len */
dt_status dt_str_append(dt_str *s, const char *bytes, size_t length);
dt_status dt_str_substr(const dt_str *s, size_t start, size_t length, dt_str **out);
bool      dt_str_eq(const dt_str *a, const dt_str *b);

/* ---------------------------------------------------------- enumerations */

/*
 * A fixed set of named values. Ordinals outside the set are rejected instead of
 * being treated as ordinary integers.
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
 * An array descriptor: the elements, plus the lower bound its indices start
 * from. A lower bound of 1 is allowed, so every access needs the subtraction
 * instead of using the index as the offset.
 */
dt_array *dt_array_new(size_t length, long long lower_bound);
void      dt_array_free(dt_array *a);
size_t    dt_array_len(const dt_array *a);
long long dt_array_lower_bound(const dt_array *a);
dt_status dt_array_get(const dt_array *a, long long index, dt_value *out);
dt_status dt_array_set(dt_array *a, long long index, dt_value v);

/* ---------------------------------------------------- associative arrays */

/*
 * Keys select values, and unlike an array this structure stores its keys.
 * Traversal follows insertion order so that printing a map gives the same
 * output every time. A removed key leaves that order, and adding it again puts
 * it at the end.
 */
dt_map   *dt_map_new(void);
void      dt_map_free(dt_map *m);
size_t    dt_map_len(const dt_map *m);
dt_status dt_map_put(dt_map *m, const char *key, dt_value v);
dt_status dt_map_get(const dt_map *m, const char *key, dt_value *out);
dt_status dt_map_remove(dt_map *m, const char *key);
/* the key at this position in insertion order, or DT_ERR_RANGE past the end */
dt_status dt_map_key_at(const dt_map *m, size_t index, const char **out);

/* --------------------------------------------------------------- records */

#define DT_RECORD_MAX_FIELDS 8

/*
 * A compiled language selects record fields by name while compiling. Here the
 * lookup happens at run time, which is the same idea with the table of names
 * left visible. A name the record does not declare gives DT_ERR_FIELD, and the
 * record keeps the fields it was built with.
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
 * A tuple selects its parts by position. It is built once from those parts and
 * read by index afterward, which is the whole difference from a record.
 */
dt_tuple *dt_tuple_new(const dt_value *values, size_t count);
void      dt_tuple_free(dt_tuple *t);
size_t    dt_tuple_arity(const dt_tuple *t);
dt_status dt_tuple_at(const dt_tuple *t, size_t index, dt_value *out);

/* ----------------------------------------------------------------- lists */

/*
 * Cons cells. dt_list_nil() is the empty list and is a null pointer, so an
 * empty list needs no memory. cdr returns the tail itself, which both lists go
 * on sharing. That is what makes cons cheap.
 */
dt_list  *dt_list_nil(void);
dt_list  *dt_list_cons(dt_value head, dt_list *tail);
void      dt_list_free(dt_list *l); /* frees this one cell, never its tail */
size_t    dt_list_len(const dt_list *l);
dt_status dt_list_car(const dt_list *l, dt_value *out);
dt_status dt_list_cdr(const dt_list *l, dt_list **out);

/* ------------------------------------------------------ owned references */

/*
 * The one module where ownership is the whole point. dt_ref_new allocates a
 * cell holding a copy of the value. The reference owns that cell and nothing
 * further. After `ref new r @s` the reference and the name s
 * share one string, so releasing r frees the cell and leaves the string alone.
 *
 * Reading through a released reference, releasing twice, and never releasing at
 * all are three mistakes C does not catch. Here you catch them yourself.
 */
dt_ref   *dt_ref_new(dt_value v);
dt_status dt_ref_borrow(const dt_ref *p, dt_value *out);
dt_status dt_ref_release(dt_ref *p);
bool      dt_ref_is_released(const dt_ref *p);
void      dt_ref_destroy(dt_ref *p); /* frees the handle itself, driver only */

#endif /* DT_H */

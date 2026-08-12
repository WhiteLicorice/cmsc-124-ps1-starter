/*
 * dt_str.c -- length-carrying strings (Unit 5, Section B).
 *
 * C's own string is a pointer to bytes that ends at the first zero. That design
 * makes strlen cost a walk, makes a string with a zero byte in the middle
 * unrepresentable, and makes appending a question about capacity that the
 * representation itself cannot answer, because a terminator does not know how
 * much room follows it.
 *
 * This one stores length and capacity beside the bytes. dt_str_len is a field
 * read. A zero byte is an ordinary byte. Appending knows when to grow.
 *
 * Keep one byte of slack and write a terminator anyway if you like; the printer
 * never relies on it, but a debugger session is friendlier when it is there.
 */

#include "dt.h"

#include <stdlib.h>
#include <string.h>

struct dt_str {
    char  *bytes;
    size_t length;
    size_t capacity;
};

dt_str *dt_str_new(const char *bytes, size_t length)
{
    /* TODO: allocate the handle and a buffer, copy `length` bytes in with
       memcpy rather than strcpy, and record the length. Return NULL if an
       allocation fails. */
    (void)bytes;
    (void)length;
    return NULL;
}

void dt_str_free(dt_str *s)
{
    /* TODO: free the buffer, then the handle. Tolerate NULL. */
    (void)s;
}

size_t dt_str_len(const dt_str *s)
{
    /* TODO: one field read, no walking. */
    (void)s;
    return 0;
}

const char *dt_str_bytes(const dt_str *s)
{
    /* TODO: return the buffer. The caller pairs it with dt_str_len. */
    (void)s;
    return "";
}

dt_status dt_str_append(dt_str *s, const char *bytes, size_t length)
{
    /* TODO: grow the buffer when length would not fit, then copy. Doubling the
       capacity keeps a sequence of appends from being quadratic. */
    (void)s;
    (void)bytes;
    (void)length;
    return DT_ERR_CAPACITY;
}

dt_status dt_str_substr(const dt_str *s, size_t start, size_t length, dt_str **out)
{
    /* TODO: DT_ERR_RANGE when start + length runs past the end. Watch that
       sum: two size_t values can wrap, so compare start against the length
       first and then length against what remains. */
    (void)s;
    (void)start;
    (void)length;
    (void)out;
    return DT_ERR_RANGE;
}

bool dt_str_eq(const dt_str *a, const dt_str *b)
{
    /* TODO: lengths first, then memcmp. strcmp would stop at an interior zero
       byte and call two different strings equal. */
    (void)a;
    (void)b;
    return false;
}

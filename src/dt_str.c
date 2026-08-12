/*
 * dt_str.c -- strings that carry their length (Unit 5, Section B).
 *
 * A C string is a pointer to bytes that ends at the first zero byte. Finding the
 * length therefore means walking the whole string, a string cannot contain a
 * zero byte, and the string does not know how much memory it has, so appending
 * safely needs information it does not store.
 *
 * Yours keeps the length and the capacity next to the bytes. dt_str_len reads
 * a field. A zero byte is an ordinary byte. Appending knows when to grow.
 *
 * You may write a terminating zero after the last byte if you like. The
 * printer never depends on it, but it makes debugging easier.
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
    /* TODO: allocate the handle and a buffer, copy `length` bytes with memcpy
       rather than strcpy, and store the length. Return NULL if an allocation
       fails. */
    (void)bytes;
    (void)length;
    return NULL;
}

void dt_str_free(dt_str *s)
{
    /* TODO: free the buffer, then the handle. Accept NULL without crashing. */
    (void)s;
}

size_t dt_str_len(const dt_str *s)
{
    /* TODO: read the field. Do not walk the bytes. */
    (void)s;
    return 0;
}

const char *dt_str_bytes(const dt_str *s)
{
    /* TODO: return the buffer. The caller uses it together with dt_str_len. */
    (void)s;
    return "";
}

dt_status dt_str_append(dt_str *s, const char *bytes, size_t length)
{
    /* TODO: grow the buffer when the new bytes do not fit, then copy them.
       Double the capacity each time. Growing by just enough makes a series of
       appends slow because every append copies the whole string again. */
    (void)s;
    (void)bytes;
    (void)length;
    return DT_ERR_CAPACITY;
}

dt_status dt_str_substr(const dt_str *s, size_t start, size_t length, dt_str **out)
{
    /* TODO: return DT_ERR_RANGE when the piece runs past the end. Careful with
       that test. Two size_t values can wrap around, so compare start against
       the length first, then length against what is left. */
    (void)s;
    (void)start;
    (void)length;
    (void)out;
    return DT_ERR_RANGE;
}

bool dt_str_eq(const dt_str *a, const dt_str *b)
{
    /* TODO: compare the lengths first, then use memcmp. strcmp would stop at a
       zero byte in the middle and call two different strings equal. */
    (void)a;
    (void)b;
    return false;
}

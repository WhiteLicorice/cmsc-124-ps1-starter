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

/*
 * dt_str_new: build a string that holds a copy of the first `length` bytes of
 * `bytes`. A zero byte in the middle is a normal byte. Returns NULL when an
 * allocation fails.
 */
dt_str *dt_str_new(const char *bytes, size_t length)
{
    /* TODO: allocate the handle and a buffer, copy `length` bytes with memcpy
       rather than strcpy, and store the length. Return NULL if an allocation
       fails.
       dt_str_new("hello", 5)  -> a string whose dt_str_len is 5
       dt_str_new("a\0b", 3)   -> a string whose dt_str_len is 3, not 1
       cases/normal/string_building.case, cases/capacity/embedded_zero_byte.case */
    (void)bytes;
    (void)length;
    return NULL;
}

/*
 * dt_str_free: release the buffer and the handle. Accepts NULL and does
 * nothing then.
 */
void dt_str_free(dt_str *s)
{
    /* TODO: free the buffer, then the handle. Accept NULL without crashing.
       dt_str_free(s)     -> the buffer and the handle are both released
       dt_str_free(NULL)  -> returns, having done nothing */
    (void)s;
}

/*
 * dt_str_len: how many bytes the string holds. This reads a field, so it takes
 * the same time no matter how long the string is.
 */
size_t dt_str_len(const dt_str *s)
{
    /* TODO: read the field. Do not walk the bytes.
       after `str new greeting "hello"` then `str append greeting ", world"`:
         dt_str_len(greeting) -> 12
       cases/normal/string_building.case */
    (void)s;
    return 0;
}

/*
 * dt_str_bytes: the string's bytes. There is no terminating zero, so pair this
 * with dt_str_len rather than treating it as a C string.
 */
const char *dt_str_bytes(const dt_str *s)
{
    /* TODO: return the buffer. The caller uses it together with dt_str_len.
       after `str new s "a\0b"`:
         dt_str_bytes(s) -> the three bytes 'a', 0, 'b', with no terminator
                            promised, so read exactly dt_str_len(s) of them
       cases/capacity/embedded_zero_byte.case */
    (void)s;
    return "";
}

/*
 * dt_str_append: add `length` bytes to the end of the string, growing the
 * buffer when they do not fit. Returns DT_ERR_CAPACITY when an allocation
 * fails. The string keeps its earlier bytes.
 */
dt_status dt_str_append(dt_str *s, const char *bytes, size_t length)
{
    /* TODO: grow the buffer when the new bytes do not fit, then copy them.
       Double the capacity each time. Growing by just enough makes a series of
       appends slow because every append copies the whole string again.
       s holds "hello": dt_str_append(s, ", world", 7) -> DT_OK, len is now 12
       an allocation failure                           -> DT_ERR_CAPACITY, s unchanged
       cases/normal/string_building.case, cases/capacity/string_growth.case */
    (void)s;
    (void)bytes;
    (void)length;
    return DT_ERR_CAPACITY;
}

/*
 * dt_str_substr: build a new string from `length` bytes starting at `start`.
 * Returns DT_ERR_RANGE when the piece runs past the end, and DT_ERR_CAPACITY
 * when an allocation fails. The original string is not changed.
 */
dt_status dt_str_substr(const dt_str *s, size_t start, size_t length, dt_str **out)
{
    /* TODO: return DT_ERR_RANGE when the piece runs past the end. Careful with
       that test. Two size_t values can wrap around, so compare start against
       the length first, then length against what is left.
       s holds "hello" (length 5):
         dt_str_substr(s, 3, 2, &out)  -> DT_OK, *out is "lo"
         dt_str_substr(s, 5, 0, &out)  -> DT_OK, *out is "", which is not an error
         dt_str_substr(s, 3, 5, &out)  -> DT_ERR_RANGE, *out untouched
       an allocation failure           -> DT_ERR_CAPACITY, *out untouched
       cases/boundary/substr_exact_end.case, cases/boundary/substr_past_end.case */
    (void)s;
    (void)start;
    (void)length;
    (void)out;
    return DT_ERR_RANGE;
}

/*
 * dt_str_eq: true when both strings hold the same bytes. The comparison uses
 * the stored lengths, so a zero byte in the middle is compared like any other
 * byte instead of ending the comparison early.
 */
bool dt_str_eq(const dt_str *a, const dt_str *b)
{
    /* TODO: compare the lengths first, then use memcmp. strcmp would stop at a
       zero byte in the middle and call two different strings equal.
       "world" and "world"  -> true
       "hello" and "world"  -> false
       "a\0b" and "a"       -> false, and their lengths differ, 3 against 1
       cases/normal/string_building.case, cases/capacity/embedded_zero_byte.case */
    (void)a;
    (void)b;
    return false;
}

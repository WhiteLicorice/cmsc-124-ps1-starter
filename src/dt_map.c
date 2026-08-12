/*
 * dt_map.c -- associative arrays (Unit 5, Section E).
 *
 * The difference from an array is one sentence. An array does not store its
 * indices. This stores its keys. That is why an array position costs one
 * subtraction and a key costs a hash plus at least one comparison.
 *
 * Two requirements drive the code.
 *
 * Hashing. Turn the key into a bucket number, then compare keys inside that
 * bucket, because two keys can land in the same bucket. Making each bucket a
 * linked list is the shortest correct answer. FNV-1a is four lines. Start the
 * accumulator at 14695981039346656037, then for each byte, exclusive-or the
 * byte into it and multiply by 1099511628211.
 *
 * Insertion order. Printing a map has to be repeatable, or nobody can write an
 * expected-output file. Bucket order depends on the hash function, so keep a
 * separate list of keys in the order they were first added. dt_map_key_at
 * reads that list. Adding an existing key replaces its value and keeps its
 * position. Removing a key takes it out of the list, and adding it again puts
 * it at the end.
 */

#include "dt.h"

#include <stdlib.h>
#include <string.h>

struct dt_map {
    int placeholder; /* TODO: replace with your buckets and your key order. */
};

dt_map *dt_map_new(void)
{
    /* TODO: an empty map. Not NULL, which means the allocation failed. */
    return NULL;
}

void dt_map_free(dt_map *m)
{
    /* TODO: free every list node, every copied key, and the map itself. The
       values belong to the environment, so leave them alone. */
    (void)m;
}

size_t dt_map_len(const dt_map *m)
{
    (void)m;
    return 0;
}

dt_status dt_map_put(dt_map *m, const char *key, dt_value v)
{
    /* TODO: replace the value when the key is already there, and add it
       otherwise. Copy the key. The caller's buffer does not last past the
       command. */
    (void)m;
    (void)key;
    (void)v;
    return DT_ERR_KEY;
}

dt_status dt_map_get(const dt_map *m, const char *key, dt_value *out)
{
    /* TODO: return DT_ERR_KEY when the key is absent. A missing key is not
       nil. */
    (void)m;
    (void)key;
    (void)out;
    return DT_ERR_KEY;
}

dt_status dt_map_remove(dt_map *m, const char *key)
{
    /* TODO: unlink the entry from its bucket and from the insertion order,
       free the copied key, and return DT_ERR_KEY when it was not there. */
    (void)m;
    (void)key;
    return DT_ERR_KEY;
}

dt_status dt_map_key_at(const dt_map *m, size_t index, const char **out)
{
    /* TODO: the key at this position in insertion order, or DT_ERR_RANGE past
       the end. */
    (void)m;
    (void)index;
    (void)out;
    return DT_ERR_RANGE;
}

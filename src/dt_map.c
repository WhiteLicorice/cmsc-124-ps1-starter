/*
 * dt_map.c -- associative arrays (Unit 5, Section E).
 *
 * The difference from an array is one sentence: an array does not store its
 * indices, and this does store its keys. That is why an array position costs
 * one subtraction and a key costs a hash plus a comparison.
 *
 * Two requirements shape the implementation.
 *
 * Hashing. Turn a key into a bucket, then compare keys inside that bucket,
 * because two keys can land in the same one. Chaining each bucket as a linked
 * list is the shortest correct answer. FNV-1a is four lines and good enough:
 * start at 14695981039346656037u, and for each byte, xor it in and multiply by
 * 1099511628211u.
 *
 * Insertion order. Printing a map has to be deterministic or nobody can write
 * an expected-output file, and bucket order is an artifact of the hash. So keep
 * a separate list of keys in the order they were first inserted, which is what
 * dt_map_key_at reads. Putting an existing key again replaces its value and
 * leaves its position alone; removing a key takes it out of that order, and
 * putting it back later appends it at the end.
 */

#include "dt.h"

#include <stdlib.h>
#include <string.h>

struct dt_map {
    int placeholder; /* TODO: replace with your buckets and your key order. */
};

dt_map *dt_map_new(void)
{
    /* TODO: an empty map. Not NULL, which means allocation failure. */
    return NULL;
}

void dt_map_free(dt_map *m)
{
    /* TODO: free every chain node, every copied key, and the map. The values
       belong to the environment; leave them alone. */
    (void)m;
}

size_t dt_map_len(const dt_map *m)
{
    (void)m;
    return 0;
}

dt_status dt_map_put(dt_map *m, const char *key, dt_value v)
{
    /* TODO: replace on an existing key, insert otherwise. Copy the key; the
       caller's buffer does not outlive the command. */
    (void)m;
    (void)key;
    (void)v;
    return DT_ERR_KEY;
}

dt_status dt_map_get(const dt_map *m, const char *key, dt_value *out)
{
    /* TODO: DT_ERR_KEY when absent. A missing key is not nil. */
    (void)m;
    (void)key;
    (void)out;
    return DT_ERR_KEY;
}

dt_status dt_map_remove(dt_map *m, const char *key)
{
    /* TODO: unlink from the bucket chain and from the insertion order, free
       the copied key, and report DT_ERR_KEY when it was not there. */
    (void)m;
    (void)key;
    return DT_ERR_KEY;
}

dt_status dt_map_key_at(const dt_map *m, size_t index, const char **out)
{
    /* TODO: the index-th key in insertion order, DT_ERR_RANGE past the end. */
    (void)m;
    (void)index;
    (void)out;
    return DT_ERR_RANGE;
}

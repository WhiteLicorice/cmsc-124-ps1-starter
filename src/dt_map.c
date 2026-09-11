/*
 * dt_map.c -- associative arrays (Unit 5, Section E).
 *
 * The selector difference this assignment exposes fits in one sentence. An
 * array does not store its indices. This map stores its keys. An array position costs one
 * subtraction. A key costs a hash followed by comparisons in one bucket. An
 * empty bucket needs no comparison.
 *
 * Two requirements drive the code.
 *
 * Hashing. Turn the key into a bucket number, then compare keys inside that
 * bucket, because two keys can land in the same bucket. Making each bucket a
 * linked list is the shortest correct answer. FNV-1a is four lines. Start the
 * unsigned accumulator at 14695981039346656037ULL. For each unsigned byte,
 * exclusive-or the byte into it and multiply by 1099511628211ULL.
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

/*
 * dt_map_new: build an empty map. NULL here means the allocation failed. An
 * empty map is a real object, not NULL.
 */
dt_map *dt_map_new(void)
{
    /* TODO: an empty map. Not NULL, which means the allocation failed.
       dt_map_new()  -> a map whose dt_map_len is 0
       cases/normal/map_basics.case */
    return NULL;
}

/*
 * dt_map_free: release every list node, every copied key, and the map itself.
 * Accepts NULL and does nothing then. The values belong to the environment and
 * are not freed.
 */
void dt_map_free(dt_map *m)
{
    /* TODO: free every list node, every copied key, and the map itself. The
       values belong to the environment, so leave them alone.
       a map holding a string value  -> the nodes and keys go, the string stays
       dt_map_free(NULL)             -> returns, having done nothing
       cases/cleanup/map_churn.case */
    (void)m;
}

/*
 * dt_map_len: how many keys the map holds. This reads a field, so it takes the
 * same time no matter how many keys there are.
 */
size_t dt_map_len(const dt_map *m)
{
    /* TODO: how many keys are bound right now. Putting an existing key again
       replaces its value and does not change this count.
       after put alpha, beta, gamma:  dt_map_len(m) -> 3
       after put beta again:          dt_map_len(m) -> 3, still
       after del alpha:               dt_map_len(m) -> 2
       cases/normal/map_basics.case */
    (void)m;
    return 0;
}

/*
 * dt_map_put: bind v to `key`. When the key is already there, its value is
 * replaced and its position in the insertion order stays. Otherwise the key is
 * added at the end. The key is copied, because the caller's buffer does not
 * outlive the command. Returns DT_ERR_CAPACITY when an allocation fails.
 */
dt_status dt_map_put(dt_map *m, const char *key, dt_value v)
{
    /* TODO: replace the value when the key is already there, and add it
       otherwise. Copy the key. The caller's buffer does not last past the
       command.
       Work in four steps: hash the key, find its bucket, search that bucket's
       chain, then either overwrite the value in place or append a new entry to
       both the chain and the insertion list.
       put "beta" -> 2 on an empty map    -> DT_OK, "beta" is last in order
       put "beta" -> 22 on that map       -> DT_OK, same position, new value
       an allocation failure              -> DT_ERR_CAPACITY, map unchanged
       cases/normal/map_basics.case */
    (void)m;
    (void)key;
    (void)v;
    return DT_ERR_CAPACITY;
}

/*
 * dt_map_get: write the value bound to `key` to *out. Returns DT_ERR_KEY when
 * the key is absent, and leaves *out alone then. A missing key is not the nil
 * value.
 */
dt_status dt_map_get(const dt_map *m, const char *key, dt_value *out)
{
    /* TODO: return DT_ERR_KEY when the key is absent. A missing key is not
       nil.
       after put "beta" -> 22:
         dt_map_get(m, "beta", &out)   -> DT_OK, *out is the integer 22
         dt_map_get(m, "ghost", &out)  -> DT_ERR_KEY, *out untouched
       cases/normal/map_basics.case, cases/boundary/map_missing_key.case */
    (void)m;
    (void)key;
    (void)out;
    return DT_ERR_KEY;
}

/*
 * dt_map_remove: unlink `key` from its bucket and from the insertion order, and
 * free the copied key. Returns DT_ERR_KEY when the key was not there.
 */
dt_status dt_map_remove(dt_map *m, const char *key)
{
    /* TODO: unlink the entry from its bucket and from the insertion order,
       free the copied key, and return DT_ERR_KEY when it was not there.
       a map holding alpha, beta, gamma:
         dt_map_remove(m, "alpha")  -> DT_OK, order is now beta, gamma
         dt_map_remove(m, "ghost")  -> DT_ERR_KEY, nothing changes
       putting "alpha" back afterwards appends it at the end, not at the front
       cases/normal/map_basics.case, cases/boundary/map_remove_missing_key.case */
    (void)m;
    (void)key;
    return DT_ERR_KEY;
}

/*
 * dt_map_key_at: write the key at position `index` in insertion order to *out.
 * Returns DT_ERR_RANGE when the index is past the end, and leaves *out alone
 * then.
 */
dt_status dt_map_key_at(const dt_map *m, size_t index, const char **out)
{
    /* TODO: the key at this position in insertion order, or DT_ERR_RANGE past
       the end. The printer walks this, so it decides the order a map prints in.
       a map holding alpha, beta, gamma:
         dt_map_key_at(m, 0, &out)  -> DT_OK, *out = "alpha"
         dt_map_key_at(m, 3, &out)  -> DT_ERR_RANGE, *out untouched
       cases/normal/map_basics.case */
    (void)m;
    (void)index;
    (void)out;
    return DT_ERR_RANGE;
}

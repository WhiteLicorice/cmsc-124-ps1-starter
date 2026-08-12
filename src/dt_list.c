/*
 * dt_list.c -- lists (Unit 5, Section H).
 *
 * A cell holds a value and a pointer to the rest of the list. CAR reads the
 * value, CDR reads the rest, and CONS puts a new cell in front. That is the
 * whole data type.
 *
 * The part to study is what CONS does not do. It does not copy the tail. It
 * points at it. After these commands:
 *
 *     list nil e
 *     list cons b 2 e
 *     list cons a 1 b
 *
 * the list a is (1 2) and the list b is (2). The cell holding 2 is one cell that
 * both lists reach. So cons takes constant time and costs one cell however long
 * the tail is, which is why a linked list is worth having.
 *
 * It is also why dt_list_free frees one cell and never follows the tail.
 * Following it would free cells that b still uses.
 *
 * The empty list is a null pointer, so it costs nothing to represent.
 */

#include "dt.h"

#include <stdlib.h>

struct dt_list {
    dt_value head;
    dt_list *tail;
};

dt_list *dt_list_nil(void)
{
    /* TODO: the empty list. Read the note above before you allocate anything. */
    return NULL;
}

dt_list *dt_list_cons(dt_value head, dt_list *tail)
{
    /* TODO: one new cell pointing at the tail you were given. Do not copy the
       tail. */
    (void)head;
    (void)tail;
    return NULL;
}

void dt_list_free(dt_list *l)
{
    /* TODO: free this one cell. Not its tail. Accept NULL without crashing. */
    (void)l;
}

size_t dt_list_len(const dt_list *l)
{
    /* TODO: walk to the end. This costs one step per cell, which is the price
       of the representation. */
    (void)l;
    return 0;
}

dt_status dt_list_car(const dt_list *l, dt_value *out)
{
    /* TODO: DT_ERR_EMPTY on the empty list. The empty list has no first
       element, and nil is a different answer from no answer. */
    (void)l;
    (void)out;
    return DT_ERR_EMPTY;
}

dt_status dt_list_cdr(const dt_list *l, dt_list **out)
{
    /* TODO: DT_ERR_EMPTY on the empty list, and the shared tail otherwise. The
       cdr of a one-element list is the empty list, which is not an error. */
    (void)l;
    (void)out;
    return DT_ERR_EMPTY;
}

/*
 * dt_list.c -- lists (Unit 5, Section H).
 *
 * Lisp's list is two things: a cell holding a value and a pointer to the rest.
 * CAR reads the value, CDR reads the rest, CONS makes a new cell in front of an
 * existing list. That is the whole data type.
 *
 * The part worth sitting with is what CONS does not do. It does not copy the
 * tail. It points at it. So after
 *
 *     list nil e
 *     list cons b 2 e
 *     list cons a 1 b
 *
 * the list a is (1 2) and the list b is (2), and the cell holding 2 is one cell
 * that both of them reach. Consing is O(1) and costs one cell no matter how
 * long the tail is, which is what makes a linked list worth having and also why
 * dt_list_free frees one cell and never follows the tail. Following it would
 * free memory that b still uses.
 *
 * The empty list is a null pointer, so it costs nothing and needs no allocation.
 */

#include "dt.h"

#include <stdlib.h>

struct dt_list {
    dt_value head;
    dt_list *tail;
};

dt_list *dt_list_nil(void)
{
    /* TODO: the empty list. Read the comment above before you allocate here. */
    return NULL;
}

dt_list *dt_list_cons(dt_value head, dt_list *tail)
{
    /* TODO: one new cell pointing at the existing tail. Do not copy the tail. */
    (void)head;
    (void)tail;
    return NULL;
}

void dt_list_free(dt_list *l)
{
    /* TODO: free this one cell. Not its tail. Tolerate NULL. */
    (void)l;
}

size_t dt_list_len(const dt_list *l)
{
    /* TODO: walk to the end. This is O(n), which is the price of the shape. */
    (void)l;
    return 0;
}

dt_status dt_list_car(const dt_list *l, dt_value *out)
{
    /* TODO: DT_ERR_EMPTY on the empty list. The empty list has no first
       element, and nil is not the right answer for one that does not exist. */
    (void)l;
    (void)out;
    return DT_ERR_EMPTY;
}

dt_status dt_list_cdr(const dt_list *l, dt_list **out)
{
    /* TODO: DT_ERR_EMPTY on the empty list, otherwise the shared tail.
       The cdr of a one-element list is the empty list, not an error. */
    (void)l;
    (void)out;
    return DT_ERR_EMPTY;
}

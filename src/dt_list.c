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

/*
 * dt_list_nil: the empty list. It is a null pointer, so it costs no memory and
 * needs no allocation.
 */
dt_list *dt_list_nil(void)
{
    /* TODO: the empty list. Read the note above before you allocate anything.
       dt_list_nil()             -> the empty list, which prints as ()
       dt_list_len(dt_list_nil()) -> 0
       cases/normal/list_basics.case */
    return NULL;
}

/*
 * dt_list_cons: build a new cell holding `head` and pointing at `tail`. The
 * tail is shared, never copied. Returns NULL when an allocation fails.
 */
dt_list *dt_list_cons(dt_value head, dt_list *tail)
{
    /* TODO: one new cell pointing at the tail you were given. Do not copy the
       tail.
       after `list nil e`, `list cons c 3 e`, `list cons b 2 c`, `list cons a 1 b`:
         a is (1 2 3) and b is (2 3), sharing the same cells for 2 and 3
       an allocation failure -> NULL
       cases/normal/list_basics.case, cases/cleanup/shared_list_tail.case */
    (void)head;
    (void)tail;
    return NULL;
}

/*
 * dt_list_free: release this one cell, never its tail. Other lists may still
 * reach the tail, so following it would free cells they still use. Accepts
 * NULL and does nothing then.
 */
void dt_list_free(dt_list *l)
{
    /* TODO: free this one cell. Not its tail. Accept NULL without crashing.
       freeing a's first cell  -> b still reaches the cells holding 2 and 3
       following the tail here is a double free the sanitizer reports in CI
       cases/cleanup/shared_list_tail.case */
    (void)l;
}

/*
 * dt_list_len: how many cells are in the list. This walks cell to cell, so it
 * costs one step per cell. That is the price of the representation.
 */
size_t dt_list_len(const dt_list *l)
{
    /* TODO: walk to the end. This costs one step per cell, which is the price
       of the representation.
       for a = (1 2 3):  dt_list_len(a) -> 3
       for the empty list: dt_list_len(NULL) -> 0
       cases/normal/list_basics.case */
    (void)l;
    return 0;
}

/*
 * dt_list_car: write the first cell's value to *out. Returns DT_ERR_EMPTY on
 * the empty list, and leaves *out alone then. The empty list has no first
 * element, and nil is a different answer from no answer.
 */
dt_status dt_list_car(const dt_list *l, dt_value *out)
{
    /* TODO: DT_ERR_EMPTY on the empty list. The empty list has no first
       element, and nil is a different answer from no answer.
       for a = (1 2 3):     dt_list_car(a, &out)    -> DT_OK, *out is 1
       for the empty list:  dt_list_car(NULL, &out) -> DT_ERR_EMPTY, *out untouched
       cases/normal/list_basics.case, cases/boundary/list_car_empty.case */
    (void)l;
    (void)out;
    return DT_ERR_EMPTY;
}

/*
 * dt_list_cdr: write the tail of the list to *out. Returns DT_ERR_EMPTY on the
 * empty list. The cdr of a one-element list is the empty list, which is a real
 * answer, not an error.
 */
dt_status dt_list_cdr(const dt_list *l, dt_list **out)
{
    /* TODO: DT_ERR_EMPTY on the empty list, and the shared tail otherwise. The
       cdr of a one-element list is the empty list, which is not an error.
       for a = (1 2 3):     dt_list_cdr(a, &out)    -> DT_OK, *out is b, the same
                                                       cells, never a copy
       for the empty list:  dt_list_cdr(NULL, &out) -> DT_ERR_EMPTY, *out untouched
       cases/normal/list_basics.case, cases/boundary/list_cdr_empty.case */
    (void)l;
    (void)out;
    return DT_ERR_EMPTY;
}

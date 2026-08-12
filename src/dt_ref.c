/*
 * dt_ref.c -- owned references (Unit 5, Section J).
 *
 * Three failures live here, and C reports none of them.
 *
 * A dangling reference. The pointee is freed and the pointer still holds its
 * address. Reading through it reads memory the allocator has taken back. It
 * often works, which is the problem: it works until the allocator hands that
 * block to something else, and then it corrupts whatever moved in.
 *
 * A double release. The same block handed back twice. Most allocators treat
 * this as corruption of their own bookkeeping rather than as a polite mistake.
 *
 * A lost pointee. The reference goes out of scope with the pointee still
 * allocated, and now nothing in the program can reach that block to free it.
 * Notice this is the exact opposite failure from a dangling reference: there
 * you have a route to memory you no longer own, here you own memory you have no
 * route to.
 *
 * A released flag turns the first two into DT_ERR_RELEASED, and the driver's
 * exit-time sweep turns the third into DT_ERR_LEAK. That flag is what a
 * reference-counted or garbage-collected language buys you, and this is
 * roughly what it costs.
 *
 * Ownership stops at the cell. dt_ref_new copies the value into a cell it owns;
 * if that value points at a string, the string still belongs to the
 * environment, so releasing must not free it.
 */

#include "dt.h"

#include <stdlib.h>

struct dt_ref {
    dt_value *cell;
    bool      released;
};

dt_ref *dt_ref_new(dt_value v)
{
    /* TODO: allocate the handle and a cell, copy v into the cell, and start
       out not released. */
    (void)v;
    return NULL;
}

dt_status dt_ref_borrow(const dt_ref *p, dt_value *out)
{
    /* TODO: DT_ERR_RELEASED after release, otherwise a copy of the cell.
       Check the flag before touching the cell pointer, not after. */
    (void)p;
    (void)out;
    return DT_ERR_RELEASED;
}

dt_status dt_ref_release(dt_ref *p)
{
    /* TODO: DT_ERR_RELEASED if already released. Otherwise free the cell, set
       the pointer to NULL, and set the flag. Setting the pointer to NULL after
       freeing is what keeps a later bug into a clean fault instead of a read of
       freed memory. */
    (void)p;
    return DT_ERR_RELEASED;
}

bool dt_ref_is_released(const dt_ref *p)
{
    (void)p;
    return true;
}

void dt_ref_destroy(dt_ref *p)
{
    /* TODO: free the cell if it is still live, then the handle. The driver
       calls this at exit, after it has already reported any leak, so this
       function reports nothing. */
    (void)p;
}

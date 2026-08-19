/*
 * dt_ref.c -- owned references (Unit 5, Section J).
 *
 * Three failures live here, and C reports none of them.
 *
 * A dangling reference. The memory is freed and the pointer still holds its
 * address. Reading through it reads memory the allocator has taken back. It
 * often appears to work, which is the danger. It keeps working until the
 * allocator gives that memory to something else, and then the read returns
 * another variable's data.
 *
 * A double release. The same memory is freed twice. Most allocators treat this
 * as damage to their own records, so the crash usually happens later, during
 * some unrelated allocation.
 *
 * A lost pointee. The reference goes away while the memory is still
 * allocated, so nothing in the program can reach that memory to free it. This
 * is the opposite of a dangling reference. There you can reach memory you no
 * longer own. Here you own memory you cannot reach.
 *
 * A released flag turns the first two into DT_ERR_RELEASED. The sweep the driver
 * runs at exit turns the third into DT_ERR_LEAK. That flag, plus the check in
 * front of every read, is close to what a reference-counted or garbage
 * collected language does for you, and close to what it costs.
 *
 * Ownership stops at the cell. dt_ref_new copies the value into a cell that
 * the reference owns. If the value points at a string, the string still
 * belongs to the environment, so releasing must not free the string.
 */

#include "dt.h"

#include <stdlib.h>

struct dt_ref {
    dt_value *cell;
    bool      released;
};

/*
 * dt_ref_new: build a reference to a copy of v. The reference owns the copy,
 * called the cell. Returns NULL when an allocation fails.
 */
dt_ref *dt_ref_new(dt_value v)
{
    /* TODO: allocate the handle and a cell, copy v into the cell, and start
       out not released.
       dt_ref_new(dt_value_int(42))  -> a reference that prints as ref(42)
       an allocation failure          -> NULL
       cases/ownership/ref_released.case */
    (void)v;
    return NULL;
}

/*
 * dt_ref_borrow: write a copy of the cell's value to *out. Returns
 * DT_ERR_RELEASED after the reference has been released, and leaves *out alone
 * then. Check the flag before touching the cell pointer.
 */
dt_status dt_ref_borrow(const dt_ref *p, dt_value *out)
{
    /* TODO: DT_ERR_RELEASED after release, and a copy of the cell otherwise.
       Check the flag before you touch the cell pointer.
       a live reference to 42:  dt_ref_borrow(p, &out) -> DT_OK, *out is 42
       after dt_ref_release(p): dt_ref_borrow(p, &out) -> DT_ERR_RELEASED,
                                                          *out untouched
       cases/ownership/ref_released.case,
       cases/post-release/borrow_after_release.case */
    (void)p;
    (void)out;
    return DT_ERR_RELEASED;
}

/*
 * dt_ref_release: free the cell and mark the reference released. Returns
 * DT_ERR_RELEASED when it was already released, and changes nothing then.
 */
dt_status dt_ref_release(dt_ref *p)
{
    /* TODO: DT_ERR_RELEASED when it is already released. Otherwise free the
       cell, set the pointer to NULL, and set the flag. Setting the pointer to
       NULL after freeing turns a later mistake into a clean crash rather than a
       silent read of freed memory.
       first call on a live reference   -> DT_OK, the cell is freed
       second call on the same one      -> DT_ERR_RELEASED, and nothing is freed
                                           twice
       a reference holding a string     -> the cell goes, the string stays, since
                                           the environment owns it
       cases/ownership/ref_double_release.case,
       cases/ownership/ref_aliases_string.case */
    (void)p;
    return DT_ERR_RELEASED;
}

/*
 * dt_ref_is_released: true when the reference has been released. This is how
 * the driver's leak sweep tells a live reference from a released one.
 */
bool dt_ref_is_released(const dt_ref *p)
{
    /* TODO: read the flag dt_ref_release sets. The driver's leak sweep calls
       this on every reference at exit, so a hard-coded true hides every leak and
       a hard-coded false reports leaks that were properly released.
       a live reference        -> false, and the sweep reports DT_ERR_LEAK for it
       after dt_ref_release(p) -> true, and the sweep leaves it alone
       cases/ownership/ref_never_released.case, cases/ownership/ref_released.case */
    (void)p;
    return true;
}

/*
 * dt_ref_destroy: free the cell if it is still there, then the handle. The
 * driver calls this at exit, after it has already reported any leak, so this
 * function reports nothing. Accepts NULL and does nothing then.
 */
void dt_ref_destroy(dt_ref *p)
{
    /* TODO: free the cell if it is still there, then the handle. The driver
       calls this at exit, after it has already reported any leak, so this
       function reports nothing.
       a released reference  -> only the handle is left to free
       a live reference      -> the cell and the handle both go, quietly
       dt_ref_destroy(NULL)  -> returns, having done nothing */
    (void)p;
}

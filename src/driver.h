/*
 * driver.h -- private declarations shared by the given driver files.
 * Not part of the assignment. Nothing you write includes this.
 */

#ifndef DT_DRIVER_H
#define DT_DRIVER_H

#include "dt.h"

void dt_print_value(dt_value v);
void dt_print_line(dt_value v);

/* Runs one case file. Returns 0, 65, or 70 per the course run contract. */
int dt_driver_run(const char *path);

#endif /* DT_DRIVER_H */

/*
 * main.c -- entry point. Given to you, complete.
 *
 * Exit codes follow the course run contract, the same one your interpreter
 * uses in the laboratory: 0 ran, 65 rejected before running, 70 died running.
 */

#include "driver.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: run <case-file>\n");
        return 65;
    }
    return dt_driver_run(argv[1]);
}

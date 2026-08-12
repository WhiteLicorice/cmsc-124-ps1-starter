/*
 * main.c -- entry point. Written for you, complete.
 *
 * The exit codes follow the course run contract, the same one your interpreter
 * uses in the laboratory. 0 means it ran, 65 means the file was rejected before
 * anything ran, and 70 means it failed while running.
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

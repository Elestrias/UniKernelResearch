#ifndef _UTILS_H_
#define _UTILS_H_

#include "utils.h"
#include <time.h>

double measureExecutionTime(generic_func_t func, void *args) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    func(args);
    clock_gettime(CLOCK_MONOTONIC, &end);

    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

#endif
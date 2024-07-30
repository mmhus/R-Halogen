// Copyright 2024 10xEngineers

#ifndef COMMON_UTILITIES_H
#define COMMON_UTILITIES_H

#include <stdio.h>
#include <stdint.h>

#define INT8 1
#define INT16 2
#define INT32 3
#define INT64 4
#define UINT8 5
#define UINT16 6
#define UINT32 7
#define UINT64 8

void print_results(void *results, int size, int type);

#endif  // COMMON_UTILITIES_H

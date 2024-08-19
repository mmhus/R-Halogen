// Copyright 2024 10xEngineers

#include "common_utilities.h"

/**
 * @brief Function to print results of different types
 * 
 * This function prints the results from an array of integers of various types
 * (int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t)
 * with the specified number of elements ('size').
 * 
 * @param results Pointer to the array containing the results to be printed
 * @param size Number of elements in the array
 * @param type Type of elements in the results array defined by macros (INT8, UINT8, etc.)
 */
void print_results(void *results, int size, int type) {
    int i;
    switch (type) {
        case INT8:  // int8_t
            for (i = 0; i < size; i++) {
                printf("%d ", ((int8_t *)results)[i]);
            }
            break;
        case INT16:  // int16_t
            for (i = 0; i < size; i++) {
                printf("%d ", ((int16_t *)results)[i]);
            }
            break;
        case INT32:  // int32_t
            for (i = 0; i < size; i++) {
                printf("%d ", ((int32_t *)results)[i]);
            }
            break;
        case INT64:  // int64_t
            for (i = 0; i < size; i++) {
                printf("%lld ", ((int64_t *)results)[i]);
            }
            break;
        case UINT8:  // uint8_t
            for (i = 0; i < size; i++) {
                printf("%u ", ((uint8_t *)results)[i]);
            }
            break;
        case UINT16:  // uint16_t
            for (i = 0; i < size; i++) {
                printf("%u ", ((uint16_t *)results)[i]);
            }
            break;
        case UINT32:  // uint32_t
            for (i = 0; i < size; i++) {
                printf("%u ", ((uint32_t *)results)[i]);
            }
            break;
        case UINT64:  // uint64_t
            for (i = 0; i < size; i++) {
                printf("%llu ", ((uint64_t *)results)[i]);
            }
            break;
        default:
            printf("Unsupported type\n");
            return;
        }
    printf("\n");
}

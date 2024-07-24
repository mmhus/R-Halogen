// Copyright 2024 10xEngineers

#include "../common/print.h"

/**
 * @brief Function to print results of different types
 * 
 * This function prints the results from an array of integers of various types
 * (int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t)
 * with the specified number of elements ('size').
 * 
 * @param results Pointer to the array containing the results to be printed
 * @param size Number of elements in the array
 * @param type Type of elements in the results array i.e "int8_t", "uint8_t"
 */
void print_results(void *results, int size, const char *type) {
    int i;
    if (strcmp(type, "int8_t") == 0) {  // int8_t
        for (i = 0; i < size; i++) {
            printf("%d ", ((int8_t *)results)[i]);
        }
    } else if (strcmp(type, "int16_t") == 0) {  // int16_t
        for (i = 0; i < size; i++) {
            printf("%d ", ((int16_t *)results)[i]);
        }
    } else if (strcmp(type, "int32_t") == 0) {  // int32_t
        for (i = 0; i < size; i++) {
            printf("%d ", ((int32_t *)results)[i]);
        }
    } else if (strcmp(type, "int64_t") == 0) {  // int64_t
        for (i = 0; i < size; i++) {
            printf("%lld ", ((int64_t *)results)[i]);
        }
    } else if (strcmp(type, "uint8_t") == 0) {  // uint8_t
        for (i = 0; i < size; i++) {
            printf("%u ", ((uint8_t *)results)[i]);
        }
    } else if (strcmp(type, "uint16_t") == 0) {  // uint16_t
        for (i = 0; i < size; i++) {
            printf("%u ", ((uint16_t *)results)[i]);
        }
    } else if (strcmp(type, "uint32_t") == 0) {  // uint32_t
        for (i = 0; i < size; i++) {
            printf("%u ", ((uint32_t *)results)[i]);
        }
    } else if (strcmp(type, "uint64_t") == 0) {  // uint64_t
        for (i = 0; i < size; i++) {
            printf("%llu ", ((uint64_t *)results)[i]);
        }
    } else {
        printf("Unsupported type\n");
        return;
    }
    printf("\n");
}

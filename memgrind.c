#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

#define TEST_ITERATIONS 120

void basicAllocFreeTest() {
    printf("Running basic alloc/free test...\n");
    
    int *ptr = (int *) malloc(sizeof(int) * 10);
    if(ptr == NULL) {
        printf("Error: Couldn't allocate memory!\n");
        return;
    }
    
    free(ptr);
    printf("Basic alloc/free test completed successfully.\n");
}

void oversizeAllocTest() {
    printf("Running oversize alloc test...\n");
    
    char *ptr = (char *) malloc(4500);
    if(ptr != NULL) {
        printf("Error: Memory shouldn't have been allocated!\n");
        free(ptr);
    } else {
        printf("Oversize alloc test completed successfully.\n");
    }
}

void doubleFreeTest() {
    printf("Running double free test...\n");
    
    char *ptr = (char *) malloc(100);
    if(ptr == NULL) {
        printf("Error: Couldn't allocate memory!\n");
        return;
    }
    
    free(ptr);
    free(ptr);  // This should throw an error about freeing a non-allocated block
    printf("Double free test completed. Check for errors.\n");
}

void randomAllocFreeTest() {
    printf("Running random alloc/free test...\n");

    char *ptrs[TEST_ITERATIONS] = {NULL};  // Initialize all pointers to NULL

    for(int i = 0; i < TEST_ITERATIONS; i++) {
        int choice = rand() % 2;  // Either 0 or 1

        if(choice) {
            // Try to allocate if not already allocated
            if(!ptrs[i]) {
                ptrs[i] = (char *) malloc(1);
                if(!ptrs[i]) {
                    printf("Error: Couldn't allocate memory!\n");
                }
            }
        } else {
            // Try to free if it's allocated
            if(ptrs[i]) {
                free(ptrs[i]);
                ptrs[i] = NULL;
            }
        }
    }

    // Clean up any remaining allocations
    for(int i = 0; i < TEST_ITERATIONS; i++) {
        if(ptrs[i]) {
            free(ptrs[i]);
            ptrs[i] = NULL;
        }
    }

    printf("Random alloc/free test completed.\n");
}


void fillAndFreeTest() {
    printf("Running fill and free test...\n");

    char *ptrs[TEST_ITERATIONS];
    for(int i = 0; i < TEST_ITERATIONS; i++) {
        ptrs[i] = (char *) malloc(1);
        if(!ptrs[i]) {
            printf("Error: Couldn't allocate memory!\n");
            break;
        }
    }

    // Free all pointers
    for(int i = 0; i < TEST_ITERATIONS; i++) {
        if(ptrs[i]) {
            free(ptrs[i]);
            ptrs[i] = NULL;
        }
    }

    printf("Fill and free test completed.\n");
}

int main() {
    srand(time(NULL));  // Seed the random number generator

    basicAllocFreeTest();
    oversizeAllocTest();
    doubleFreeTest();
    randomAllocFreeTest();
    fillAndFreeTest();

    // More test cases can be added as required
    return 0;
}
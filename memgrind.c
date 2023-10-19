#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

#define TEST_ITERATIONS 120

//Allocating and immedeatly freeing 1 byte of memory 120 times
void allocFreeTest() {
    printf("Running basic alloc/free test...\n");
    
    char *ptr = (char *) malloc(sizeof(char));
    if(ptr == NULL) {
        printf("Error: Couldn't allocate memory!\n");
        return;
    }
    
    free(ptr);
    printf("Success! Basic alloc/free test completed successfully!\n");
    return;
}

//fill and free test declares and defines an array of 120 bytes 
//malloc will be called 120 times to get blocks of size 1 bytes
//once objects are all allocated, all objects wll be freed 
void fillAndFreeTest() {
    printf("Running fill and free test...\n");

    char *ptrs[TEST_ITERATIONS];
    for(int i = 0; i < TEST_ITERATIONS; i++) {
        ptrs[i] = (char *) malloc(1);
        if(!ptrs[i]) {
            printf("Error: Couldn't allocate memory!\n");
            return;
        }
    }

    // Free all pointers
    for(int i = 0; i < TEST_ITERATIONS; i++) {
        if(ptrs[i]) {
            free(ptrs[i]);
            ptrs[i] = NULL;
        }
    }

    printf("Success! Fill and free test completed.\n");
    return;
}

// randomTest will declare an array of 120 pointers
// the function will make random choices between allocating a 1- byte
// object and adding a pointer to the array and deallocating a previously
// allocated object until allocation occurs 120 times.
void randomTest() {
    printf("Running random alloc/free test...\n");

    char *ptrs[TEST_ITERATIONS] = {NULL};  // Initialize all pointers to NULL
    for(int i = 0; i < TEST_ITERATIONS; i++) {
        int random = rand() % 2;  // Either 0 or 1

        if(random) {
            // Try to allocate if not already allocated
            if(!ptrs[i]) {
                ptrs[i] = (char *) malloc(1);
                if(!ptrs[i]) {   // if block is null after allcoation, print error message
                    printf("Error: Couldn't allocate memory!\n");
                }
            }
        } else {
            int j=0;
            // Try to free if it's allocated
            while(ptrs[j]){
            if(ptrs[i]) {
                free(ptrs[i]);
                ptrs[i] = NULL;
                break;
            }
            j++;
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

    printf("Success! Random alloc/free test completed.\n");
    return;
}


//allocate two large blocks of memory, free then allocate all memory and free
void largeAllocAndFree(){

    
    char *a = malloc(2036);
    if (a == NULL){
        printf("Error: malloc failed!");
        return;
    }

    char *b = malloc(2036);
    if (b == NULL){
        printf("Error: malloc failed !");
        return;
    }

    free(a);
    free(b);

    char *c = malloc(4088);
    if (c == NULL){
        printf("Error: malloc failed! ");
    }

    free(c);

    printf("Success! Large Alloc and Free test completed succesfully!");
    return;

    
}


void arrayWriteAlloc(){
    int *nums = malloc(sizeof(int) * 20);

    if (nums == NULL){
        printf("Error: Malloc has failed\n");
        return;
    }

    for (int i = 0; i < 20; i++){
        nums[i] = i;
    }

    for (int i = 0; i < 20; i++){
        
        if (nums[i] != i){
            printf("Error: objects are not properly written\n");
            return;
        }
        
    }

    free(nums);
    printf("Success! Array object was succesfully allocated and written to!");
}



int main() {
    //run basicAllocFreeTest() 50 times in a row 
    double avgTime = 0.0;

    for (int i = 0; i < 50; i++){
        //initialize clock 
        clock_t time; 
        time = clock();

        allocFreeTest();

        //calculate time taken to execute task 
        time = clock() - time ;
        
        double total_time = ((double) time) / CLOCKS_PER_SEC;
        avgTime += total_time;
        printf("allocFreeTest() executed in %f seconds\n", total_time);


    }


    printf("Average execution for allocFreeTest() is %f seconds\n\n", avgTime/50);
    

    avgTime = 0.0;
    for (int i = 0; i < 50; i++){

        clock_t time; 
        time = clock();

        randomTest();

        time = clock() - time ;
        
        double total_time = ((double) time) / CLOCKS_PER_SEC;
        avgTime += total_time;
        printf("randomTest() executed in %f seconds\n", total_time);

    }
    printf("Average execution for randomTest() is %f seconds\n\n", avgTime/50);

    avgTime = 0.0;
    for (int i = 0; i < 50; i++){

        clock_t time; 
        time = clock();

        fillAndFreeTest();

        time = clock() - time ;
        
        double total_time = ((double) time) / CLOCKS_PER_SEC;
        avgTime += total_time;
        printf("fillAndFreeTest() executed in %f seconds\n", total_time);

    }
    printf("Average execution for fillAndFreeTest() is %f seconds\n\n", avgTime/50);
    
    avgTime = 0.0;
    for (int i = 0; i < 50; i++){

        clock_t time; 
        time = clock();

        largeAllocAndFree();

        time = clock() - time ;
        
        double total_time = ((double) time) / CLOCKS_PER_SEC;
        avgTime += total_time;
        printf("largeAllocAndFree() executed in %f seconds\n", total_time);

    }
    printf("Average execution for largeAllocAndFree() is %f seconds\n\n", avgTime/50);

    avgTime = 0.0;
    for (int i = 0; i < 50; i++){

        clock_t time; 
        time = clock();

        arrayWriteAlloc();

        time = clock() - time ;
        
        double total_time = ((double) time) / CLOCKS_PER_SEC;
        avgTime += total_time;
        printf("arrayWriteAlloc() executed in %f seconds\n", total_time);

    }
    printf("Average execution for arrayWriteAlloc() is %f seconds\n\n", avgTime/50);

    return 0;
}
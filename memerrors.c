/***************************************************************
*  This program will contain functions that will incorrectly   *
*  use malloc() and free(). The purpose of these test cases    *
*  is to assure malloc() and free() are catching common errors *
***************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include "mymalloc.h"

//function will call free twice
void doubleFreeTest() {
    
    printf("Running doubleFreeTest() ...\n");
    printf("Attempting to double free a pointer");
    
    char *ptr = (char *) malloc(100);
    
    if(ptr == NULL) {
        printf("Error: Couldn't allocate memory!\n");
        return;
    }
    
    free(ptr);
    free(ptr);  // This should throw an error 
    
    printf("Success! Double free test completed.\n\n");
    
    return;
}

//this function will try to free a pointers which are invalid
void invalidPtrFree(){
    
    char *y = malloc(sizeof(char) * 60);
   
    //attempt to free pointer that is not at beginning of payload
    printf("Running invalidPtrFree() ...\n");
    printf("Attempting to free a pointer that is not at the beginning of a payload. \n");
    
    free(y + 1);

    //attempt to free a local variable
    int n = 10;
   
    printf("Attempting to free a local variable. \n");
    
    free(&n);


    free(y);
    
    printf("\n");
    
    return;
    
}


//this function will try to call malloc with a non-positive size
void invalidSize(){
    printf("Running invalidSize() ...\n");
    printf("Attempting to call malloc with a size of 0\n");
    
    int *zeroMalloc = malloc(0);
    
    if (zeroMalloc == NULL){
        printf("Malloc detected error succesfully\n\n");
    } 
    
    else{
        printf("Malloc did not detect the error\n");
        return;
    }


    printf("Attempting to call malloc with a negative size\n");
    
    int *negativeMalloc = malloc(-5);
    
    if (negativeMalloc == NULL){
        printf("Malloc detected error succesfully\n\n");
    }

    else{
        printf("Malloc did not detect the error\n");
        return;
    }


    printf("\n");
    
    return;
}

//this function will attempt to call malloc when there is no free space
void oversizeTest() {
    printf("Running oversizeTest() ...\n");
    printf("Running oversize alloc test...\n");
    
    char *ptr = (char *) malloc(4777);
   
    if(ptr != NULL) {
        printf("Error: Memory shouldn't have been allocated!\n");
        free(ptr);
        return;
    }
    else {
        
        printf("Malloc detected error succesfully\n");
        return;
    }
}

int main(int argv, char **argc){
    
    doubleFreeTest();
    invalidPtrFree();
    invalidSize();
    oversizeTest();

    return 1;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"

#define MEMLENGTH 512 
#define BYTES 4096
#define HEADERSIZE sizeof(header)
#define NEXTHEADER ptr + (HEADERSIZE + ptr->blockSize)/sizeof(header) //calculates the next header based on the size of the current block
#define EOM headstart + ((BYTES) / sizeof(header)) //EOM: "End of Memory" addreses of the last byte in memory

#ifndef DEBUG 
#define DEBUG 1
#endif


//Our "heap" an array of doubles that can hold 
//up to 4069 bytes
static double memory[MEMLENGTH];


void  * mymalloc(size_t size, char *file, int line){

    //pointer to beginning of memory array
    header *headstart = (header *) memory;

    //if memory is currently all free, initalize the header
    //set the current block to free and set size to the number of BYTES in the array 
    //minus the space the header takes up.
    if (headstart->inUse == 0 && headstart->blockSize == 0){
        headstart->inUse = 0; 
        headstart->blockSize = BYTES - HEADERSIZE;
    }
    
    //Round up the amount of memory the client needs to the 
    //smalled multiple of 8 to maintain alignment
    int memNeeded = (size +7) & ~ 7;

    
    for (header *ptr = headstart; ptr < EOM; ptr = NEXTHEADER){

        //Calculates how much memory is in the current block
        int availableMem = ptr->blockSize;
        

        //If there is free memory and, the chunk is large enough
        if (ptr->inUse == 0 && availableMem >= memNeeded){
            
            //initialize header to in use, update the size of the header 
            ptr->inUse = 1;
            ptr->blockSize = memNeeded;
            

            //check for splitting, minimum block size for split is 32 bytes
            if ((signed)(availableMem - (memNeeded+sizeof(header))) > 32){
                
                //create the free block of data following the block that just got allocated for the client

                //increment to the beginning of the allocated block
                header *tmp = ptr + 1; 

                //iterate to the end of the allocated block, this is where the new header will be for the free chunk
                tmp = tmp + (ptr->blockSize)/HEADERSIZE; 
                
                tmp->inUse = 0;
                tmp->blockSize = availableMem - (memNeeded + HEADERSIZE);
            }
            //return pointer to the allocated block 
            return (ptr + 1);
        } 
    }

    //If loop exits, this means there was not enough free space to allocate memory
    return NULL;
}
/*
* The function @myFree  will deallocate the memory previosuly allocated by myMalloc()
*
*/

void myfree(void *ptr, char *file, int line) {

    if (ptr == NULL) {                                      // if pointer is Null, terminate the function
        printf("Error: The pointer is null. File: %s, Line: %d\n", file, line);
        return;
    }


    header *headstart= (header *) memory; // start address of memory array
    header *prevHeader = NULL; // Creating a new header called previous header
    
    
    
    for (header* tmp = (header *) memory; tmp < EOM; tmp = tmp + (HEADERSIZE + tmp->blockSize)/sizeof(header)){
        // this is a valid pointer we can continue to free
        if ((char *) tmp + 8 == (char *) ptr){
            
            //make sure memory is not already freed
            if (tmp->inUse == 0){
                printf("Error: attempted to free a non allocated memory block. File: %s, Line: %d\n", file, line);
                return;
            }

            //since memory is not in use we can mark as free
            tmp->inUse = 0;

            //get access to the next header
            header *nextHeader = tmp + (HEADERSIZE + tmp->blockSize)/sizeof(header);
            
            //if nextheader exists, and is free, coalesce
            if (nextHeader < EOM && nextHeader->inUse == 0){
                tmp->blockSize = tmp->blockSize + nextHeader->blockSize + sizeof(header);
            }

            //if previous header is non-Null, and is free, coalesce
            if (prevHeader && prevHeader->inUse==0){
                prevHeader->blockSize += sizeof(header) + tmp->blockSize;      // Adding two blocks together
            }    
            return;
        }

        prevHeader = tmp;
        
    }
    printf("Error: The pointer provided is invalid. File: %s, Line: %d\n", file, line);
}


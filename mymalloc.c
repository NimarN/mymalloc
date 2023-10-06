#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"

#define MEMLENGTH 512
#define BYTES 4096
#define HEADERSIZE sizeof(header)
#define EOM headstart + BYTES //EOM : "End of Memory";
#define NEXTHEADER ptr + HEADERSIZE + ptr->blockSize

#ifndef DEBUG 
#define DEBUG 1
#endif


//Our "heap" an array of doubles that can hold 
//up to 512 bytes
static double memory[MEMLENGTH];


void  *mymalloc(size_t size, char *file, int line){

    //pointer to beginning of array 
    header *headstart = (header *) memory;

    //if memory is currently all free, initialize how much size there is 
    if (headstart->inUse == 0 && headstart->blockSize == 0){
        headstart->inUse = 0; 
        headstart->blockSize = BYTES - HEADERSIZE;
        printf("mem is initialized\n\n");
    }
    
    int memNeeded = (size +7) & ~ 7;
    if (DEBUG) printf("Need %d bytes of mem\n\n", memNeeded);
    for (header *ptr = headstart; ptr < EOM; ptr = NEXTHEADER){
        //means currblock had enough free space
        int availableMem = ptr->blockSize;
        if (ptr->inUse == 0 && availableMem >= memNeeded){
            if (DEBUG) printf("Found a block big enough that contains %d bytes. ", availableMem);
            //initialize header
            ptr->inUse = 1;
            ptr->blockSize = memNeeded;

            //check for splitting, minimum block size for split is 32 bytes
            if ((signed)(availableMem - (memNeeded+sizeof(header))) > 32){
                int test = (signed)(availableMem - (memNeeded+HEADERSIZE));
                if (DEBUG) printf("%d\n", test);
                if (DEBUG)printf("but it needs to be split\n");
                //create new block of data, after the block that just got allocated
                header *tmp = (header *)(ptr + HEADERSIZE + ptr->blockSize);
                tmp->inUse = 0;
                tmp->blockSize = availableMem - (memNeeded + HEADERSIZE);
                if (DEBUG) printf("The block is now split, into two blocks with block one having %d bytes and block two having %d bytes\n\n", ptr->blockSize, tmp->blockSize);
            }
            //return the addressof the avail memory block 
            return ptr ++;
        } 
    }

    printf("no free mem avail.");
     return NULL;
}
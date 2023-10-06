#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"

int main(int argc, char **argv){

    char *tmp = malloc(700);
    if (tmp == NULL){
        printf("mallocfailed\n");
        return 0;
    } 
    
    
    char *tmp2 = malloc(8);
    if (tmp2 == NULL){
        printf("mallocfailed\n");
        return 0;
    } 

    
    //strcpy(tmp2, "hello");
    //printf("%s\n", tmp2);
    
    int *tmp3 = malloc(8);
    if (tmp3 == NULL){
        printf("mallocfailed\n");
        return 0;
    } 
    
    printf("success");
    return 1;

}
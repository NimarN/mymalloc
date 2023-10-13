#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"

int main(int argc, char **argv){

    char *a = malloc(2036);
    if (a == NULL){
        printf("malloc failed a");
        return 0;
    }
    
    char *b = malloc(2036);
    if (b == NULL){
        printf("malloc failed b");
        return 0;
    } 

    free(a);
    
    free(a);
    free(b);

    char *p = malloc(4088);
    if (p == NULL){
        printf("malloc failed c");
        return 0;
    }
    free(p);
    
    return 1;


}
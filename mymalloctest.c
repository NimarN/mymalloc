#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"

int main(int argc, char **argv){
    
    int *t = malloc(sizeof(int));
    if (t==NULL){
        return 0;
    }
    memset(t, 5, 1);
    //*t = 5;
    

    printf("%d", *t);
   
    return 1;

}
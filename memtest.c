// Compile with -DREALMALLOC to use the real malloc() instead of mymalloc()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"

#define MEMS 4096
#define HEADERSI 8
#define OBJECTS 64
#define OBJSIZE (MEMS / OBJECTS - HEADERSI)
int main(int argc, char **argv)
{
char *obj[OBJECTS];
int i, j, errors = 0;
// fill memory with objects
for (i = 0; i < OBJECTS; i++) {
obj[i] = malloc(OBJSIZE);
}
// fill each object with distinct bytes
for (i = 0; i < OBJECTS; i++) {
memset(obj[i], i, OBJSIZE);

}
// check that all objects contain the correct bytes
for (i = 0; i < OBJECTS; i++) {
for (j = 0; j < OBJSIZE; j++) {
if (obj[i][j] != i) {
errors++;
printf("Object %d byte %d incorrect: %d\n", i, j, obj[i]
[j]);
}
}
}

printf("%d incorrect bytes\n", errors);
return EXIT_SUCCESS;
}


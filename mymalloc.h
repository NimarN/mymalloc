#ifndef MYMALLOC_H
#define MYMALLOC_H

#define malloc(s) mymalloc(s, __FILE__, __LINE__)
#define free(p) myfree(p, __FILE__, __LINE__)

 typedef struct{
    int inUse;
    unsigned blockSize;
 } header;

void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);

#endif



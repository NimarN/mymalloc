My Little Malloc Project 
CS214
Professor Menendez
Fall 23
Rutgers University

Project Contributers:
Nimar Nasir nn286 

Project Design and Layout

Heap/Memory design 

    Layout:
        
        Our heap will be a static array of 512 doubles. Calls to malloc will allocate and free
        memory from this array. 

    Header Design and Layout:




Malloc Function Implementation 

    void *mymalloc(size_t size, char *file, int line); (1)
    
    Function Overview: 
        
        Our malloc function is designed to be called from the client with a call to malloc(size_t).
        There exists macros within mymalloc.h which will replace this call with the suitable function
        protoype as showcased in (1). 

        The client supplies a size in bytes and the malloc function will sequentially search for 
        a free block of memory that has the the appropriate size. The allocation is completed with
        first-fit functionality, meaning the first free block encountered that is large enough to 
        store the client data will be used. If a suitable block is found, then a pointer to the 
        beginning of the payload is returned. If malloc fails, an error message will be printed and 
        NULL will be returned to the client. 

        
        





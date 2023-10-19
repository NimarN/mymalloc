My Little Malloc Project 
CS214 - Systems Programming
Professor Menendez
Fall 2023
Rutgers University

Project Contributers:
Mykola Doskoch  md1596
Nimar Nasir     nn286 

PROJECT DESIGN AND LAYOUT

HEAP/MEMORY DESIGN AND LAYOUT   

    Layout:
        
        Our heap will be a static array of 512 doubles. Calls to malloc will allocate and free
        suitable sized bytes of memory from this array. 

    Header Design and Layout:

        For the design of the header, we chose to implement a struct. 

        typedef struct{
            int inUse;
            unsigned blockSize;
        } header;

        The struct is typedef as header for cleanliness.
        The header struct contains the following fields: 
            1.  Integer inUse determines wether the current payload is in use. 
                0 indicates not in use (free).
                1 indicates in use.
            
            2.  Integer blockSize indicates how much free memory is held in the 
                payload. Note this size does not take into account the size of header
                and only the size of the memory intended for the client. 
        
        Our reasoning behind using a struct was to maintain cleanliness and readablility 
        within our code. Using a struct saved us the hassle of having to do additional pointer 
        arithmetic to access header info. This improves readability and reduces chances of bugs. 


MALLOC FUNCTION IMPLEMENTATION

    void *mymalloc(size_t size, char *file, int line); (1)
    
    Function Overview: 
        
        Our malloc function is designed to be utilized by the client with a call to malloc(size_t).
        There exists macros within mymalloc.h which will replace this call with the suitable function
        protoype as showcased in (1). 

        The client supplies a size in bytes and the malloc function will sequentially search for 
        a free block of memory that has the the appropriate size. The allocation is completed with
        first-fit functionality, meaning the first free block encountered that is large enough to 
        store the client data will be used. 

    Paramaters: 

        size_t size: the number of bytes the client wishes to allocate

    Return Values:
     
        If malloc() finds a suitable size of memory for the client, then a pointer to the first 
        byte of the payload is returned. The pointer type is void * to ensure that it is promoted 
        to whichever type the user is intending to use.

        If malloc() fails to find a suitably sized block of memory, then NULL is returned to the 
        client. Additionally, an error message will be printed before function exits. It is the 
        client's responsibility to ensure that the pointer returned by malloc() is non-NULL. 
        Our implementation of malloc will not halt the client program for purposes of avoiding 
        memory-leaks in the case that the client will free any previously allocated memory 
        later in their program.
    
    How Memory is Allocated:

        Assuming the client calls malloc() properly, the size which they request will be rounded up 
        to the smallest multiple of 8. This is to ensure 8 byte alignment in our heap. 
        
        malloc() will then sequentially iterate through the existing headers and find the first payload
        which is both free and large enough. malloc() will then check wether the chunk is large enough to 
        be split. The minimum block size which can be split is 32 bytes. This allows for at minimum to create
        2 chunks of memory of 16 bytes each. This is needed since our header will contain 8 bytes and the minimum 
        payload size for alignment purposes is 8 bytes. 

        If splitting occurs, then the header associated with the client's data is set to inUse and the blockSize is 
        updated. Directly following the client payload, a new header is initialized for the chunk of data that was 
        created as a result of Splitting. The pointer to the client's allocated memory is then returned.

        In the event no splitting occur, the header for the clients payload is updated by marking it in use.
        The pointer to the client's allocated memory is then returned.
    
    Error Detection and Handling: 

        The possible errors that our malloc implementation can detect are:
        
            (1) The size requested by the user is non-positive or zero
            (2) The size requested by the user is larger than the size of the heap
            (3) There is no longer any memory left in the heap
        
        Error Handling:
            
            In the case errors (1) & (2) occur:
                
                An error mesage is printed which notifies the user that the size requested is invalid.
                The file name and line number upon which the particular call to malloc() occurs is also printed.
                NULL is then returned to the user. 
            
            In the case error (3) occurs: 

                An error message is printed which notifies the user that there is no longer any free 
                memory left in the heap and advises the user to consider freeing any allocated memory 
                if appropriate. The file name and line number upon which the particular call to malloc() 
                occurs is also printed. NULL is then returned to the user. 

            In all cases of all errors the client's program is not halted. This design choice is implemented for flexibility 
            for our users as well as for prevention of memory leaks if the client has any calls to free() later in their program.
            Additionally, it is the client's responsibility to ensure that the pointer returned by malloc() is non-NULL. 

FREE FUNCTION IMPLEMENTATION
    
    void myfree(void *ptr, char *file, int line) (1)

    Function Overview:

        Our free() function is intented to be utilized by the client to free any memory which had been previously allocated by 
        the client. The client will call the function by calling free(void *ptr).  There exists macros within mymalloc.h which will 
        replace this call with the suitable function protoype as showcased in (1).

    Parameters: 

        void* ptr : The user is to provide a pointer to an allocated block of memory.

    Success vs Failure:

        Upon Success, free will set the intended header to free, and coalesce with any adjacent free memory blocks. 
        There will be no success message printed in the event free() runs properly. Thus if nothing is printed after 
        a call to free() the client can be garunteed that the call was succesful 

        Upon Error, Depending on the error, a suitable error message is printed for the user and the free() function 
        exits. 

    How Memory is Freed:

        Memory is freed by iterating through all the headers in the heap and comparing the start address of the current 
        payload against the pointer that the client has provided. If there is match and the current header is in use, 
        then the header is set to free and is coalesced with any adjacent free blocks of memory. 

        If the pointer provided by the user does not match any of the starting payload addresses, a suitable error message is printed.

    Coalescing: 

        To ensure adjacent free blocks are properly coalesced, there will be a previous pointer that points to the previouos 
        header as free() iterates through the heap. If free() finds a pointer to the start of a payload that is in use and matches
        the client's provided pointer and if there is a free header following the client's payload then the header associated with
        the payload that was freed will be updated in size to accomodate the two free adjacent blocks. The previous header will then 
        be checked to determine wether it free. If it is free, the size field will be updated by incrementing by the size of the newly
        updated block size of the client's freed payload. 

    Error Detection and Handling:

        Free() will detect the following errors:
            
            (1) The client attempts to free a pointer that is not allocated from our heap
            (2) The pointer provided points to an address in the heap but is not at the beginning of a valid payload
            (3) The client attempts to double free or free a pointer which is already free. 
            
        Error Handling:
            In the case of errors (1) and (2):
                
                Free() will print an error statement that says the pointer which they provided is invalid. 

            In the case of error (3):
                
                An error statement wil be printed which alerts the user of attempting to free a non allocated block. 
            
            In all cases, the client's program is not halted, this is designed to provide flexibility to the client. It 
            is the client's responsibility to resolve these errors. 
        
        Memory Leaks:
            
            Memory Leaks are not handled by the mymalloc() library it is in the client's best interest to ensure that before exiting 
            a program that all allocated memory has been freed. 

TESTING OUTLINE

    Basic Functionality Tests:

        basicMallocTests.c
            
            This program contains functions that test wether the basic functionalities of malloc and free work correctly
                
                1. void llTest() 
                    Tests to see if our implementation of malloc and free can create a basic linked list
                    
                    Expected Outcome: The program should print a success message if malloc works and prints a linked
                                      list of size (3)
                
                2. void binaryTreeTest()
                    Tests to see if our implementation of malloc can create a binary tree
                    
                    Expected Outcome: Program should print a success message if malloc works. It should display the 
                                      contents of the binary tree. 
                
                3. void basicStringTest()
                    Tests to see if our implementation of malloc can allocate memory for a string and we should be able to write the 
                    string "Hello World" to the allocated memory. 
                    
                    Expected Outcome: Program should print a success message if maloc works. It should then print "Hello World"
        
        memstringtest.c
        
            This program tests the ability of malloc() to write to large objects(). It will ensure that the memory allocated is distinct and 
            that writing to one object does not overwrite the other. 

            Expected Outcome: Two large test strings are kept in macros within memstringtest.h. The program will allocate two distinct objects large enough to hold one of each string
                              respectively. Then the contents of each test string will be copied into the memory allocated for it by uses of strcpy(). strcmp() will then be used to 
                              compare each object to its controlled test string. If strcpy() returns 0 then each object matches its test string thus malloc()  worked succesfully, and no memory has been overridden or corrupted.   
                              On success, the program will print "Success! Both of the strings are the same!" On error, the program will print an error which reads "Error: The strings are not equal"
    
    Error Detection Tests:      
        
        memerrors.c

            This program contains functions that purposefully calls malloc() and free() with the intent to cause errors. The purpose of 
            these tests is to see how well malloc() and free() detect and handle errors.

                1. void doubleFreeTest()
                   Tests to see if our implementation of free() catches an attempt to free a pointer twice. 
                  
                   Expected Outcome: free() should print a message stating "Error: attempted to free a non block pointer" the line number 
                                     and file name where the call to free() occured will also be provided.
                
                2. void invalidPtrFree()
                   Tests to see if free() will detect an attempt to free a pointer that doesnt point to the beginning of a payload, or 
                   a pointer that does not belong to out heap. 
                   
                   Expected Outcome: free() should print a message stating "Error: the pointer provided is invalid". The line number and 
                                     file name where the call to free() occured will also be provided.
                
                3. void invalidSize()
                   Tests to see if malloc() will detect an attempt to allocate a block of size <= 0
                   
                   Expected Outcome: The program prints a success message if the pointer returned by malloc is NULL, additionally malloc() will print 
                                     an error statement which states "Size requested is invalid. The file name and line number
                                     where the call to malloc occured will be provided. 
                
                4. void oversizeTest()
                   Test to see if malloc() will detect an attempt to allocate a block of memory that is larger than out heap. 

                   Expected Outcome: The program prints a success message if the pointer returned by malloc() is NULL, additionallt malloc() will print
                                     an error statement which states "Size requested is invalid. The file name and line number where the call
                                     to malloc occured will be provided. 
        
    Stress Tests: 
        
        memgrind.c 

            The purpose of the functions within this programs is to test how well the mymalloc library works under stress. All functions will be called by a main()
            function 50 times. The runtime in seconds for each call will be printed after the function executes. After all 50 iterations, the average runtime in seconds
            for the function to execute will be printed. 
        
                1. allocFreeTest()
                   This function tests the basic functionality of the malloc() and free() functions. It attempts to allocate a byte of memory and then immediately frees it. This occurs 
                   for a total of 120 iterations.
                   
                   Errors it's supposed to catch: Failure to allocate memory.
                   
                   Normal Operation: Memory should be successfully allocated and then freed without errors. 

                2. void fillAndFreeTest()
                    This function will declare an array of 120 char pointers. It will then call malloc() to fill the array with char pointers. Finally, all the pointers in the array will be freed. 
                    
                    Errors it's supposed to catch: Allocation errors during continuous allocation. Deallocation errors during the freeing phase.
                    
                    Normal Operation: All requested memory blocks should be allocated and then successfully freed.
                    
                    Expected Outcome: The function should output "Success! Fill and free test completed." if all allocations and deallocations are successful.       
                
                3. void randomTest()
                    
                    This function tests the memory management system by declaring an array of 120 pointers and randomly chooses between allocating pointers to add to the array and freeing pointers. 
                    It uses an int called random to pick a number between 0-1. If random == 1 then it will allocate and add an object to the array, otherwise it will free an object. 

                    Errors it's supposed to catch: Allocation errors and Deallocation errors.
                    
                    Normal Operation: Memory blocks should be allocated, added and freed based on the random choices, without causing any errors.
                    
                    Expected Outcome: The function should output "Success! Random alloc/free test completed." if all random allocations and deallocations proceed without issues.
                
                4. void largeAllocAndFree() 
                    This function will test the ability of malloc() and free() to allocate and free large chunks of memory. The test is designed to initially request for all the memory in the heap by two seperate calls 
                    to malloc(). Immedeatly after allocation, the two pointers will be freed and there will be a final call to malloc() requesting for all the memory in the heap in a single call. 

                    Expected Outcome: On success, the program should print "Success! Large Alloc and Free test completed succesfully!"

                5. void arrayWriteAlloc()
                    This function will test the ability of malloc() to properly allocate memory for an array. The array will be written to and tested to see 
                    if the object holds the correct value. 

                    Expected Outcome: On success, the program should print "Success! Array object was succesfully allocated and written to!" 

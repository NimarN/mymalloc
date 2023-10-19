/************************************************************************************
*                                PROGRAM OVERVIEW                                   *                                                                            *
* memstringtest will test wether malloc can allocate and write to  two large blocks *
* of memory without overriding. Two large test strings will be written to two       *
* seperate allocated block of memory through strcpy(). strcmp() will then be used   * 
* to ensure that the two strings are equivalent to the test string                  *
*************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <string.h>
#include "mymalloc.h"
#include "memstringtest.h"


int main(int argc, char **argv){

    //contents of TESTSTRING1 will be kept in memstringtest.h
    char TESTSTRING1[] = STRING1CONTENT;

    //allocate block of memory equal to TESTSTRING1
    char *myString1 = malloc(sizeof(TESTSTRING1));

    //ensure malloc ran succesfully 
    if (myString1 == NULL){
        printf("Error: malloc failed\n");
    }
    printf("Success! malloc worked \n");
    
    //copy the contents of myString1 into the contents of TESTSTRING1
    strcpy(myString1, TESTSTRING1);

    //contents of TESTSTRING1 will be kept in memstringtest.h
    char TESTSTRING2[] = STRING2CONTENT;

    //allocate block of memory equal to TESTSTRING1
    char *myString2 = malloc(sizeof(TESTSTRING2));
    
    //ensure malloc ran succesfully 
    if (myString2 == NULL){
        printf("Error: malloc failed\n");
        return 0;
    }
    printf("Success! malloc worked \n");
    
    //copy the contents of myString1 into the contents of TESTSTRING1
    strcpy(myString2, TESTSTRING2);

    //compare the first string to the test string
    if (strcmp(myString1, TESTSTRING1) == 0){
        printf("Success! Both of the strings are the same!\n");
    }
    
    else{
        printf("Error: The strings are not equal\n");
        return 0;
    }

    //compare the second string to the teststring
    if (strcmp(myString2, TESTSTRING2) == 0){
        printf("Success! Both of the strings are the same!\n");
    } 
    
    else{
        printf("Error: The strings are not equal\n");
        return 0;
    }

    //free the allocated blocks
    free(myString1);
    free(myString2);
    return 1;


}
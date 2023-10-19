//These test programs will ensure that the basic functionalities of 
//the mymalloc.c library work without failure. 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"

//create the struct for a list node
typedef struct _listNode{
    int data;
    struct _listNode *next;
} listNode;

//create the struct for a tree node
typedef struct _treeNode{
    int data;
    struct _treeNode *l;
    struct _treeNode *r;
} treeNode;

//function will attempt to allocate 3 nodes for a linked list
//upon succesful allocation the nodes' data will be written to 
//the final linked list will be printed
void llTest(){
    listNode *head = malloc(sizeof(listNode));

    //initialize the data for head of linked list, allocate space for next node
    head->data = 1;
    head->next = malloc(sizeof(listNode));
    
    //check if next node pointer is not null
    if (head->next == NULL){
        printf("Could not allocate memory");
        return ;
    }

    //initialize second node's data of linked list, allocate space for third node
    head->next->data = 2;
    head->next->next = malloc(sizeof(listNode));
    
    //check if third node pointer is not null
    if (head->next->next == NULL){
        printf("Could not allocate memory");
        return ;
    }

    //initalize data for third node 
    head->next->next->data = 3;
    head->next->next->next = NULL;
    
    printf("Sucess! The Linked List is: \n\n");
    for (listNode *ptr = head; ptr!= NULL; ptr = ptr->next){
        printf("%d->", ptr->data);
    }
    printf("NULL\n\n");

    //free all the nodes
    free(head);
    free(head->next);
    free(head->next->next);

    return;
}


//function will attempt to allocate 3 nodes for a binary tree
//upon succesful allocation, the nodes data will be written to 
//the final binary tree will be printed. It should contain 1 as a parent, 2 as the left child and 3 as the right child
void binaryTreeTest(){
    treeNode *parent = malloc(sizeof(treeNode));
    parent->data = 1;

    parent->l = malloc(sizeof(treeNode));
    parent->r = malloc(sizeof(treeNode));

    parent->l->data = 2;
    parent->r->data = 3;

    parent->l->l = NULL;
    parent->l->r = NULL;

    parent->r->l = NULL;
    parent->r->r = NULL;

    printf("Sucess! The Binary Tree is: \n\n");
    printf("\t%d\t\n       / \\\n      %d   %d\n\n", parent->data, parent->l->data, parent->r->data);

    free(parent);
    free(parent->r);
    free(parent->l);
}

//function will attempt to allocate space for a string containing "Hello World"
//the contents of teststr will be copied to str and compared for consistency
void basicStringTest(){
    char teststr[] = "Hello World";
    char *str = malloc(sizeof(teststr));
    if (str == NULL){
        return;
    }

    strcpy(str, teststr);
    
    if(strcmp(str , teststr) != 0){
        printf("Error: Unable to write to the allocated memory");
        return;
    }

    printf("Sucess! the string is: \n");
    printf("%s\n", str);

    free(str);
    return;

}

int main(){
   
    llTest();
    binaryTreeTest();
    basicStringTest();
    return 1;

}


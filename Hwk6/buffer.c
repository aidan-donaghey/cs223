#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>
#include "buffer.h"

typedef struct node
{
    char c;
    struct node *prev;
    struct node *next;
} node_t;

struct buffer
{
    //Stores the pointer to the head of the linked list
    node_t *head;
    //Stores all the cursors
    node_t **cursors;
    //This is constant
    unsigned long long cursorLength;
    unsigned long long bufferLength;
};

Buffer bufferCreate(size_t n)
{
    //Need to create a Node and malloc it.
    //Create a buffer and Malloc it
    //Assign the b node to the node of the malloc
    //Create all the cursors
    //Set each to the head position / NULL
    //save cursorLength
    node_t *head = calloc(1,sizeof(struct node));
    
    //Buffer b = malloc(sizeof(struct buffer));
    //Had to change this to Calloc for valgrind reasons
    Buffer b = calloc(1,sizeof(struct buffer));
    b->head = head;
    b->head->c = '\0';
    b->head->next = NULL;
    b->head->prev = NULL;
    b->cursorLength = n;
    node_t **cursors = calloc(n,sizeof(struct node));
    for (int i = 0; i < n; i++)
    {
        //Is this valid math
        cursors[i] = b->head;
    }
    b->cursors = cursors;
    b->bufferLength =0;
    return b;
}

void bufferDestroy(Buffer b)
{
    while (b->head != NULL)
    {
        node_t* tmp = b->head;
        b->head = b->head->next;
        free(tmp);
    }
    free(b->head);
    free(b->cursors);
    free(b);
}
// Insert a new non-null character before the i-th cursor position.
// All cursors continue to point to the same character
// they pointed to before.
// If i is out of range or c is '\0', has no effect.
void bufferInsert(Buffer b, size_t i, char c)
{
    if (i < b->cursorLength)
    {
        if (c != '\0')
        {
            
            node_t* newnode = malloc(sizeof(struct node));
            node_t* cursornode = b->cursors[i];
            if(cursornode->prev==NULL){
                b->head = newnode;
                newnode->prev = NULL;
                newnode->c = c;
                //printf("%c ",newnode->c);
                newnode->next = cursornode;
                cursornode->prev = newnode;
            }
            else{
                cursornode->prev->next = newnode;
                newnode->prev = cursornode->prev;
                newnode->c = c;
                //printf("%c ",newnode->prev->c);
                //printf("%c",newnode->c);
                newnode->next = cursornode;
                cursornode->prev = newnode;
            }
            b->bufferLength++;
        }
    }
}

// Advance cursor i one position.
// If i is out of range, or the i-th cursor
// already points to the final '\0',
// has no effect.
void bufferCursorForward(Buffer b, size_t i){
    if (i < b->cursorLength)
    {
        if(b->cursors[i]->c!='\0'){
            b->cursors[i] = b->cursors[i]->next;
        }
    }
}

void bufferCursorBack(Buffer b, size_t i){
    if (i < b->cursorLength)
    {
        if(b->cursors[i]!=b->head){
            b->cursors[i] = b->cursors[i]->prev;
        }
    }

}

size_t bufferCursors(Buffer b){
    return b->cursorLength;
}

size_t bufferSize(Buffer b){
    return b->bufferLength;
}

char *bufferContents(Buffer b){
    //char* returnarray = malloc(sizeof(char) * b->bufferLength);
    char* returnarray = calloc(b->bufferLength+1,sizeof(char));
    unsigned long long i=0;
    node_t* tempnode = b->head;
    while (tempnode != NULL)
    {
        // returnarray[i]=b->head->c;
        // b->head = b->head->next;
        //printf("%c",b->head->c);
        returnarray[i] = tempnode->c;
        //printf("%lld",i);
        tempnode = tempnode->next;
        i++;

    }
    return returnarray;
}
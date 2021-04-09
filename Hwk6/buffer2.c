#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>

#include "buffer.h"

// A buffer is a sequence of zero or more non-null characters
// followed by a null.

struct buffer {
  char* array;
  long long arrayLength;
  long long arrayCapacity;
  //Cursors needs to be an array of pointers
  //int **cursors;
  char** cursors;
  long long cursorLength;
  long long cursorCapacity;
};

Buffer bufferCreate(size_t n){
  // Initially, the buffer is empty, and all cursors point to the null.
  long long cursorLength = n;
  //Intiallising the array of pointers
  char **cursors = malloc(cursorLength * sizeof(int*));
  //setting the intial size because i dont know it
  char* array = (char*)malloc(sizeof(char)*100);
  Buffer b = malloc(sizeof(struct buffer));
  
  //TODO set each of the cursors to the null value.... All set to the first postitions???
  for(int i =0; i<cursorLength;i++){
    cursors[i] = &array[0];
  }

  b->array = array;
  b->arrayLength = 0;
  b->cursorLength = cursorLength;
  //each cursor should be cursor = &array[i]
  b->cursors = cursors;
  //Incase we need to add more cursors
  b->cursorCapacity = cursorLength*2;
  //Setting this 100 as that is used above. Might change this to a const
  b->arrayCapacity = 100;
  return b;
}

void bufferDestroy(Buffer b){
  free(b->array);
  free(b->cursors);
  free(b);
}

// Insert a new non-null character before the i-th cursor position.
// All cursors continue to point to the same character
void bufferInsert(Buffer b, size_t i, char c){
  long long cursorLength = b->cursorLength;
  if(i < cursorLength && i >= 0){
    if(c != '\0'){
      //This if block is reallocating double the memory if the memory is too small
      if(b->arrayLength+1==b->arrayCapacity){
        //Double the tracking of capacity
        b->arrayCapacity *=2;
        //Double the actual capacity of the array
        b->array = realloc(b->array,(b->arrayCapacity * sizeof(char)));
      }

      //Everytime this runs we need to add 1 to array length
      b->arrayLength +=1;

      //The posistion before the char is inserted, the cursors will remain correct
      //We need to move all of the remaining chars forward 1 spot and also change any cursors forward 1 spot
      for(int x = (b->arrayLength-1); x > i ; x--){
        b->array[x]=b->array[x-1];
      }
      //Now we move all cursors after the indexed one to move forward by an index amount
      for(int x = 0; x < cursorLength;x++){
        //Size of char cause that how it is index in the array
        b->cursors[x] += sizeof(char);
        
      }
      //Now the only left to do is insert that new char in at this location 
    }else{return;}
  }else{return;}
}

void bufferCursorForward(Buffer b, size_t i){
  //Need to add the logic to check that it is in range
  if(i < b->cursorLength && i >= 0){
    //if the value(which is an address) of the cursor is less than the address of the last array element 
    if(b->cursors[i]<&(b->array[b->arrayLength])){
      //Moves it forward 1
      b->cursors[i] += sizeof(char);
    }
  }
}

void bufferCursorBack(Buffer b, size_t i){
  if(i < b->cursorLength && i >= 0){
    //if the value(which is an address) of the cursor is less than the address of the first array element 
    if(b->cursors[i]>&(b->array[0])){
      //Moves it forward 1
      b->cursors[i] -= sizeof(char);
    }
  }
}

size_t bufferCursors(Buffer b){
  return b->cursorLength;
}

size_t bufferSize(Buffer b){
  return b->arrayLength;
}

char *bufferContents(Buffer b){
  return b->array;

}



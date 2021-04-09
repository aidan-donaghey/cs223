#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "wordArray.h"



//Defining the Structure of the Word Array
struct wordArray{
  int* array;
  long long arrayLength;
  int keyLength;
};

int power(int base, int power){
  int temp = 1;
  for(int i =0; i <power;i++ ){
    temp*=base;
  }
  return temp;
}

//We are creating an array that is indexed by strings length n
WordArray wordArrayCreate(unsigned int n){
  long long length = power(26,n);
  int* array = (int*)calloc(length, sizeof(int));
  WordArray w = malloc(sizeof(struct wordArray));
  w->arrayLength = length;
  w->array = array;
  w->keyLength = n;
  //printf("I have created this Correctly");
  return w;

}

void wordArrayDestroy(WordArray w){
  free(w->array);
  free(w);
}

//Check that it is as simple as this
int wordArrayKeyLength(WordArray w){
  return w->keyLength;
}

// Returns a pointer to location in word array
// indexed by string key.
//
// If key is the wrong length, or contains
// characters that are not between MIN_KEY and MAX_KEY,
// returns 0.
int *wordArrayRef(WordArray w, const char *key){
  int length = wordArrayKeyLength(w);
  //The keylength is always 2 (THIS IS CORRECT DUE TO THE INPUT)
  //printf("Key Length = %i \n",length);
  unsigned long long index = 0;
  //First check it is the right lenght
  //Might want to get rid of this due to strlen problems
  if(strlen(key)==length){
    //WORKS SO IT IS CHECKING LENGTH printf("I got here meaning the key is right length!");
    for(int i =0;i<length;i++){
      if(key[i]>=MIN_KEY_LETTER && key[i]<=MAX_KEY_LETTER ){
        //This WORKS NOW printf("length correct and correct char range   ");
        unsigned long long multifactor = power(26, (length-i-1));
        index+= multifactor*(key[i]-MIN_KEY_LETTER);
      
      }
      else{return 0;}
    }
    //we need to find the new pointer which is the old pointer moved index forward
    return &(w->array[index]);
  }
  else{return 0;}
}

//This is correct
char *wordArrayMinKey(WordArray w){
  //l+1 to add the termination null
  int len = w->keyLength;
  char *p = malloc(sizeof(char) * ( len + 1 ) );
  for(int i =0; i<len;i++){
    p[i] = MIN_KEY_LETTER;
  }
  p[len++] = '\0';
  return p;

}


int wordArrayIncKey(char *s){
  
  int len = strlen(s);
  //printf("String length is now: %i\n",len);
  for (int i = len-1; i>= 0; i--){
    if(i==0 && s[i] ==MAX_KEY_LETTER){
      //printf("I am returning 1");
      return 1;
    }
    if(s[i]< MAX_KEY_LETTER){
      s[i]+= 1;
      return 0;
    }
    if(s[i]== MAX_KEY_LETTER){
      s[i] = MIN_KEY_LETTER;
    }
  }
  return 0;
}



void wordArrayPrint(WordArray w)
{


  char *key = wordArrayMinKey(w); 
    
  do {
      printf("%s %d\n", key, *wordArrayRef(w, key));
  } while(wordArrayIncKey(key) == 0);
  //This is actually freeing wordArrayMinKey which i havent freed yet
  free(key);
}
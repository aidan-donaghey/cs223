#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "wordArray.h"

int wordArrayInc(char *s){
  
  int len = strlen(s);
  printf("String length is now: %i\n",len);
  for (int i = len-1; i>= 0; i--){
    if(i==0 && s[i] ==MAX_KEY_LETTER){
      printf("I am returning 1");
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

int main(int argc, char **argv){
  char s[] ={'y','z','z','\0'};
  printf("String is: %s\n",s);
  wordArrayInc(s);
  printf("String is now: %s\n",s);
  return 0;
}


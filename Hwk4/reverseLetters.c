#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>



//Reading in a string and saving it to memory.
//Modified from the example given in PSet 3
char *inputString(FILE* fp,size_t *length){
    size_t capacity =100;
    //int capacity =100;
    char *str;
    int ch;
    size_t len = 0;
    str = malloc(capacity);//size is start size
    //if(!str)return str;
    if(str == NULL)return NULL;
    while(EOF!=(ch=getchar())){
        str[len++]=ch;
        if(len==capacity){
            capacity *= 2;
            str = realloc(str,capacity);
            if(!str)return str;
        }
    }
    *length = len;
    str[len++]='\0';
    

    return str;
}
//It is type int to ensure it is big enough for all char values 
char *charsOnly(char *inputstring, size_t *length){
  char *temp =malloc(*length * sizeof(char));
  int count=0;
  for(int i =0; i < *length; i++){
    //Fix this so count and i are not synched and so it only aadds if char is correct
    if(isalpha(inputstring[i])){
      temp[count] = tolower(inputstring[i]);
      count++;
    }
  }
  //temp[count] = '\0';
  *length = count;
  return temp;
}

void reverseChars(char *inputString, size_t *length){
  char temp;
  for(int i =0; i < (*length)/2; i++){
    temp = inputString[i];
    //+1 is to avoid the null char at end!
    inputString[i] = inputString[*length-(i+1)];
    inputString[*length-(i+1)] = temp;
  }
  //shoudlnt be needed cause that stayed in place this just setting the same value to its self
  //inputString[*length] ='\0';
} 




void finalOutput(char *inputstring,char *reversedchars,size_t length){
  int count=0;
  for(int i=0;i<length;i++){
    if(isalpha(inputstring[i])){
      //printf("%c",reversedchars[count]);
      //Now do the capitalisation check
      if(isupper(inputstring[i])){
        inputstring[i] = toupper(reversedchars[count]); 
        count++;
      }
      else{
        inputstring[i] = reversedchars[count]; 
        count++;
      }

      
      //printf("%c",inputstring[i]);

    }

 }
}



int main(void){
    size_t length =0;
    char *inputstring = inputString(stdin,&length);
    size_t inputlength = length;
    char *charsonly = charsOnly(inputstring,&length);
    reverseChars(charsonly,&length);
    finalOutput(inputstring,charsonly,inputlength);
    for(int i= 0; i < inputlength;i++){
      printf("%c",inputstring[i]);
    }




    free(inputstring);
    free(charsonly);
    return 0;
}

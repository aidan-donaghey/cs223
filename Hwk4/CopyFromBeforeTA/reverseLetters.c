#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>



//Reading in a string and saving it to memory.
//Modified from the example given in PSet 3
char *inputString(FILE* fp){
    char *str;
    int ch;
    size_t len = 0;
    size_t size = sizeof(char);
    str = realloc(NULL, sizeof(*str)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp))){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(*str)*len);
}

char *charsOnly(char *inputstring){
  int length =strlen(inputstring);
  
  //size_t size = sizeof(char);

  char *temp =malloc(length * sizeof(char));
  //char *temp = realloc(NULL, sizeof(*temp)*size);
  int count=0;
  for(int i =0; i < length; i++){
    //Fix this so count and i are not synched and so it only aadds if char is correct
    if(isalpha(inputstring[i])){
      temp[count] = tolower(inputstring[i]);
      count++;
    }
  }
  //TODO MIGHT STILL NEED THIS
  //temp[count] = '\0';
  //printf("length of charsOnly: %i \n",count);
  return realloc(temp, sizeof(*temp)*count);
}

void reverseChars(char *inputString){
  char temp;
  //TODO ERROR HERE
  int length =strlen(inputString);
  //printf("length of reverseChars: %i \n",length);
  //printf("length is :%i",length);
  for(int i =0; i < (length)/2; i++){
    temp = inputString[i];
    //+1 is to avoid the null char at end!
    inputString[i] = inputString[length-(i+1)];
    inputString[length-(i+1)] = temp;
  }
  inputString[length] ='\0';
} 




void finalOutput(char *inputstring,char *reversedchars){
  int inlength =strlen(inputstring);
  int count=0;
  for(int i=0;i<inlength;i++){
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
  inputstring[inlength] ='\0';
}



int main(void){
    char *inputstring = inputString(stdin);
    char *charsonly = charsOnly(inputstring);
    reverseChars(charsonly);
    
    //Reversing included the last when printed
    //printf("%s",charsonly);
    //*charsonly are now reversed!
    finalOutput(inputstring,charsonly);
    printf("%s",inputstring);




    free(inputstring);
    free(charsonly);
    return 0;
}

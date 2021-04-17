#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include "FileManagement.h"

//Allocation of Space for Inputs 
Input* AllocateInputString(){
  Input* temp = malloc(sizeof(struct input));
  return temp;
}

//Freeing all of the memory allocated 
void DestroyInputString(Input* input){
  free(input->str);
  free(input);
}


//This gives back a string from the Stdin
//Might want to edit this to include a string len and other important 
//variables that would make development easier
//Possible Place for Valgrind problems
//This returns the correct lenght
Input* ReadFileFromStdin(){
  ///This is reading in the file and saving it
  size_t stringlen = 0;
  size_t stringcap = 10000;
  int *entiretext = malloc(stringcap * sizeof(int));

  int c;
  while ((c = getchar()) != EOF)
  {
    //This is the bit that is saving the whole input to a string
    if (stringlen + 1 == stringcap)
    {
      stringcap *= 2;
      entiretext = realloc(entiretext, stringcap * sizeof(int));
    }
    entiretext[stringlen] = c;
    stringlen += 1;
  }
  entiretext[stringlen] ='\0';
  Input* inputStruct = AllocateInputString();
  inputStruct->str = entiretext;
  inputStruct->buffersize = stringcap;
  inputStruct->strlen = stringlen;
  return inputStruct;
}

//Unsure if this is needed or not
Input* ReadUntilBracket(Input* inputstring){
  return inputstring;
  
}



//Possible Valgrind Problems
Input* StringBetweenBrackets(Input* input){
  Input* temp = AllocateInputString();
  int firstBracket = 0;
  int bracketcount = 0;
  int leftindex = 0;
  int rightindex = 0;
  int stringlen=0;
  int* string = malloc(sizeof(int)*input->strlen);
  //It will never be bigger than this
  for(int i=0; i < input->strlen; i++){
    if(input->str[i] == '{'){
      if(firstBracket == 0){
        firstBracket = 1;
        leftindex = i;
      }
      bracketcount+= 1;
    }
    if(input->str[i] == '}'){
      bracketcount-= 1;
      if(bracketcount == 0){
        rightindex = i;
        //This is where the output needs to be for when the brackets are even and brackets exist
        //I also know i could put this about and do it in real time 
        //The minus two accounts for getting rid of the brackets
        stringlen = (rightindex - leftindex)-2 ;
        //printf("string lenght is: %d \n",stringlen);
        for(int j = 0; j < stringlen+1 ; j++){
          string[j] = input->str[(leftindex+1) + j];
          //printf(" %c \n",string[j]);
        }
        string[stringlen+1] = '\0';
        
        temp->str = string;
        temp->strlen = stringlen+1;
        temp->buffersize = input->strlen;
        return temp;
      }
    }
  }
  //For Testing only
  //This needs changed or I think we will miss last bracket
  temp->str = string;
  temp->strlen = stringlen;
  temp->buffersize = input->strlen;
  //TODO Free this maybe???
  return temp;
}


//A more specific version that reverses the string inside of an input struct
//It also flips the direction of the brackets
//No Memory needs changed so this will not a reason for valgrind errors
Input* ReverseInputString(Input* input){
  int len = input->strlen;
  int tempend;
  int tempstart;
  for(int i= 0; i< len/2; i++){
    if(input->str[i] == '{'){
      tempstart = '}';
    }
    else if(input->str[i] == '}'){
      tempstart = '{';
    }
    else{
      tempstart = input->str[i];
    }


    if(input->str[len-1-i] == '}'){
      tempend = '{';
    }
    else if(input->str[len-1-i] == '{'){
      tempend = '}';
    }
    else{
      tempend = input->str[len-1-i];
    }
    input->str[i] = tempend;
    input->str[len-1-i] = tempstart;
  }
  return input;
}


//Returns a string that is up to the first bracket
//It will return a NUll char and a strlen = 0 if empty
Input* BeforeFirstBracket(Input* input){
  Input* string = AllocateInputString();
  string->str = malloc(sizeof(int) * input->buffersize);
  string->buffersize = input->buffersize;
  for(int i=0; i<input->strlen; i++){
    if(input->str[i] == '{'){
      string->str[i] ='\0';
      string->strlen = i;
      //printf("%d\n",i);
      return string;
    }
    string->str[i]  = input->str[i];
  }
  string->strlen = input->strlen;
  return string;
}

//Unsure if this is needed anymore
Input* AfterFirstBracket(Input* input){
  int seenfirst =0;
  int indexoffirst =0;
  Input* string = AllocateInputString();
  string->str = malloc(sizeof(int) * input->buffersize);
  string->buffersize = input->buffersize;
  for(int i=0; i<input->strlen; i++){
    if(seenfirst ==0){
      if(input->str[i] == '{'){
        //printf("Index of First bracket: %d\n",i);
        seenfirst =1;
        indexoffirst = i;
      }
    }
    if(seenfirst == 1){
      string->str[i-indexoffirst] = input->str[i];
    }
    string->strlen = (input->strlen - indexoffirst);
  }
  //printf("Total inside: %ls\n", string->str);
  return string;
}

//This returns whatever string is after the bracket Pair
//It will return NULL char and a string length of 0 if there is nothing after it
Input *AfterBracketPair(Input *input)
{
  Input *temp = AllocateInputString();
  int firstBracket = 0;
  int bracketcount = 0;
  //int leftindex = 0;
  int rightindex = 0;
  int stringlen = 0;
  int *string = malloc(sizeof(int) * input->strlen);
  for (int i = 0; i < input->strlen; i++)
  {
    if (input->str[i] == '{')
    {
      if (firstBracket == 0)
      {
        firstBracket = 1;
        //leftindex = i;
      }
      bracketcount += 1;
    }
    if (input->str[i] == '}')
    {
      bracketcount -= 1;
      if (bracketcount == 0)
      {
        rightindex = i;
        //This is where the output needs to be for when the brackets are even and brackets exist
        //I also know i could put this about and do it in real time
        //The minus two accounts for getting rid of the brackets
        stringlen = input->strlen - rightindex;
        for (int j = 0; j < stringlen + 1; j++)
        {
          string[j] = input->str[rightindex + 1 + j];
          //printf(" %c \n",string[j]);
        }

        temp->str = string;
        temp->strlen = stringlen -1;
        temp->buffersize = input->strlen;
        //TODO Free this maybe???
        return temp;
      }
    }
  }
  //If it gets here it means that there is nothing after the brackets
  //More Specifically it means there are no bracket pairs
  temp->str = '\0';
  temp->strlen = 0;
  temp->buffersize = input->strlen;
  //TODO Free this maybe???
  return temp;
}
//Need to free this at somepoint too
char* IntArraytoCharArray(Input* input){
  char* output = malloc(sizeof(char) * input->strlen+1);
  for(int i=0; i<input->strlen+1; i++){
    output[i] = input->str[i];
    }
    output[input->strlen+1] = '\0';
    return output;
}
//This assumes there is enough room to do so
Input* AppendtoInput(Input* input,Input* input2){
  //printf("outputSTRLEN:%ld",input->strlen);
  //printf("inputSTRLEN:%ld\n",input2->strlen);
  for(int i = input->strlen; i < input->strlen + input2->strlen; i++){
    //printf("%d ",i);
    input->str[i] = input2->str[i-input->strlen];
  }
  DestroyInputString(input2);
  return input;
}


//New Solution 
int* ReverseIntArray(int* a, int len){
  int tempend;
  int tempstart;
  for(int i= 0; i< len/2; i++){
    if(a[i] == '{'){
      tempstart = '}';
    }
    else if(a[i] == '}'){
      tempstart = '{';
    }
    else{
      tempstart = a[i];
    }


    if(a[len-1-i] == '}'){
      tempend = '{';
    }
    else if(a[len-1-i] == '{'){
      tempend = '}';
    }
    else{
      tempend = a[len-1-i];
    }
    a[i] = tempend;
    a[len-1-i] = tempstart;
  }
  return a;
}

int* ReverseIntsBetween(int* a , int begin, int end){
  int tempend;
  int tempstart;
  int len = end - begin;
  for(int i= begin; i< begin + (len/2); i++){
    if(a[i] == '{'){
      tempstart = '}';
    }
    else if(a[i] == '}'){
      tempstart = '{';
    }
    else{
      tempstart = a[i];
    }


    if(a[len-1-i] == '}'){
      tempend = '{';
    }
    else if(a[len-1-i] == '{'){
      tempend = '}';
    }
    else{
      tempend = a[len-1-i];
    }
    a[i] = tempend;
    a[len-1-i] = tempstart;
  }
  return a;
}



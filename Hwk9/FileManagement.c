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


//Take in the location of the starting and ending location 
//Outputs the string reversed between those two values
//I could just return the index number i suppose 
//Possible Valgrind Problems
Input* StringBetweenBrackets(Input* inputstring){
  Input* temp = AllocateInputString();
  int firstBracket = 0;
  int bracketcount = 0;
  int leftindex = 0;
  int rightindex = 0;
  int stringlen=0;
  int* string = malloc(sizeof(int)*inputstring->strlen);
  //It will never be bigger than this
  for(int i=0; i < inputstring->strlen; i++){
    if(inputstring->str[i] == '{'){
      if(firstBracket == 0){
        firstBracket =1;
        leftindex = i;
      }
      bracketcount+= 1;
    }
    if(inputstring->str[i] == '}'){
      bracketcount-= 1;
      if(bracketcount == 0){
        rightindex = i;
        //This is where the output needs to be for when the brackets are even and brackets exist
        //I also know i could put this about and do it in real time 
        //The minus two accounts for getting rid of the brackets
        stringlen = (rightindex - leftindex)-2 ;
        //printf("string lenght is: %d \n",stringlen);
        for(int j = 0; j < stringlen+1 ; j++){
          string[j] = inputstring->str[(leftindex+1) + j];
          //printf(" %c \n",string[j]);
        }
        string[stringlen+1] = '\0';
        
        temp->str = string;
        temp->strlen = stringlen;
        temp->buffersize = inputstring->strlen;
        //Strange that it gets here but it doesnt return a temp that includes string
        //printf("%ls \n",temp->str);
        DestroyInputString(inputstring);
        return temp;
      }
    }
  }
  //For Testing only
  //This needs changed or I think we will miss last bracket
  inputstring->str[0] = 0;
  return inputstring;
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



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include "FileManagement.h"


void RecursiveFunc(Input* input,int* output){
  //Fix This with a real end condition
  if(input->str[0] == 0 ){
    //DestroyInputString(input);
    return;
  }
  printf("%ls\n",input->str);
  input = StringBetweenBrackets(input);
  input = ReverseInputString(input);
  //Problem with not freeing memory 
  //I think it will be resovled with I set the 
  //return type of Recursive fucnt as input then i can free that at 
  //the end
  RecursiveFunc(input,output);
}

int main(int argc, char **argv)
{
  Input* inputstr = ReadFileFromStdin();
  int* output = malloc(inputstr->strlen * sizeof(int));
  RecursiveFunc(inputstr,output);
  
  DestroyInputString(inputstr);

}


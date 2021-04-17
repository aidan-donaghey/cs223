#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include "FileManagement.h"




//The solution neal had was we pass in &len and then dereferecne it
//Unsure how we actually do this 
//len_rec should be passed like &len_rec
//Dont need a length to read to because it will always have a closing bracket
int* RecursiveFuct(int* inputstr, int* len_rec, int index,int totallen){
  //Starting at count 1 because it skips over the bracket
  int* buffer = malloc(sizeof(int)* totallen);
  int count = 1;
  while(inputstr[count+index]!= '}'){
    if(inputstr[count] == '{'){
      int* temp = RecursiveFuct(inputstr, len_rec,  index + count);
      for(int j = 0; j < len_rec ; j++){
        output[i+j] = temp[j];//Return of Recursive funct
      }
    }
    buffer[count] = inputstr[count+index];
    count += 1;

  }
  if(inputstr[index] == '}'){
    *len_rec = count;
    buffer = ReverseIntArray(buffer,len_rec);
    //Buffer needs reversed before return
    return buffer;
  }
  
  
}

//If i see a bracket i want to create a buffer to save it 
//But also be checking if another bracket shows up

int main(int argc, char **argv)
{
  //This reads it in as a *int
  //It also contains the length
  Input* input = ReadFileFromStdin();
  int inputlen = input->strlen;
  int* inputstring = input->str;
  int* len_rec = 0;
  int totalbracketcount = 0;
  int* output = malloc(sizeof(int) * inputlen);
  
  //Big overall Loop for creating final output
  for(int i=0; i < inputlen; i++){
    if(inputstring[i]!='{'){
      output[i] = inputstring[i];
    }
    if(inputstring[i]=='{'){
      //Call the recurive function
      //This returns a int* and will have altered len
      //so that this works
      int* temp = RecursiveFuct(inputstring,&len_rec,i,inputlen);
      for(int j = 0; j < len_rec ; j++){
        output[i+j] = temp[j];//Return of Recursive funct
      }
      

    }
    
  }
 
    

}
  

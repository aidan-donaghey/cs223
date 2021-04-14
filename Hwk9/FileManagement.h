#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>

//TODO organise these better
struct input
{
  int *str;
  size_t buffersize;
  size_t strlen;
};

typedef struct input Input;

Input* AllocateInputString();
void DestroyInputString(Input* );


//Reads and outputs a string with Stdin 
Input* ReadFileFromStdin(void);

//Get the string between brackets
Input* StringBetweenBrackets(Input* );


Input* ReverseInputString(Input* );
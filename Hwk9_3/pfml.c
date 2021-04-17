#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "FileManagement.h"


void reverse_str(int* input_str, int len) {
    for(int i = 0; i < len / 2; i += 1) {
        int tmp = input_str[i];
        input_str[i] = input_str[len - i - 1];
        input_str[len - i - 1] = tmp;
    }
}

void print(int* input_str, int len) {
    for(int i = 0; i < len; i += 1) {
        putchar((char)input_str[i]);
    }
    puts("\r\n");
}

void print_without(int* input_str, int len) {
    for(int i = 0; i < len; i += 1) {
        if(input_str[i] == '{' || input_str[i] == '}')
            continue;
        putchar((char)input_str[i]);
    }
    //puts("\r\n");
}

void reverse(int* input_str, int len) {
    int cnt = 0;
    int firstIdx = -1;

    for(int i = 0; i < len; i += 1) {
        //printf("%c",input_str[i]);

        if(input_str[i] == '{') {
            if (firstIdx == -1) {
                firstIdx = i;
            }
            cnt += 1;
        }

        if(input_str[i] == '}') {
            if (cnt == 1) {
                //printf("set found\r\n");

                reverse(input_str + firstIdx + 1, i - firstIdx);
                reverse_str(input_str + firstIdx + 1, i - firstIdx - 1);

                firstIdx = -1;
            }
            cnt -= 1;
        }

    }
    
}


int main(int argc, char **argv)
{
  
  Input* input = ReadFileFromStdin();
  int inputlen = input->strlen;
  //printf("%d",inputlen);
  int* inputstring = input->str;
  int* outputstring = malloc(sizeof(int)* inputlen);
  memcpy(outputstring,inputstring,sizeof(int)* inputlen);  
  reverse(outputstring, inputlen);
  //printf("%ls",inputstring);
  //print_without(inputstring, inputlen);
  print_without(outputstring, inputlen);
  DestroyInputString(input);
  free(outputstring);
}

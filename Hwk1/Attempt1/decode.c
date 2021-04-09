#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
   int len = 0;
   char c;
   while((c= getchar()) != EOF ){
      
      if(len==0){
         if(isdigit(c)){
         len = c - 48;
         len = len + 1;
         }
         else{
            printf("%c",c);
         }
      }
      else{
         for (int i = 0; i < len; i++){
            printf("%c",c);
         }
         len = 0;
      }
   }
   return 0;
}
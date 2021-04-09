#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
   bool processingSeq = false;
   int current_no = 0;
   int c;

   while((c= getchar()) != EOF ) {
      if(!processingSeq) {
        if(isdigit(c)) {
          current_no = c -'0';
          processingSeq = true;
        } else {
          printf("%c",c);
          } 
      } else { 
          for(int i = 0; i < current_no + 1; i +=1) {
            printf("%c",c);
          }
        processingSeq = false;
        }
   }
}
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
  //Check that this exists
  //This setting current_char might mess it up
   int current_char = getchar();
   if(current_char == EOF){
     return 0;
   }
   int current_no = 1;
   int c;

   while((c= getchar()) != EOF ) {
     if(c==current_char) {
       current_no +=1;
       if(current_no==10) {
         printf("9%c",current_char);
         //Why is this set to zero
         current_no = 0;
       }
     } else {
       if(current_no ==1) {
         if(isdigit(current_char)) {
           printf("0%c",current_char);
         } else {
           printf("%c",current_char);
         }
       } else if(current_no ==2) {
         if(isdigit(current_char)) {
           printf("1%c",current_char);
         } else {
           printf("%c%c",current_char, current_char);
         }
       } else if(current_no != 0) {
         //Maybe just change this to %d
         printf("%c%c",(current_no-1)+'0',current_char);
       }
       current_char = c;
       current_no =1;
     }
   }
   //This is the cases for the last sequence of digits
   //The logic is the same as above.
   if(current_no ==1) {
         if(isdigit(current_char)) {
           printf("0%c",current_char);
         } else {
           printf("%c",current_char);
         }
       } else if(current_no ==2) {
         if(isdigit(current_char)) {
           printf("1%c",current_char);
         } else {
           printf("%c%c",current_char, current_char);
         }
       } else if(current_no != 0) {
         //Maybe just change this to %d
         printf("%c%c",(current_no-1)+'0',current_char);
       }

       c = getchar();
       return 0;

}
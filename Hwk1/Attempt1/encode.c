#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  char c;
  char currentc;
  int len = 0;
  //TEST
  int first =1;
  while ((c = getchar()) != EOF)
  {
    //printf("c = %c currentc = %c len = %d\n",c,currentc,len);
    if (c != currentc)
    {

    
      /* 
      This is an extra part to deal with the undefined currentc variable
       */

      //This is for a single character
      if (len == 0)
      {
        //single Number
        if (isdigit(currentc))
        {
          printf("0%c", currentc);
          currentc = c;
        }
        else
        {
          if(first ==1){
            currentc = c;
            first = 0;
          }
          else
          {
            printf("%c", currentc);
            currentc = c;
          }
          
        }
      }
      //This is for the edge case where there are 2 and only 2 in a row
      else if (len == 1)
      {
        //This is the edge case where there are 2 of the same digit in which it is given by
        //1(digit) NOT
        if (isdigit(currentc))
        {
          printf("1%c", currentc);
          currentc = c;
          len = 0;
        }
        //This is for if there are 2 non digits in a row
        else
        {
          printf("%c%c", currentc, currentc);
          currentc = c;
          len = 0;
        }
      }
      //This is the standard output for duplications greater than 2
      else
      {
        printf("%d%c", len, currentc);
        currentc = c;
        len = 0;
      }
    }
    //This is if it is the same and we are not done
    else
    {
      //if it is more than 10 Digits long
      if (len == 9)
      {
        printf("%d%c", len, currentc);
        currentc = c;
        len = 0;
      }
      else
      {
        len += 1;
      }
    }
  }
  //END of WHILE LOOP

  //This is the check that we do for the last set of digits
  //This is for a single character
  if (len == 0)
  {
    if (isdigit(currentc))
    {
      printf("0%c", currentc);
    }
    else
    {
      printf("%c", currentc);
    }
  }
  //This is for the edge case where there are 2 and only 2 in a row
  else if (len == 1)
  {
    //This is the edge case where there are 2 of the same digit in which it is given by
    //1(digit) NOT
    if (isdigit(currentc))
    {
      printf("1%c", currentc);
    }
    //This is for if there are 2 non digits in a row
    else
    {
      printf("%c%c", currentc, currentc);
    }
  }
  //This is the standard output for duplications greater than 2
  else
  {
    printf("%d%c", len, currentc);
  }
  return 0;
}
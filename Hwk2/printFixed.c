#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "printFixed.h"
#include <string.h>
//#include "testheader.h"
// test harness for printFixed

#define BASE (10) // to force base 10 in strtoll

extern void printFixed(long long number, char separator, char decimalPoint, unsigned int precision){

  //This is just getting the size of the array that I need
  long long numlength = 0;
  int negative = 0;
  long long temptempnumber = llabs(number);
  if(number < 0){
    negative = 1;
    }
  //do a check up here if it is negetive or not
  unsigned long long tempnumber = temptempnumber;
  //printf("%lld\n",tempnumber);
  while(tempnumber !=0){
    tempnumber /=10;
    numlength++;
  }
  
  
  
  char numarray[numlength];
  numlength = 0;
  tempnumber = temptempnumber;
  while(tempnumber !=0){
    numarray[numlength] = (tempnumber % 10)+48;
    tempnumber /=10;
    numlength++;
  }
  numarray[numlength] = '\0';
  //printf("%s",numarray);
  

  //Reversing the string
  char temparray[2000];
  for(int i =0; i< numlength; i++){
    temparray[i] = numarray[numlength-i-1];
  }
  temparray[numlength] = '\0'; 

  //printf("%s",temparray);





  //At this point I have a string saved as temparray which is the correct string for whateverlong it can be .
  //printf("%lu",strlen(temparray));
  int currentarraylength = strlen(temparray);
  char tempfront[1000];
  char reversetemp[1000];
  char commatemp[1000];
  int currentpos = 0;
  int positionoffirstdecimal = 0;
  int temparraylength = 0;
  //Now lets deal with easy case of placing the decimal where it needs to go.
  if(precision < currentarraylength){
    //getting front back array
    for(int i =0; i< (currentarraylength - precision); i++){
    tempfront[i] = temparray[i];
    currentpos ++;
    }
    tempfront[currentpos] = '\0';


    positionoffirstdecimal = currentpos;
    temparraylength =currentarraylength;

    
    //This is attempting to add the comma's before we add the end
    //printf("This is all the parts before the decimal:%s\n",tempfront);
    
    
    
    //This is where we add the commas that are needed
    int commacount =0;
    int commastringpos= 0;
    int tempfrontlen = strlen(tempfront);
    for(int i = 0; i < tempfrontlen;i++){
      reversetemp[i] = tempfront[(tempfrontlen-i-1)];
      commastringpos++;
    }
    reversetemp[commastringpos] = '\0';
    //printf("This is all before dec but backwards :%s\n",reversetemp);
    //Above is the string before the decimal in the reverse order
    //Below i will be adding the commas every three positions 
    //After that i will have to reverse it again 



    //Calculate the number of Commas
    int amountofcommas = (tempfrontlen-1)/3;
    //The above is a good way to solve things.
    commastringpos= 0;
    int extraCharsadded = 0;

    //printf("amount of commas: %i",amountofcommas);
    for(int i =0; i < tempfrontlen + amountofcommas; i++){
      commacount ++;
      if(commacount<=3)
      {
        commatemp[i] = reversetemp[i-extraCharsadded];
      }
      else{
        commacount =0;
        extraCharsadded ++;
        commatemp[i] =  + separator;
      }
      commastringpos++;
    }
    commatemp[commastringpos] =  '\0';
    int commaddedlength = commastringpos;

    //This part above is in the wrong order so now it needs reversed
    char commaddedforeward[1000];
    for(int i =0; i< commaddedlength; i++){
    commaddedforeward[i] = commatemp[commaddedlength-i-1];
    }
    commaddedforeward[commaddedlength] = decimalPoint;
    commaddedlength++; 
    commaddedforeward[commaddedlength] = '\0'; 
    //strcat(commaddedforeward,&decimalPoint);
    //At this point the commaddedforeward is the correct first bit.
    //Now i just need to get the length of that string so that we can start the rest of the 
    //program at the right index

    



      

    //This is where we add the decimal 

    //I am just printing out the chars after decimal to show i can do it
    char lastdigits[2000];
    int lastdigitpos = 0;
    for(int i = positionoffirstdecimal; i<temparraylength ; i ++){
      lastdigits[lastdigitpos] = temparray[i];
      lastdigitpos++;
    }
    lastdigits[lastdigitpos] ='\0';
    //printf("This is the last digits after the decimal: %s \n",lastdigits);
    //This is adding what is after the decimal to the comma seperated version
    strcat(commaddedforeward,lastdigits);
    
    //Fix it above here on how to get the decimal
    //Adding the Negative
    if(negative == 1){
      printf("-%s",commaddedforeward);
    }else{
      printf("%s",commaddedforeward);
    }
  }
  //This is for if we need to add trailing zeros   
  //This is what i will do in the morning!!


  //This for if the they are the same length
  else if(precision == currentarraylength){
    //printf("precision = to the length\n");
    tempfront[0] = '0';
    tempfront[1] = decimalPoint;
    for(int i =0; i< (currentarraylength+2); i++){
    tempfront[i+2] = temparray[i];
    currentpos ++;
    }
    tempfront[currentpos] ='\0';
    //Adding the Negative
    if(negative == 1){
      printf("-%s",tempfront);
    }else{
      printf("%s",tempfront);
    }
  }
  //This is for if precision is higher than the length
  else{
    int differenceinLength = precision - currentarraylength;
    //printf("Precision is %i longer than number\n",differenceinLength);
    tempfront[0] = '0';
    tempfront[1] = decimalPoint;
    int pos = 2;
    while(differenceinLength>0){
      differenceinLength--;
      tempfront[pos] = '0';
      pos++;
    }
    tempfront[pos] = '\0';
    strcat(tempfront,temparray);

    if(negative == 1){
      printf("-%s",tempfront);
    }else{
      printf("%s",tempfront);
    }
  }

}

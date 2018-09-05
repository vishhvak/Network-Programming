#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int binary(long num)
{
    long decimal_num, remainder, base = 1, binary = 0, no_of_1s = 0;
    decimal_num = num;
    while (num > 0)
    {
        remainder = num % 2;
        binary = binary + remainder * base;
        num = num / 2;
        base = base * 10;
    }
    return binary;
}

int parity(char bin[]) {
  int parity,x,count=0,l = strlen(bin);
  printf("\nLength of message is %d",l);
  for(int i=0; i<l; i++)
  {
    x = bin[i] - '0';
    if(x==1) 
      ++count;
  }
  printf("\nNumber of 1s in string is %d",count);
  if(count%2==0)
    parity = 0;
  else
    parity = 1;
  return parity;
}

int main() {
  long temp;
  char s[4],buffer[100];
  char bin[100];
  long bins;
  printf("\nEnter a 4 character string");
  scanf("%s",s);
  for(int i = 0; i < 4; i++) {
    temp = (long)s[i];
    bins = binary(temp);
    sprintf(buffer,"%ld",bins);
    strcat(bin,buffer);
  } 
  printf("\nBinary form of string is %s\n",bin);
  int par = parity(bin);
  printf("\nParity of string is %d\n",par);
  char parity = par + '0';
  strcat(bin,&parity);
  printf("Message sent with parity = %s",bin);
  return 0;
}

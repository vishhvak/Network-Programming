#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
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

  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;
  int cport;
  long temp,bins;
  char s[4],buffer[100],bin[100];

  printf("Enter port number\n");
  scanf("%d",&cport);

  int csd = socket(AF_INET, SOCK_STREAM, 0);
  //Check if socket is created or not;
  if (csd < 0)
  {
        printf("\n Socket creation error \n");
        return -1;
  }

  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  servaddr.sin_port=htons(cport);

  int c = connect(csd,(struct sockaddr*)&servaddr,sizeof(servaddr));
  //check whether connection is done or not;
  if (c < 0)
  {
        printf("\nConnection Failed \n");
        return -1;
  }
  else 
      printf("\nConnection Successful!\n");

  printf("\nEnter a 4 character string - ");
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
  printf("Message being sent after adding parity = %s",bin);

  printf("\nSending message to server\n");
  send(csd, bin, 30, 0);

  recv(csd, buffer, 10, 0);
  printf("\nMessage recieved from Server : %s\n", buffer);
  printf("\nClosing connection.\n");
  close(csd);
  return 0;
}

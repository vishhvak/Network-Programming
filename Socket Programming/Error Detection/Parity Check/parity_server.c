#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int parity_check(char bin[]) {
  int parity,x,count=0,l = strlen(bin);
  printf("\nLength of message is %d",l);
  for(int i=0; i<l; i++)
  {
    x = bin[i] - '0';
    if(x==1) 
      ++count;
  }
  printf("\nNumber of 1s in message is %d",count);
  if(count%2==0)
    parity = 0;
  else
    parity = 1;
  return parity;
}

int main() {
  
  struct sockaddr_in servaddr, cliaddr;
  socklen_t size;
  int portnumber;
  printf("Enter port number\n");
  scanf("%d",&portnumber);
  //Enter port number - integer;

  int sd = socket(AF_INET,SOCK_STREAM,0);
  //Check if socket is created or not;
  if (sd == 0)
  {
      perror("Socket Failed");
      exit(EXIT_FAILURE);
  }

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY); //host to network long
  servaddr.sin_port = htons(portnumber);
  int b = bind(sd,(struct sockaddr*)&servaddr, sizeof(servaddr));

  //check if binded or not;
  if (b < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

  int l = listen(sd, 3);
    //listen for connection;
  if (l < 0)
  {
      perror("Listen");
      exit(EXIT_FAILURE);
  }
  size = sizeof(cliaddr);
  int nsd = accept(sd, (struct sockaddr*)&cliaddr, &size);

  //Check whether connection is accepted or not;
  if (nsd <0)
  {
      perror("Accept");
      exit(EXIT_FAILURE);
  }
  else
    printf("\nServer is connected!\n");

  char buffer[100];
  recv(nsd, buffer, 29, 0);

  printf("\nMessage recieved from client is %s\n",buffer);
  int res = parity_check(buffer);

  printf("\nMessage recieved with parity = %d\n",res);

  if(res == 0) {
    char msg[] = "No Errors";
    printf("\nMessage recieved with no errors");
    send(nsd, msg, 10, 0);
  }
  else if(res == 1) {
    char msg[] = "Error";
    printf("\nError detected in message recieved");
    send(nsd, msg, 5, 0);
  }

  printf("\nSending Acknowledgement to Client..\n");
  printf("\nClosing connection.\n");
  close(sd);
  return 0;
}

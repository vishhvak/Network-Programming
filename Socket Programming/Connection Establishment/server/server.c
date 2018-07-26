#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int main() {
	struct sockaddr_in servaddr, cliaddr;
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
    int clilen = sizeof(cliaddr);
    int nsd = accept(sd, (struct sockaddr*)&cliaddr, &clilen);
    //Check whether connection is accepted or not;
    if (nsd <0)
    {
        perror("Accept");
        exit(EXIT_FAILURE);
    }
    else
    	printf("\nServer is connected!\n");
    close(sd);
	return 0;
}

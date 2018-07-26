#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
	struct sockaddr_in servaddr, cliaddr;
	int portnumber;
    char *msg,*rcv;
    char bye[]="Bye";
    msg = malloc(256);
    rcv = malloc(256);
	printf("Enter port number\n");
	scanf("%d",&portnumber);
	//Enter port number - integer;
	int sd = socket(AF_INET,SOCK_STREAM,0);
	//Check if socket is created or not;
	if (sd == 0)
    {
        perror("Socket Failed");
        exit(0);
    }
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY); //host to network long
	servaddr.sin_port = htons(portnumber);
	int b = bind(sd,(struct sockaddr*)&servaddr, sizeof(servaddr));
	//check if binded or not;
	if (b < 0)
    {
        perror("Bind failed");
        exit(0);
    }
    int l = listen(sd, 3);
    //listen for connection;
    if (l < 0)
    {
        perror("Listen");
        exit(0);
    }
    int clilen = sizeof(cliaddr);
    int nsd = accept(sd, (struct sockaddr*)&cliaddr, &clilen);
    //Check whether connection is accepted or not;
    if (nsd <0)
    {
        perror("Accept");
        exit(0);
    }
    int c = 1;
    printf("\nServer Connected to Chat!\n");
    do {
        scanf("%s", msg);
        send(sd , msg , strlen(msg) , 0 );
        if(strcmp(bye,msg)==0)
        {
            c = -1;
            printf("\nClosing Chat\n");
            break;
        }
        recv(sd, rcv, 100, 0);
        printf("\nClient : %s\n",rcv);
    }while(c > 0);
    close(sd);
	return 0;
}

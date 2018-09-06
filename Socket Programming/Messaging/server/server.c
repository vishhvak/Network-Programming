#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXSIZE 1024
int main() {
	struct sockaddr_in servaddr, cliaddr;
	int portnumber;
    char *msg,*rcv;
    msg = malloc(sizeof(char) * 1024);
    rcv = malloc(sizeof(char) * 1024);
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
    if (nsd < 0)
    {
        perror("Accept");
        exit(0);
    }
    int r,s,c = 1,x=0;
    r = recv(nsd, rcv, 1024, 0);
    printf("\nChat mode is live!\n");
    do {
        printf("\nClient : %s \n", rcv);
        fgets(msg,MAXSIZE-1,stdin);
        if(strcmp("Bye",msg)==0)
        {
            c = -1;
            printf("\nClosing Chat\n");
            break;
        }
        s = send(nsd , msg , strlen(msg) , 0 );
        if(s < 0)
        {
            printf("\nFailed to send message!\n");
            break;
        }
        r = recv(nsd, rcv, 1024, 0);
        if(r < 0)
        {
            printf("\nFailed to Recieve message!\n");
            break;
        }
    }while(c > 0);
    close(nsd);
    close(sd);
	return 0;
}

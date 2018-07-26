#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1024
int main() {
	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;
	char *msg,*rcv;
    msg = malloc(sizeof(char) * 1024);
    rcv = malloc(sizeof(char) * 1024);
	//Enter port number - integer;
	int cport;
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
    int s,r;
    printf("\nChat mode is live!\n");
    int d = 1,x=0;
	do {
        r = recv(csd, rcv, 1024, 0);
        if(r < 0)
        {
            printf("\nFailed to Recieve message!\n");
            break;
        }
        if(x==0) {
            printf("\nServer : Online! \n\n");
            ++x;
        }
        else
            printf("\nServer : %s \n", rcv);
        fgets(msg,MAXSIZE-1,stdin);
        s = send(csd , msg , strlen(msg) , 0);
        if(s < 0)
        {
            printf("\nFailed to send message!\n");
            break;
        }
        if(strcmp("Bye",msg)==0)
        {
            d = -1;
            printf("\nClosing Chat\n");
            break;
        }
    }while(d > 0);
	close(csd);
	return 0;
}

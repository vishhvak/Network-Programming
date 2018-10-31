#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main() {

	struct sockaddr_in servaddr;

	char *msg,*rcv;
    msg = malloc(sizeof(char) * 1024);
    rcv = malloc(sizeof(char) * 1024);

	//Enter port number - integer;
	int cport;
	printf("Enter port number\n");
	scanf("%d",&cport);

	int client = socket(AF_INET, SOCK_STREAM, 0);
	//Check if socket is created or not;
	if (client < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(cport);

	int c = connect(client,(struct sockaddr*)&servaddr,sizeof(servaddr));
	//check whether connection is done or not;
	if (c < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    int s,r;
    printf("\nChat mode is live!\n");

    int d = 1, x=0, y=0;

	do {

        msg = malloc(sizeof(char) * 1024);
        rcv = malloc(sizeof(char) * 1024);
        
        if(x == 0) {
            printf("\nClient : Initial ACK ");
            ++x;
        }
        else if (x!=0)
        {
            printf("\nClient : ");
            fgets(msg,1024,stdin);
            s = send(client , msg , strlen(msg) , 0);
            if(s < 0)
            {
                printf("\nFailed to send message!\n");
                break;
            }
        }

        if(y==0) {
            printf("\nServer : Online! \n\n");
            ++y;
        }
        else if(y!=0) 
        {
            r = recv(client, rcv, 1024, 0);
            if(r < 0)
            {
                printf("\nFailed to Recieve message!\n");
                break;
            }
            printf("\nServer : %s \n", rcv);
        }
            
        /*if(strcmp("Bye",msg)==0)
        {
            d = -1;
            printf("\nClosing Chat\n");
            break;
        }*/

        free(msg);
        free(rcv);

    }while(d > 0);

	close(client);
	return 0;
}

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main() {

	struct sockaddr_in servaddr;

	//Enter port number - integer;
	int cport = 1877;
	// printf("Enter port number\n");
	// scanf("%d",&cport);

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


    printf("\nChat mode is live!\n");

    char msg[1024], rcv[1024];
	
    while(1)
    {
        printf("\nClient : ");
        
        fgets(msg,1024,stdin);
        int s = send(client , msg , 1024, 0);
        
        if(s < 0)
            printf("\nFailed to send message to server!\n");
        
        if(strcmp("Bye",msg)==0)
        {
            printf("\nClosing Chat\n");
            break;
        }
        
        int r = recv(client, rcv, 1024, 0);
        
        if(r > 0)
            printf("\nServer : %s \n", rcv);
        else if(r < 0)
            printf("\nFailed to recieve message from server!\n");
        
        if(strcmp("Bye", rcv)==0)
        {
            printf("\nClosing Chat\n");
            break;
        }
    }

	close(client);
	return 0;
}

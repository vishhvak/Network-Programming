#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
	
    struct sockaddr_in servaddr;
    socklen_t size;
	int portnumber = 1877;

	// printf("Enter port number\n");
	// scanf("%d",&portnumber);
	//Enter port number - integer;

	int server = socket(AF_INET,SOCK_STREAM,0);
	//Check if socket is created or not;
	if (server == 0)
    {
        perror("Socket Failed");
        exit(0);
    }

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY); //host to network long
	servaddr.sin_port = htons(portnumber);
	
    int b = bind(server,(struct sockaddr*)&servaddr, sizeof(servaddr));
	//check if binded or not;
	
    if (b < 0)
    {
        perror("Bind failed\n");
        exit(0);
    }
    else
        printf("Socket Binded\n");

    printf("Listening for connections\n");
    int l = listen(server, 5);
    //listen for connection;
    if (l < 0)
    {
        perror("Listen");
        exit(0);
    }

    size = sizeof(servaddr);
    int client = accept(server, (struct sockaddr*)&servaddr, &size);
    
    //Check whether connection is accepted or not;
    if (client < 0)
    {
        perror("Accept");
        exit(0);
    }
    else
        printf("Connection Accepted, we are online and ready to chat!\n");

    char msg[1024], rcv[1024];

    while(1)
    {
        int r = recv(client, rcv, 1024, 0);

        if(r > 0)
            printf("\nClient : %s\n", rcv);
        
        if(strcmp("Bye", rcv)==0)
        {
            printf("\nClosing Chat\n");
            break;
        }
        
        printf("\nServer : ");
        fgets(msg, 1024, stdin);
        int s = send(client , msg , 1024 , 0 );
        if(s < 0)
            printf("\nFailed to send message to client!\n");
        
        if(strcmp("Bye",msg)==0)
        {
            printf("\nClosing Chat\n");
            break;
        }
    }

    close(client);
    close(server);

	return 0;
}

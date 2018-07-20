#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;
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
    else 
    	printf("\nConnection Successful!\n");
	close(csd);
	return 0;
}

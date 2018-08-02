#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

//Needs to be improvised with function specific code to make it neater


int main(){
	int clientSoc, portNum, nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	clientSoc = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(1334);
	serverAddr.sin_addr.s_addr = inet_addr("172.16.13.201");
	memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));
	addr_size = sizeof(serverAddr);
	int c = connect(clientSoc,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
	//check whether connection is done or not;
	if (c < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("\nConnection Established\n");
	//Card = 16 digits
	long long card;
	int pin,amt,op;
	/*//Message from Server for Connection and Card No.
	nBytes = recvfrom(clientSoc,buffer,1024,0,NULL, NULL);
	printf("%s\n",buffer);
	//Enter Card Details
	scanf("%ld",&card);
	int card_net = htonl(card);
	send(clientSoc, (const char*)&card_net, 16, 0);
	//Card Verification, Asking Pin
	nBytes = recvfrom(clientSoc,buffer,1024,0,NULL, NULL);
	printf("%s\n",buffer);
	//Send Pin
	scanf("%d",&pin);
	int pin_net = htonl(pin);
	send(clientSoc, (const char*)&pin_net, 3, 0);
	//Login success?
	nBytes = recvfrom(clientSoc,buffer,1024,0,NULL, NULL);
	printf("%s\n",buffer);*/
	//Menu and Transactions
	while(1){
		//Getting Menu
		nBytes = recvfrom(clientSoc,buffer,1024,0,NULL, NULL);
		printf("%s\n",buffer);
		//Scanning Option and sending
		scanf("%d",&op);
		int op_net = htonl(op);
		send(clientSoc, (const char*)&op_net, 1, 0);
		//Get Reply from Server for given option
		nBytes = recvfrom(clientSoc,buffer,1024,0,NULL, NULL);
		printf("%s\n",buffer);
		if(op==1 || op==2) {
			// Scan amount for deposit or withdraw
			scanf("%d",&amt);
			int amt_net = htonl(amt);
			send(clientSoc, (const char*)&amt_net, sizeof(amt_net), 0);
			//recieve updated balance
			nBytes = recvfrom(clientSoc,buffer,1024,0,NULL, NULL);
			printf("%s\n",buffer);
		}
		else if(op == 3) {
			// recieve balance info
			nBytes = recvfrom(clientSoc,buffer,1024,0,NULL, NULL);
			printf("%s\n",buffer);
		}
		else if(op == 4)
		// if exit option is chosen
			break;
	}
	//close(clientSoc);
	return 0;
}

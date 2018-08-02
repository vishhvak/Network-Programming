#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int sock, nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr, clientAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size, client_addr_size;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(1334);
	serverAddr.sin_addr.s_addr = inet_addr("172.16.13.201");
	memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));
	int b = bind(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	addr_size = sizeof(serverStorage);
	if (b < 0)
    {
        perror("Bind failed");
        exit(0);
    }
    int l = listen(sock, 3);
    //listen for connection;
    if (l < 0)
    {
        perror("Listen");
        exit(0);
    }
    int nsd = accept(sock, (struct sockaddr *)&clientAddr, &client_addr_size);
    //Check whether connection is accepted or not;
    if (nsd < 0)
    {
        perror("Accept");
        exit(0);
    }
    printf("Connection Established\n");
	char menu[] = "Enter an Option --- 1. Deposit  2. Withdraw  3. Balance  4. Exit";
	int opt, option,amt,balance = 0;
	while(1) {
		sendto(sock, menu,sizeof(menu),0,(struct sockaddr*)&serverStorage, addr_size);
		nBytes = recvfrom(sock,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
		recv(sock, &option, 1, 0);
		opt = ntohl(option);
		printf("Option Entered by Client is %d",opt);
		strcpy(buffer,"You have entered the option, thanks!");
		sendto(sock, buffer,sizeof(buffer),0,(struct sockaddr*)&serverStorage, addr_size);
		switch(opt) {
			case 1: 
				strcpy(buffer,"Enter amount to deposit");
				sendto(sock, buffer,sizeof(buffer),0,(struct sockaddr*)&serverStorage, addr_size);
				recv(sock, &amount, 1, 0);
				amt = ntohl(amount);
				balance+=amt;
				strcpy(buffer,"Balance is");
				sendto(sock, buffer,sizeof(buffer),0,(struct sockaddr*)&serverStorage, addr_size);
				break;
			case 2:
				strcpy(buffer,"Enter amount to withdraw");
				sendto(sock, buffer,sizeof(buffer),0,(struct sockaddr*)&serverStorage, addr_size);
				recv(sock, &amount, 1, 0);
				amt = ntohl(amount);
				balance-=amt;
				strcpy(buffer,"Balance is");
				sendto(sock, buffer,sizeof(buffer),0,(struct sockaddr*)&serverStorage, addr_size);
				break;
			case 3:
				strcpy(buffer,"Balance is");
				sendto(sock, buffer,sizeof(buffer),0,(struct sockaddr*)&serverStorage, addr_size);
				break;
			case 4:
				strcpy(buffer,"Exiting");
				sendto(sock, buffer,sizeof(buffer),0,(struct sockaddr*)&serverStorage, addr_size);
				break;
			default:
				break;
		}
	}
	close(sock);+
	return 0;
}

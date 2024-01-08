#include<sys/socket.h> //listening
#include<netdb.h> //provide network db operations
#include<unistd.h> //close the connection
#include<stdio.h> 
#include<string.h>
#include <arpa/inet.h>

int main()
{
	int sock,c;
	char str[100];
	char str2[100];
	struct sockaddr_in serv,cli;
	
	bzero(str,100);
	bzero(str2,100);
	bzero(&serv,sizeof(serv));
	c=sizeof(cli);
	
	sock=socket(AF_INET,SOCK_DGRAM,0);
	
	serv.sin_family=AF_INET;
	serv.sin_port=htons(12345);
	serv.sin_addr.s_addr=INADDR_ANY;
	
	bind(sock,(struct sockaddr *)&serv,sizeof(serv));
	
	//receving ip addr of client and the length of the client
	//cli stores client ip address
	while(1){
	recvfrom(sock,str,100,0,(struct sockaddr *)&cli,&c);
	printf("Client :%s",str);
	printf("You:");
	fgets(str2,100,stdin);
	sendto(sock,str2,strlen(str2),0,(struct sockaddr *)&cli,c);
	bzero(str2,100);
	}
	
	close(sock);
}

#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>

int main()
{
	int sockfd;
	int ret;
	char sendstr[100];
	char recvstr[100];
	struct sockaddr_in servaddr;
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	bzero(sendstr,100);
	bzero(recvstr,100);
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(21000);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	connect(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr));
	
	while(1)
	{
		printf("YOU : ");
		fgets(sendstr,100,stdin);
		send(sockfd,sendstr,sizeof(sendstr),0);
		recv(sockfd,recvstr,100,0);
		ret = strncmp(recvstr,"exit",4);
	if(ret==0){
		break;
	}
		printf("SERVER :%s",recvstr);	
	}
}

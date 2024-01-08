#include<stdio.h>
#include<netdb.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
	int sockfd;
	int sendarr[10];
	int recvarr[10];
	struct sockaddr_in servaddr;
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	bzero(recvarr,10);
	bzero(sendarr,10);
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(21000);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	printf("Enter 10 elements : \n");
	
	for(int i=0;i<10;i++){
		scanf("%d",&sendarr[i]);
	}
	send(sockfd,sendarr,sizeof(sendarr),0);
	recv(sockfd,recvarr,sizeof(recvarr),0);
	printf("SORTED ARRAY  :");
	for(int i=0;i<10;i++)
	{
		printf("%d ",recvarr[i]);
	}
	
	return 0;
	
}

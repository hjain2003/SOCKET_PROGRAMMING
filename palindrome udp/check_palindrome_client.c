#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<fcntl.h>
#include<arpa/inet.h>

int main()
{
	int listen_fd,len;
	int recvans;
	char sendstr[100];
	struct sockaddr_in servaddr;
	len=sizeof(servaddr);
	
	bzero(&servaddr,sizeof(servaddr));
	bzero(sendstr,100);
	bzero(&recvans,sizeof(int));
	
	listen_fd=socket(AF_INET,SOCK_DGRAM,0);
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	while(1)
	{
		printf("Enter string :");
		fgets(sendstr,sizeof(sendstr),stdin);
		sendstr[strlen(sendstr)-1]='\0';
		
		sendto(listen_fd,sendstr,sizeof(sendstr),0,(struct sockaddr *)&servaddr,len);
			recvfrom(listen_fd,&recvans,sizeof(recvans),0,(struct sockaddr *)&servaddr,&len);
		printf("%d",recvans);
		printf("\n");
		if(recvans==1){
			printf("string is paindrome");
			}
		else{
			printf("string is not palindrome");
		}			
	}
}

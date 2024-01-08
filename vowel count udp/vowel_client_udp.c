#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>

int main()
{
	int listen_fd,len;
	char strsend[100];
	char strrecv[100];
	struct sockaddr_in servaddr;
	
	bzero(strsend,100);
	bzero(strrecv,100);
	bzero(&servaddr,sizeof(servaddr));
	
	listen_fd=socket(AF_INET,SOCK_DGRAM,0);
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	len=sizeof(servaddr);
	
	while(1){
		printf("Enter string : ");
		fgets(strsend,sizeof(strsend),stdin);
		
		strsend[strlen(strsend)-1]='\0';
		sendto(listen_fd,strsend,sizeof(strsend),0,(struct sockaddr *)&servaddr,len);	
		
		recvfrom(listen_fd,strrecv,sizeof(strrecv),0,(struct sockaddr *)&servaddr,&len);
		
		printf("VOWELS : %s",strrecv);
		printf("\n");
	}
	close(listen_fd);
}







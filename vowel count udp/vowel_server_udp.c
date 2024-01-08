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
	int listen_fd,c;
	char strsend[100];
	char strrecv[100];
	struct sockaddr_in servaddr,cli;
	
	bzero(strsend,100);
	bzero(strrecv,100);
	bzero(&servaddr,sizeof(servaddr));
	c=sizeof(cli);
	
	listen_fd=socket(AF_INET,SOCK_DGRAM,0);
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=INADDR_ANY;
	
	bind(listen_fd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	while(1){
		recvfrom(listen_fd,strrecv,sizeof(strrecv),0,(struct sockaddr *)&cli,&c);
		
		
		char vowels[100];
		bzero(vowels,100);
		int count=0;
		for(int i=0;strrecv[i]!='\0';i++)
		{
			char ch=strrecv[i];
			if(ch=='a' || ch=='i' || ch=='e' || ch=='o' || 			ch=='u'){
				vowels[count++]=ch;
			}
		}	
		vowels[count]='\0';
		
		sendto(listen_fd,vowels,sizeof(vowels),0,(struct sockaddr *)&cli,c);
	}
	close(listen_fd);
}

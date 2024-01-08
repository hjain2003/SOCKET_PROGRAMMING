#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<string.h>

int main()
{
	int listen_fd,c;
	char recvstr[100];
	struct sockaddr_in servaddr,cli;
	c=sizeof(cli);
	
	bzero(&servaddr,sizeof(servaddr));
	bzero(recvstr,100);
	
	listen_fd=socket(AF_INET,SOCK_DGRAM,0);
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=INADDR_ANY;
	
	bind(listen_fd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	while(1)
	{	
		recvfrom(listen_fd,recvstr,sizeof(recvstr),0,(struct sockaddr *)&cli,&c);
		
		int low=0;
		int high=strlen(recvstr)-1;
		int ans=1;
		
		while(low<high && recvstr[0]!='\0' && recvstr[high]!='\0'){
			if(recvstr[low]!=recvstr[high]){
				ans=0;	
				break;
			}
			else{
			low++;
			high--;			
			}
		}
		
		sendto(listen_fd,&ans,sizeof(int),0,(struct sockaddr *)&cli,c);
		if(ans==0)
			printf("non-pali");
		else
			printf("pali");
	}
	close(listen_fd);
}

#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int ret;
	char sendstr[100];
	char recvstr[100];
	int listen_fd,comm_fd;
	struct sockaddr_in servaddr;
	
	listen_fd=socket(AF_INET,SOCK_STREAM,0);
	
	bzero(sendstr,100);
	bzero(recvstr,100);
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family =AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(21000);
	
	bind(listen_fd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	listen(listen_fd,5);
	
	comm_fd=accept(listen_fd,(struct sockaddr *)NULL,NULL);
	
	while(1){	
	recv(comm_fd,recvstr,100, 0);
	ret = strncmp(recvstr,"exit",4);
	if(ret==0){
		break;
	}
	printf("CLIENT : %s",recvstr);
	printf("YOU :");
	fgets(sendstr,100,stdin);
	send(comm_fd, sendstr,sizeof(sendstr),0);
	bzero(sendstr,100);
	}
	close(comm_fd);
}

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<math.h>

int main()
{
	int listen_fd,c;
	int x,y,z;
	float result1,result2;
	struct sockaddr_in servaddr,cli;
	c=sizeof(servaddr);
	
	bzero(&servaddr,sizeof(servaddr));
	
	listen_fd=socket(AF_INET,SOCK_DGRAM,0);
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=INADDR_ANY;
	
	
	bind(listen_fd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	while(1)
	{
		recvfrom(listen_fd,&x,sizeof(int),0,(struct sockaddr *)&cli,&c);
		recvfrom(listen_fd,&y,sizeof(int),0,(struct sockaddr *)&cli,&c);
		recvfrom(listen_fd,&z,sizeof(int),0,(struct sockaddr *)&cli,&c);
		result1 = (-y + sqrt(y*y-4*x*z))/(2*x);
		result2 = (-y - sqrt(y*y-4*x*z))/(2*x);
		printf("%f",result1);
		printf("%f",result2);
		sendto(listen_fd,&result1,sizeof(int),0,(struct sockaddr *)&cli,c);
			sendto(listen_fd,&result2,sizeof(int),0,(struct sockaddr *)&cli,c);
		
	}
	close(listen_fd);
	
}

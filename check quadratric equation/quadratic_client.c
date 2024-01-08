#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int listen_fd,len;
	struct sockaddr_in servaddr;
	len=sizeof(servaddr);
	
	listen_fd=socket(AF_INET,SOCK_DGRAM,0);
	
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	while(1)
	{
		int a,b,c;
		float result1,result2;
		bzero(&result1,sizeof(int));
		bzero(&result2,sizeof(int));
		printf("Enter a :");
		scanf("%d",&a);
		printf("Enter b :");
		scanf("%d",&b);
		printf("Enter c :");
		scanf("%d",&c);
		
		sendto(listen_fd,&a,sizeof(int),0,(struct sockaddr *)&servaddr,len);
		sendto(listen_fd,&b,sizeof(int),0,(struct sockaddr *)&servaddr,len);
		sendto(listen_fd,&c,sizeof(int),0,(struct sockaddr *)&servaddr,len);
				
		recvfrom(listen_fd,&result1,sizeof(int),0,(struct sockaddr *)&servaddr,&len);
		recvfrom(listen_fd,&result2,sizeof(int),0,(struct sockaddr *)&servaddr,&len);
		printf("\n");
		printf("ROOT 1 %f:",result1);
		printf("ROOT 2 %f:",result2); 

	}
}

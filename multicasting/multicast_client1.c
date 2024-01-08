#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>

int main()
{
	int r=1,sock;
	struct sockaddr_in serv;
	char str[100];
	bzero(&serv,sizeof(serv));
	
	sock=socket(AF_INET,SOCK_DGRAM,0);
	
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&r,sizeof(r));
	
	serv.sin_family=AF_INET;
	serv.sin_port=htons(12345);
	serv.sin_addr.s_addr=INADDR_ANY; //CAN ALSO USE 255.255.255.255
	
	bind(sock, (struct sockaddr *)&serv,sizeof(serv));
	
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr=inet_addr("224.1.1.1");
	mreq.imr_interface.s_addr=INADDR_ANY;
	
	while(1)
	{
		bzero(str,100);
		recvfrom(sock,str,100,0,(struct sockaddr *)NULL,NULL);
		printf("%s",str);
	}
	close(sock);
}

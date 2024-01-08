#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>

int main()
{
	int b=1; //for broadcasting, size is 4
	int sock;
	char str[100],str2[10];
	struct sockaddr_in serv;
	
	bzero(&serv,sizeof(serv));
	
	sock=socket(AF_INET,SOCK_DGRAM,0);
	
	serv.sin_family=AF_INET;
	serv.sin_port=htons(12345);
	serv.sin_addr.s_addr=inet_addr("224.1.1.1"); //server will broadcast on this address, its not listening like before
	
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr=inet_addr("224.1.1.1");
	mreq.imr_interface.s_addr=INADDR_ANY;
	
	setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
	
	while(1)
	{
		printf("do you want to send data?");
		fgets(str2,10,stdin);
		if(strncmp(str2,"yes",3)==0)
		{
			bzero(str,100);
			printf("Enter the string :");
			fgets(str,100,stdin);
			sendto(sock,str,sizeof(str),0,(struct sockaddr *)&serv,sizeof(serv)); 
		}
		else
		{
			break;
		}
	}
	close(sock);	
}

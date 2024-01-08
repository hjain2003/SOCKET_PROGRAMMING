#include<sys/socket.h> //listening
#include<netdb.h> //provide network db operations
#include<fcntl.h> //open the connection
#include<unistd.h> //close the connection
#include<stdio.h> 
#include<string.h>
#include <arpa/inet.h>

int main()
{
	int sock,len;
	char str1[100],str2[100];
	struct sockaddr_in serv;
	
	bzero(str1,100);
	bzero(str2,100);
	bzero(&serv,sizeof(serv));
	
	sock=socket(AF_INET,SOCK_DGRAM,0);
	
	serv.sin_family=AF_INET;
	serv.sin_port=htons(12345);
	serv.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	len=sizeof(serv);
	while(1){
	printf("You: ");
	fgets(str1,100,stdin);
	sendto(sock,str1,strlen(str1),0,(struct sockaddr *)&serv,len);
	recvfrom(sock,str2,100,0,(struct sockaddr *)&serv,&len);
	printf("Server : %s",str2);
	}
	
	close(sock);
}

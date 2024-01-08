#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<fcntl.h>

void bubble_sort(int arr[],int n)
{
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(arr[j]>arr[j+1]){
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}
int main()
{
	int recvarr[10];
	int sendarr[10];
	int listen_fd,comm_fd;
	struct sockaddr_in servaddr;
	
	listen_fd=socket(AF_INET,SOCK_STREAM,0);
	
	bzero(recvarr,10);
	bzero(sendarr,10);
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(21000);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	bind(listen_fd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	listen(listen_fd,5);
	
	comm_fd=accept(listen_fd,(struct sockaddr *)NULL,NULL);
	
	recv(comm_fd,recvarr,sizeof(recvarr),0);
	printf("RECEIVED ARRAY  : ");
	for(int i=0;i<10;i++){
		printf("%d ",recvarr[i]);
	}
	bubble_sort(recvarr,10);
	printf("\n");
	printf("SORTED ARRAY : ");
	for(int i=0;i<10;i++){
		printf("%d ",recvarr[i]);
	}
	send(comm_fd,recvarr,sizeof(recvarr),0);
	
	
	close(comm_fd);
	
}

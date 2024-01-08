#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>

void merge(int arr[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], R[n2];

  for (i = 0; i < n1; i++) {
    L[i] = arr[l + i];
  }
  for (j = 0; j < n2; j++) {
    R[j] = arr[m + 1 + j];
  }

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
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
	mergeSort(recvarr,0,9);
	printf("\n");
	printf("SORTED ARRAY : ");
	for(int i=0;i<10;i++){
		printf("%d ",recvarr[i]);
	}
	send(comm_fd,recvarr,sizeof(recvarr),0);
	
	
	close(comm_fd);
}

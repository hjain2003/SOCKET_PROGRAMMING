#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <stdio.h>

int main() {
  int n = 0;
  int target = 0;
  int found = 0;
  int arr[100];
  int sockfd, commfd;
  struct sockaddr_in servaddr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(arr, sizeof(arr));
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;       // IPv4
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //localhost
  servaddr.sin_port = htons(21000);

  connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  
  printf("CLient Started!\n");

  while (1) {
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    printf("Enter the array elements in sorted order: ");
    for (int i = 0; i < n; i++) {
      scanf("%d", &arr[i]);
    }
    printf("Enter the element to be searched: ");
    scanf("%d", &target);

    send(sockfd, &n, sizeof(int), 0);
    send(sockfd, &arr, sizeof(arr), 0);
    send(sockfd, &target, sizeof(int), 0);

    recv(sockfd, &found, sizeof(int), 0);

    printf("The element is found at index %d\n", found);

    bzero(&arr, sizeof(arr));
  }
}


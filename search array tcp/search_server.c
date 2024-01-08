#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <stdio.h>

int binary_search(int arr[], int n, int target) {
  int l = 0;
  int r = n - 1;

  while (l <= r) {
    int mid = (l + r) / 2;
    if (arr[mid] == target) {
      return mid;
    } else if (target < arr[mid]) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }

  return -1;
}

int main() {
  int sockfd, commfd;
  struct sockaddr_in servaddr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;       // IPv4
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(21000);

  bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

  listen(sockfd, 5);

  commfd = accept(sockfd, (struct sockaddr*)NULL, NULL);
  
  printf("Server Started!\n");

  while (1) {
    int n = 0;
    int target = 0;
    int found = 0;
    int arr[100];
  
    bzero(arr, sizeof(arr));
    
    recv(commfd, &n, sizeof(int), 0);
    recv(commfd, &arr, sizeof(arr), 0);
    recv(commfd, &target, sizeof(int), 0);

    found = binary_search(arr, n, target);

    send(commfd, &found, sizeof(found), 0);

    bzero(&arr, sizeof(arr));
  }
}


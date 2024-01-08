#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(21000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while (1) {
        int num[100];
        int n;
        int i;
        
        printf("Enter the number of elements in the array: ");
        scanf("%d", &n);
        printf("Enter the array elements: \n");
        for(i=0;i<n;i++){
        	scanf("%d", &num[i]);
        }

        // Send the size and array numbers to the server
        send(sockfd, &n, sizeof(int), 0);
        send(sockfd, &num, sizeof(num), 0);

        int result[100];

        // Receive the result from the server
        recv(sockfd, &result, sizeof(result), 0);
        printf("Sorted Array: ");
        for(i=0;i<n;i++)
        {
        	printf("%d ",result[i]);
        }
        printf("\n");
    }

    close(sockfd);
}


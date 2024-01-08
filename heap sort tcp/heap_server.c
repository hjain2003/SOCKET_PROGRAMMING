#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void heapify(int array[], int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && array[left] > array[largest]) {
    largest = left;
  }

  if (right < n && array[right] > array[largest]) {
    largest = right;
  }

  if (largest != i) {
    int temp = array[i];
    array[i] = array[largest];
    array[largest] = temp;

    heapify(array, n, largest);
  }
}

void heap_sort(int array[], int n) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(array, n, i);
  }

  for (int i = n - 1; i >= 0; i--) {
    int temp = array[0];
    array[0] = array[i];
    array[i] = temp;

    heapify(array, i, 0);
  }
}

int main()
{
    char str[100];
    int listen_fd, comm_fd;
    struct sockaddr_in servaddr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;       // IPv4
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(21000);

    bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listen_fd, 5);

    comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);

    while (1) {
        int a[100];
        int n = 0;

        // Receive two numbers from the client
        recv(comm_fd, &n, sizeof(int), 0);
        recv(comm_fd, &a, sizeof(a), 0);

        heap_sort(a,n);

        // Send the sum back to the client
        send(comm_fd, &a, sizeof(a), 0);
    }

    close(comm_fd);
}


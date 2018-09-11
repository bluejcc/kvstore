// A simple server using TCP.

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage %s <port>\n", argv[0]);
    exit(0);
  }

  int port = atoi(argv[1]);

  int server_fd;
  if ((server_fd = socket(AF_INET, SOCK_STREAM, /* protocol */ 0)) < 0) {
    printf("Error opening socket: %d\n", errno);
    exit(1);
  }

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(port);
  if (bind(server_fd,
           (struct sockaddr *) &server_address,
           sizeof(server_address)) < 0) {
    printf("Error on binding: %d\n", errno);
    exit(1);
  }

  listen(server_fd, /* backlog */ 5);

  struct sockaddr_in client_address;
  socklen_t client_address_socklen = sizeof(client_address);
  int new_socket;
  if ((new_socket = accept(server_fd,
                           (struct sockaddr *) &client_address,
                           &client_address_socklen)) < 0) {
    printf("Error accepting: %d\n", errno);
    exit(1);
  } else {
    //write(new_socket, "1", 1);
  }

  char buffer[1024] = {0};
  int ret;
  if ((ret = read(new_socket, buffer, 1023)) < 0) {
    printf("Error reading from socket.\n");
  }
  printf("From client: %s\n", buffer);
  if ((ret = write(new_socket, "hey from server", 15)) < 0) {
    printf("Error writing to socket.\n");
  }
  close(new_socket);
  close(server_fd);
  fflush(stdout);
  return 0;
}

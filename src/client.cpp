#include <arpa/inet.h>
#include <cstring>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(0);
  }
  int port = atoi(argv[1]);

  int sock_fd;
  if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Error opening socket:%d \n", errno);
    exit(1);
  }

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);

  if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
    printf("Invalid address\n");
    exit(1);
  }

  if (connect(sock_fd, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) {
    printf("Error connecting\n");
    exit(1);
  }
  char buffer[1024];
  if (1) {
  bzero(buffer, 1024);
  printf("Msg to send: ");
  fgets(buffer, 1023, stdin);
  printf("Sending to server...\n");
  if (write(sock_fd, buffer, strlen(buffer)) < 0) {
    printf("Error writing to socket\n");
  }
  bzero(buffer, 1024);
  if (read(sock_fd, buffer, 1023) < 0) {
    printf("Error reading from socket\n");
  }
  printf("From server: %s\n", buffer);
  close(sock_fd);
  }
  fflush(stdout);
  return 0;
}

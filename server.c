#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>

#define PORT 8080
#define IP "127.0.0.1"
#define BUFFER_SIZE 1024
#define PROTOCOL_FAMILY AF_INET
#define SOCKET_TYPE SOCK_DGRAM
#define EXIT_MESSAGE "Exit"
#define SUCCESS_MESSAGE "Received"

bool oparate_message(char *buffer, size_t lenght_of_message) {
  // Deep copy of the message in case of use of multithreading.
  char* message = malloc(lenght_of_message);
  memcpy(message, buffer, lenght_of_message);
  printf("Message from client: %s\n", message);
  bool keep_running = strcmp(message, EXIT_MESSAGE) != 0;
  free(message);
  return keep_running;
}

int main (int argc, char *argv[]){
  int sock_fd = socket(PROTOCOL_FAMILY, SOCKET_TYPE, 0);
  
  if (sock_fd < 0) {
    int error = errno;
    printf("Socket function error: %s\n", strerror(error));
    return 1;
  }

  struct sockaddr_in server_address;
  socklen_t server_address_length = sizeof(server_address);

  memset(&server_address, '\0', sizeof(server_address));

  server_address.sin_family = PROTOCOL_FAMILY;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = inet_addr(IP);

  if (bind(sock_fd, (struct sockaddr*)& server_address, server_address_length) < 0) {
    int error = errno;
    printf("Bind function error: %s\n", strerror(error));
    return 1;
  }

  char* buffer = malloc(BUFFER_SIZE);
  struct sockaddr_in client_address;
  socklen_t client_address_length = sizeof(client_address);

  bool keep_running = true;
  printf("Server is running...\n");
  while (keep_running) {
    explicit_bzero(buffer, BUFFER_SIZE);

    int lenght_of_message = recvfrom(sock_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)& client_address, &client_address_length);
    
    if (lenght_of_message < 0) {
      int error = errno;
      printf("Recvfrom function error: %s\n", strerror(error));
      printf("Error produced while processing request of %s.\n", inet_ntoa(client_address.sin_addr));
      return 1;
    }

    keep_running = oparate_message(buffer, lenght_of_message);

    if(!keep_running) {
      printf("Server is shutting down...\n");
      continue;
    }

    explicit_bzero(buffer, BUFFER_SIZE);
    memcpy(buffer, SUCCESS_MESSAGE, strlen(SUCCESS_MESSAGE));

    if(sendto(sock_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)& client_address, client_address_length) < 0){
      int error = errno;
      printf("Sendto function error: %s\n", strerror(error));
      printf("Error produced while processing response of %s.\n", inet_ntoa(client_address.sin_addr));
      return 1;
    }

  }

  free(buffer);
  if(close(sock_fd) < 0) {
    int error = errno;
    printf("Close function error: %s\n", strerror(error));
    return 1;
  }

  return 0;
}

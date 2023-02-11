#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define PORT 8080
#define IP "127.0.0.1"
#define BUFFER_SIZE 1024
#define PROTOCOL_FAMILY AF_INET
#define SOCKET_TYPE SOCK_DGRAM
#define EXIT_MESSAGE "Exit"

int main (int argc, char *argv[]){
  if(argc != 2){
    printf("Please enter a message for the server.\n");
    return 1;
  }
  size_t lenght_of_message = strlen(argv[1]);
  char* user_message = malloc(lenght_of_message);
  memcpy(user_message, argv[1], strlen(argv[1]));

  int sock_fd = socket(PROTOCOL_FAMILY, SOCKET_TYPE, 0);
  
  if (sock_fd < 0) {
    int error = errno;
    printf("Socket function error: %s\n", strerror(error));
    return 1;
  }

  struct sockaddr_in server_address;
  socklen_t server_address_lenght = sizeof(server_address);

  memset(&server_address, '\0', sizeof(server_address));

  server_address.sin_family = PROTOCOL_FAMILY;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = inet_addr(IP);

  char* buffer = malloc(BUFFER_SIZE);

  srand(time(NULL));
  int random_number_of_request = (rand() % 10) + 1; 

  for(int i = 0; i < random_number_of_request; i++){
    explicit_bzero(buffer, BUFFER_SIZE);
    memcpy(buffer, user_message, strlen(user_message));

    int lenght_of_request_message = sendto(sock_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)& server_address, server_address_lenght);

    if (lenght_of_request_message < 0) {
      int error = errno;
      printf("Sendto function error: %s\n", strerror(error));
      return 1;
    }

    int lenght_of_response = recvfrom(sock_fd, buffer, BUFFER_SIZE, 0, NULL, NULL);

    if (lenght_of_response < 0) {
      int error = errno;
      printf("Recvfrom function error: %s\n", strerror(error));
      return 1;
    }

    char* response = malloc(lenght_of_response);
    memcpy(response, buffer, lenght_of_response);
    printf("Server response: %s\n", response);

    if (strcmp(response, EXIT_MESSAGE) == 0) {
      printf("Server has exited.\n");
      free(response);
      return 1;
    }
    
    free(response);
  }

  explicit_bzero(buffer, BUFFER_SIZE);
  memcpy(buffer, EXIT_MESSAGE, strlen(EXIT_MESSAGE));

  int lenght_of_exit = sendto(sock_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)& server_address, server_address_lenght);

  if ( lenght_of_exit < 0) {
    int error = errno;
    printf("Sendto function error: %s\n", strerror(error));
    return 1;
  }

  free(user_message);
  free(buffer);

  if(close(sock_fd) < 0) {
    int error = errno;
    printf("Close function error: %s\n", strerror(error));
    return 1;
  }
  
  return 0;
}

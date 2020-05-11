#include <signal.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <iostream>

  int server_fd = 0;

void ctrlc_handler(int s)
{
  printf("Got Ctrl-c\nExiting.\n");
  close(server_fd);
  exit(1);
}

int publishFile(std::string filename, char* buffer)
{
 char* payload = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello World!\0";
 buffer = new char[76];
 printf("strlen [%d]\n", strlen(payload));
 memcpy(buffer, &payload, strlen(payload));
 printf("Created buffer [%s]\n", buffer);
 return 1;
}

static const int PORT = 8080;

int main()
{
  std::cout << "Starting server on port : " << PORT << std::endl;
  signal(SIGINT, ctrlc_handler);
  signal(SIGSEGV, ctrlc_handler);

  int new_socket = 0;
  long valread = 0;

  struct sockaddr_in address;
  int addrlen = sizeof(address);

  char *response;// = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello World!";

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    perror("When creating socket");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons ( PORT );

  memset(address.sin_zero, '\0', sizeof address.sin_zero);

  if (bind(server_fd, (struct sockaddr*)&address, sizeof(address))<0)
  {
    perror("When binding to socket.");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 10) < 0)
  {
    perror("When listening on port.");
    exit(EXIT_FAILURE);
  }

  while(true)
  {
    printf("\nWaiting for connection.\n");
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen))<0)
    {
      perror("In accept.");
      exit(EXIT_FAILURE);
    }

    char buffer[30000] = {0};
    valread = read(new_socket, buffer, 30000);
    printf("Buffer: \n %s \n", buffer);
    if (publishFile("index.html", response))
    {
      write(new_socket, response, strlen(response));
      printf("Sendt response : \n %s \n", response);
    }
    else 
    {
      printf("Error sending file\n");
    }
    close(new_socket);

  }
  close(server_fd);
  return 0;
}

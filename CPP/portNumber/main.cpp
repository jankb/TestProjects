
#include <iostream>
#include <memory.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "unistd.h"

struct sockaddr_in myaddr;
struct sockaddr_in broadcastAddr;
int fd = 0;

int setup()
{
  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("Cannot create socket.");
    return 0;
  }


  memset((char*)&myaddr, 0, sizeof(myaddr));

  myaddr.sin_family = AF_INET;
  myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myaddr.sin_port = htons(5004);


  if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
  {
    perror("Cannot bind..");
    return 0;
  }


  memset((char*)&broadcastAddr, 0, sizeof(broadcastAddr));
  broadcastAddr.sin_family=AF_INET;
  broadcastAddr.sin_port = htons(5004);

  inet_pton(AF_INET, "192.168.1.75", &(broadcastAddr.sin_addr));


}


int main()
{
  std::cout << "Starting ..." << std::endl;
  setup();
  char* message = "Hello world...";
  while (true)
  {
    std::cout << "Sending..." << std::endl;
    if (sendto(fd, message, strlen(message), 0, (struct sockaddr*)&broadcastAddr, sizeof(broadcastAddr)) < 0)
    {
      perror("send failed");
      return 0;
    }
    sleep(1);
  }

  return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void scanPort(char * ip, int port) 
{
  int mysocket = socket(AF_INET, SOCK_STREAM, 0);

  if (mysocket == -1) {
    printf("Erreur lors du scan de port  : %d", port);
  }

  struct sockaddr_in socketAddress;

  socketAddress.sin_family = AF_INET;
  socketAddress.sin_port = htons(port);
  socketAddress.sin_addr.s_addr = inet_addr(ip);
  int result = connect(mysocket, (struct sockaddr * ) & socketAddress, sizeof(socketAddress));

  if (result == 0) {
    printf("Port %d is open\n", port);
  }
  close(mysocket);

}

int main(int argc, char * argv[]) 
{
  if (argc != 3) {
    printf("Usage: %s <ip_address> <port>\n", argv[0]);
    return 1;
  }

  char * ip = argv[1];
  int port_range = atoi(argv[2]);

  for (int i = 0; i < port_range; i++) {
    scanPort(ip, i);
  }

  return 0;
}

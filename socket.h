#ifndef _SOCKET_
#define _SOCKET_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#include "game.h"

// define the buffer size for receiving messages
#define BUFFERSIZE 1024

// define a list of ports for communication
#define PORTS {5050, 5051, 5052, 5053}

// define a list of IPs for communication
#define IPS {"192.168.0.1", "192.168.0.2", "192.168.0.3", "192.168.0.4"}

// define a structure to hold player socket information
typedef struct player_socket_t {
  int id;              // unique identifier for the player
  int sockfd;          // file descriptor for the socket
  int recv_port;       // port number for receiving messages
  int send_port;       // port number for sending messages
  char *recv_ip;
  char *send_ip;
  struct sockaddr_in recvaddr;  // address structure for receiving messages
  struct sockaddr_in sendaddr;  // address structure for sending messages
} player_socket_t;

player_socket_t* init_player_socket (int ports[], player_t* player, char *ips[]);

void send_msg (player_socket_t* p_socket, const char* msg);

int recv_msg (player_socket_t* p_socket);

#endif
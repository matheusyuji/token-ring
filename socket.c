#include "socket.h"

// allocates memory for a player_socket_t structure 
player_socket_t* allocate_player_socket () {
  player_socket_t* p_socket = malloc(sizeof(player_socket_t));

  if (!p_socket) {
    perror("error allocating player socket\n");
    exit(EXIT_FAILURE);
  }
  return p_socket;
}

// creates a UDP socket
int create_socket () {
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  if (sockfd < 0) {
    perror("error creating socket\n");
    exit(EXIT_FAILURE);
  }
  return sockfd;
}

// configures a sockaddr_in structure
void configure_address (struct sockaddr_in *addr, int port, char *ips) {
  memset(addr, 0, sizeof(*addr));
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = INADDR_ANY;
  addr->sin_port = htons(port);
}

// binds the socket to the specified address and port
int bind_socket (int sockfd, struct sockaddr_in *addr) {
  int rc = bind(sockfd, (const struct sockaddr *)addr, sizeof(*addr));

  if (rc < 0) {
    perror("unable to connect socket to address\n");
    exit(EXIT_FAILURE);
  }
  return 0;
}

// initializes a player_socket_t structure
player_socket_t* init_player_socket (int ports[], player_t* player, char *ips[]) {
  player_socket_t* p_socket = allocate_player_socket();

  p_socket->recv_port = ports[player->id];
  p_socket->send_port = ports[player->next_id];

  p_socket->recv_ip = ips[player->id];
  p_socket->send_ip = ips[player->next_id];

  p_socket->sockfd = create_socket();
  configure_address (&(p_socket->recvaddr), p_socket->recv_port, p_socket->recv_ip);
  bind_socket(p_socket->sockfd, &(p_socket->recvaddr));
  configure_address (&(p_socket->sendaddr), p_socket->send_port, p_socket->send_ip);

  return p_socket;
}

// sends a message to the configured address
void send_msg (player_socket_t* p_socket, const char* msg) {
  if (sendto(p_socket->sockfd, msg, strlen(msg), 0, (struct sockaddr *)&p_socket->sendaddr, sizeof(p_socket->sendaddr)) == -1) {
    perror("failed to send message\n");
  }
}

// receives a message from the configured address
int recv_msg (player_socket_t* p_socket) {
  char buffer[BUFFERSIZE];
  memset(buffer, 0, BUFFERSIZE);
  int len = sizeof(p_socket->recvaddr);

  int n = recvfrom(p_socket->sockfd, (char *)buffer, BUFFERSIZE-1, MSG_WAITALL, (struct sockaddr*)&p_socket->recvaddr, &len);
  buffer[n] = '\0';
  printf("received message: %s\n", buffer);

  return n;
}
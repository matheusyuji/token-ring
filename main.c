#include "game.h"
#include "socket.h"

int main (int argc, char **argv) {

  int player_id = parse_id_from_args(argc, argv);
  player_t *player = init_player(player_id);

  int ports[] = PORTS;
  char *ips[] = IPS;

  player_socket_t* p_socket = init_player_socket(ports, player, ips);

  char buffer[BUFFERSIZE];
  if (player_id == 0) {
    snprintf(buffer, BUFFERSIZE, "hello from player %d", player_id);
    send_msg(p_socket, buffer);
  }

  while (1) {
    recv_msg(p_socket); 

    snprintf(buffer, BUFFERSIZE, "hello from player %d", player_id);
    send_msg(p_socket, buffer);

    sleep(1); 
  }

  close(p_socket->sockfd);
  free(player);
  free(p_socket);

  return 0;
}
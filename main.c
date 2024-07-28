#include "game.h"
#include "socket.h"

int main (int argc, char **argv) {

  int player_id = parse_id_from_args(argc, argv);
  player_t *player = init_player(player_id);

  int ports[] = PORTS;
  player_socket_t* p_socket = init_player_socket(ports, player);

  if (player_id == 0) {
    char *hello = "hello from client";
    send_msg (p_socket, hello);
  }
  else {
    recv_msg (p_socket);
  }

  return 0;
}
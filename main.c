#include "game.h"
#include "socket.h"
#include "message.h"
#include "card.h"

int main (int argc, char **argv) {

  int player_id = parse_id_from_args(argc, argv);
  player_t *player = init_player(player_id);

  int ports[] = PORTS;
  char *ips[] = IPS;

  player_socket_t* p_socket = init_player_socket(ports, player, ips);

  message_t* msg = create_message ();
  if (player_id == 0) {
   
    player->baton = 1;
   
  }

  while (1) {
    if (player->baton == 1) {
      init_message(msg, player, 'P');
      send_msg(p_socket, msg);
      send_baton(p_socket, player);
    } else  {
      recv_msg(p_socket, msg);
      
      process_msg(msg, player);
    }
  }
  
  //card_t* deck = NULL;
  //criarBaralhoCompleto(&deck);
  //imprimir_deck(deck);
  //liberarBaralho(deck);


  close(p_socket->sockfd);
  free(player);
  free(p_socket);

  return 0;
}
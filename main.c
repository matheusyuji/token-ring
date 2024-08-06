#include <stdio.h>

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
      init_message(msg, player, 'P', NULL);
      send_msg(p_socket, msg);
      send_baton(p_socket, player);
    } else  {
      recv_msg(p_socket, msg);
      
      process_msg(msg, player);
    }
  }
  
  implime_regra();

//  if(player_id == 0){                        //só o player 0 cria o baralho (para não criar 4 baralhos)
  Deck_t* deck = NULL;
  criarBaralhoCompleto(&deck); 
//  }

/*
  int game = 1;
  int ROUND = 1;                                //0 = OFF   1 = ON
  int palpite, palp;                                
  while(game){                                //inicio do jogo
    Shuffle_deck(deck);                         //embaralha as cartas

    for(int i = 0; i < ROUND; i++){             //distribuias cartas
      if(player->baton == 1){                   //ainda tem que configurar destino correto dos jogadores
        init_message(msg, player, 'B', deck);
        send_msg(p_socket,msg);
        send_baton(p_socket, player);
      }
      else{
        recv_msg(p_socket, msg);
        process_msg(msg, player);
      }
    }

    card_t* manilha = deck->Deck[deck->total];  //escolhe a manilha do deck
    deck->total--;

    scanf("%d", &palpite);
    //printar o palpite de cada jogador para todo mundo
    palp = 1;
    while(palp){
    }

    //iniciar as jogadas

    game = 0;                                   //encerra o jogo
  }
*/
  imprimir_deck(deck);
  liberarBaralho(deck);


  close(p_socket->sockfd);
  free(player);
  free(p_socket);

  return 0;
}
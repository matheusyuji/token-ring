#include "message.h"
#include "game.h"
#include "card.h"

//  create a new message
message_t* create_message () {
  message_t* msg = malloc(sizeof(message_t));
  
  if (!msg) {
    perror("error creating message\n");
    exit(EXIT_FAILURE);
  }
  msg->origin = 0;
  msg->dest = 0;
  msg->type = '0';
  msg->card.numero = 0;
  msg->card.tipo = 0;
}

// initialize a message with player information
void init_message (message_t* msg, player_t* player, char type, Deck_t* D) {
  msg->origin = player->id;
  msg->dest = player->next_id;
  msg->type = type;
  if(type == TYPE_BATON)
    Draw_card(D, msg->card);
}

// sends a message to the configured address
void send_msg (player_socket_t* p_socket, message_t* msg) {
  int n = sendto(p_socket->sockfd, msg, sizeof(message_t), MSG_CONFIRM, (struct sockaddr *)&p_socket->sendaddr, sizeof(p_socket->sendaddr));
  if (n < 0) {
    perror("failed to send message\n");
    exit(EXIT_FAILURE);
  }   
}

// receives a message from the configured address
void recv_msg (player_socket_t* p_socket, message_t* msg) {

  socklen_t len = sizeof(struct  sockaddr_in);
  int n = recvfrom(p_socket->sockfd, msg, sizeof(message_t), MSG_WAITALL, (struct sockaddr*)&p_socket->recvaddr, &len);
  if (n < 0) {
    perror("failed to recv message\n");
    exit(EXIT_FAILURE);
  }
}

// send a baton to the next player
void send_baton (player_socket_t* p_socket, player_t* player) {
  message_t* msg = create_message();
  msg->origin = player->id;
  msg->dest = player->next_id;
  msg->type = TYPE_BATON;
  player->baton = 0;

  send_msg(p_socket, msg);
}

// process a received message
void process_msg (message_t* msg, player_t* player) {
  switch (msg->type)
  {
  case TYPE_BATON:
    player->baton = 1;
    printf ("player baton: %d\n", player->baton);
    break;
  
  case TYPE_PRINT:
    if (player->id == msg->dest)
      if(msg->card.tipo == 0)   printf ("Receive msg from %d to %d, type=%c and card= Spade :", msg->origin, msg->dest, msg->type);
      else if(msg->card.tipo == 1)  printf ("Receive msg from %d to %d, type=%c and card= Club :", msg->origin, msg->dest, msg->type);
      else if(msg->card.tipo == 2)  printf ("Receive msg from %d to %d, type=%c and card= Heart :", msg->origin, msg->dest, msg->type);
      else printf ("Receive msg from %d to %d, type=%c and card= Diamond :", msg->origin, msg->dest, msg->type);

      if(msg->card.numero == 11)  printf(" Jack\n");
      else if(msg->card.numero == 12) printf(" Queen\n");
      else if(msg->card.numero == 13) printf(" King\n");
      else printf(" %d\n");
    break;
    
  default:
    break;
  }
}
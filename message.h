#ifndef _MESSAGE_
#define _MESSAGE_

#include "socket.h"

#define TYPE_BATON 'B'
#define TYPE_PRINT 'P'

typedef struct message_t {
  int origin;
  int dest;
  char type;
  int num_cards;
} message_t;

message_t* create_message ();

void init_message (message_t* msg, player_t* player, char type);

void send_msg (player_socket_t* p_socket, message_t* msg);

void recv_msg (player_socket_t* p_socket, message_t* msg);

void send_baton (player_socket_t* p_socket, player_t* player);

void process_msg (message_t* msg, player_t* player);

#endif

#ifndef _GAME_
#define _GAME_

#include <stdio.h>
#include <stdlib.h>

// define a structure to hold player information
typedef struct player_t {
  int id;       // unique identifier for the player
  int next_id;  // identifier of the next player
  int baton;
  int life;
} player_t;

int parse_id_from_args (int argc, char **argv);

player_t* init_player(int id);

#endif
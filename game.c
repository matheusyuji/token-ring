#include "game.h"

// get player ID from command line
int parse_id_from_args (int argc, char **argv) {
  int id;

  if (argc != 2) {
    puts("usage: ./play <id number>");
    exit(EXIT_FAILURE);
  }

  id = atoi(argv[1]);

  return id;
}

// initializes a player_t structure
player_t* init_player(int id) {
  player_t* player = malloc(sizeof(player_t));

  player->id = id;
  player->next_id = (id + 1) % 4;

  return player;
}
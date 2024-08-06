#include <stdio.h>
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
  player->baton = 0;

  return player;
}

void implime_regra(){
  printf("====================== REGRA DO JOGO =======================\n");
  printf("O jogo é dividido em 0 fases por round !\n");
  printf("\n");
  printf("===============  Fase 1: Fazer os palpites ! ===============\n");
  printf("Após os jogadores receber suas cartas e tirar a manilha, cada jodagadores,\n");
  printf("irá fazer o seu palpite, o qual é adivinhar quantas jogadas voçê irá fazer nesta rodada.\n");
  printf("\n");
  printf("===============  Fase 2: Jogar as cartas ! ===============\n");
  printf("Agora é a vez de os jogadores jogaren as suas cartas de acordo com suas forças !\n");
  printf("\n");
  printf("A ORDEM DAS CARTAS:\n");
  printf(" 4  5  6  7  12(Queen)  11(Jack)  13(King)  1(Ace)  2  3 \n");
  printf("->->->->->->->->->->->->->->->->->->->->->->->->->->->->->\n");
  printf("mais fraco                                        mais forte");
  printf("\n\n");
  printf("Quando todos os jogadores jogaram as suas cartas, os jogadores \n");
  printf("irão perder suas vidas de acordo com seus palpites.\n");
  printf("Exenplo: se seu palpite for 2 e voçê jogou 1, o jogador perde uma vida.\n");
  printf("\n");
  printf("Repetir essas fases até sobreviver um jogador que é o VENCEDOR !\n");
  printf("ou até atingir o ROUND 5(neste caso, aquele que tiver mais vida é o VENCEDOR !)\n");

}
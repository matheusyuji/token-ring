#ifndef _CARD_
#define _CARD_

#include <stdio.h>
#include <stdlib.h>

typedef struct card_t{
    int tipo;           //0 = spade, 1 = crub, 2 = heart, 3 = diamond
    int numero;         // numero da carta  10 tipos
}card_t;

typedef struct Deck_t{
    int total;          //total de cartas restam no baralho
    card_t *Deck[40];   //vetor de cartas que restam no baralho(lista)
}Deck_t;

void criarBaralhoCompleto(Deck_t* Deck);

void trade_card (Deck_t* D ,int value1, int value2);    //muda a posição de duas cartas

void Shuffle_deck(Deck_t* D);             //embalha as cartas

void Draw_card(Deck_t* D, card_t C);

void imprimir_deck(Deck_t* D);

void liberarBaralho(Deck_t* D);

#endif
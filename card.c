#include "card.h"

void criarBaralhoCompleto(Deck_t* Deck){
    Deck_t *D;
    if(!(D = malloc(sizeof(Deck_t)))){
        printf("ERRO de alocação !\n");
        return;
    }

    //configura as cartas
    int x = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 1; j <= 10; j++){
            if(j <= 7)    D->Deck[x]->numero = j;
            else    if(j == 8)  D->Deck[x]->numero = 11;  //Jack
            else    if(j == 9)  D->Deck[x]->numero = 12;  //Queen
            else    D->Deck[x]->numero = 13;              //King

            D->Deck[x]->tipo = i;
            x++;
        }
    }
}
void trade_card (Deck_t* D, int value1, int value2){
    card_t* C = D->Deck[value1];
    D->Deck[value1] = D->Deck[value2];    
    D->Deck[value2] = C;
}

void Shuffle_deck(Deck_t* D){
    int value;
    for(int i = D->total; i > 0; i--){
        value = rand() % (i + 1);    
        trade_card(D, i, value);
    }
}

void Draw_card(Deck_t* D, card_t C){
    C.numero = D->Deck[D->total]->numero;
    C.tipo = D->Deck[D->total]->tipo;
    D->total--;
}

void imprimir_deck(Deck_t* D){
    for(int i = 0; i < D->total; i++){
        if(D->Deck[i]->tipo == 0)    printf("Spade   ");
        else if(D->Deck[i]->tipo == 1)   printf("Crub    ");
        else if(D->Deck[i]->tipo == 2)   printf("Heart   ");
        else    printf("Diamond ");

        if(D->Deck[i]->numero < 8)   printf("%d \n");
        else if(D->Deck[i]->numero == 11)    printf("Jack \n");
        else if(D->Deck[i]->numero == 12)    printf("Queen \n");
        else    printf("King \n");
    }
}

void liberarBaralho(Deck_t* D){
    free(D);
}
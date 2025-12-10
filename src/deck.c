#include <time.h>
#include <stdlib.h>

#include "deck.h"

#define NUM_DECK 2
#define DECK_SIZE 52
#define NUM_SUITS 4


void create_deck(CARD deck[]) {
    for (int loop = 0 ; loop < NUM_DECK; ++loop){
        for (int i = 0; i < NUM_SUITS; ++i)
            for (int index = 0; index < DECK_SIZE/NUM_SUITS; ++index ) {
                if (loop == 2){index += 52;};
                int deck_index = index + (13*i);
                deck[deck_index].card_name = index;
                switch (deck[deck_index].card_name) {
                    case QUEEN:
                    case KING:
                    case JACK:
                        deck[deck_index].card_value = 10;
                        break;
                    default:
                        deck[deck_index].card_value = index;
                        break;
                }
                deck[deck_index].card_suit = i;
        } 
    }  
}

void shuffle_deck(CARD deck[]) {
    srand(time(NULL));

    for (int i = 0; i < (NUM_DECK*DECK_SIZE); ++i) {
        int j = rand() % (NUM_DECK*DECK_SIZE);

        CARD temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

PLAYER_HAND deal_player_cards(CARD deck[], int top_card, char* name){
    PLAYER_HAND hand;
    hand.cards[0] = deck[top_card];
    hand.cards[1] = deck[top_card+1];
    hand.name = name;
    hand.count = 1;
    return hand;
}



#pragma once

#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DECK_SIZE 52
#define NUM_SUITS 4
#define MAX_HAND_SIZE 11
#define NUM_DECKS 2

typedef enum {
    KING, ACE, TWO, THREE, FOUR, FIVE, 
    SIX, SEVEN, EIGHT, NINE, 
    TEN, JACK, QUEEN
} CARD_NAME;

typedef struct {
    int bot;
    int player;
    int bot_bet;
    int player_bet;
} COINS;


typedef enum {
    DIAMONDS, SPADES, CLUBS, HEARTS
} CARD_SUIT;

typedef struct {
    CARD_NAME card_name;
    int card_value;
    CARD_SUIT card_suit;
    int hi_lo;
} CARD; 

typedef struct {
    CARD cards[MAX_HAND_SIZE];
    int count;
    char* name;
    int x_cord;
    int y_cord;
} PLAYER_HAND;

void create_deck(CARD deck[]);
void shuffle_deck(CARD deck[]);
PLAYER_HAND deal_player_cards(CARD deck[], int top_card, char* name);


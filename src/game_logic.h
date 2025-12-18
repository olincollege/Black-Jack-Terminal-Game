#pragma once

#include "deck.h"
#include "terminal_ui.h"
#include "bot_decision.h"
#include "card_counting.h"

#define BUST_AMOUNT 21
#define DEALER_HIT 17
#define MIN_DECK_SIZE 30
#define ACE_ADD 10
#define ADD_ACE 12

typedef struct {
    int top_card; 
    PLAYER_HAND bot_hand;
    PLAYER_HAND player_hand;
    PLAYER_HAND dealer_hand;
} GAME_STATE;


GAME_STATE init_game(CARD deck[], COINS *coins);
void player_turn(CARD deck[], PLAYER_HAND *hand, int *top_card, COINS *coins);
int hand_sum (PLAYER_HAND hand);
void bot_turn(CARD deck[], PLAYER_HAND *bot_hand, PLAYER_HAND *dealer_hand, int *top_card, COINS *coins);
void dealer_turn(CARD deck[], PLAYER_HAND *dealer_hand, 
    PLAYER_HAND *player_hand, PLAYER_HAND *bot_hand, int *top_card, COINS *coins);
void init_new_round (CARD deck[], COINS *coins, int *top_card, PLAYER_HAND *dealer_hand, 
    PLAYER_HAND *player_hand, PLAYER_HAND *bot_hand); 
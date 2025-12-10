#pragma once

#include "deck.h"
#include "terminal_ui.h"
#include "bot_decision.h"


typedef struct {
    int top_card;
    PLAYER_HAND bot_hand;
    PLAYER_HAND player_hand;
    PLAYER_HAND dealer_hand;
} GAME_STATE;


GAME_STATE init_game(CARD deck[], COINS coins);
int player_turn(CARD deck[], PLAYER_HAND *hand, int *top_card, COINS *coins);
int hand_sum (PLAYER_HAND hand);
int bot_turn(CARD deck[], PLAYER_HAND *bot_hand, PLAYER_HAND *dealer_hand, int *top_card, COINS *coins);
void dealer_turn(CARD deck[], PLAYER_HAND *dealer_hand, 
    PLAYER_HAND *player_hand, PLAYER_HAND *bot_hand, int *top_card, COINS *coins);
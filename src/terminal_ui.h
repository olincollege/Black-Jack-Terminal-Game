#pragma once

#include "deck.h"  
#include "game_logic.h"


const char* card_name_string(CARD_NAME name);
const char* card_suit_string(CARD_SUIT suit);
void print_card(CARD card);
void print_hand_sum(PLAYER_HAND hand);
void print_hand(PLAYER_HAND hand, int count);
void print_start_game(PLAYER_HAND bot_hand, 
    PLAYER_HAND player_hand, PLAYER_HAND dealer_hand, COINS coins);
int ask_player_move();
void print_showdown(PLAYER_HAND player_hand, PLAYER_HAND dealer_hand, 
    PLAYER_HAND bot_hand, COINS *coins);


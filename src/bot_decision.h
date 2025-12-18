#pragma once

#include "deck.h"
#include "game_logic.h"

#define HIT     "hit"
#define STAND   "stand"
#define DOUBLE  "double"

extern const char* hard_decision_table[17][10];
extern const char* soft_decision_table[9][10];
int bot_decision(PLAYER_HAND bot_hand, PLAYER_HAND dealer_hand, COINS *coins);
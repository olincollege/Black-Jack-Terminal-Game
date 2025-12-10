#include <stdio.h>

#include "game_logic.h"
#include "terminal_ui.h"
#include "deck.h"

void main(void){
    COINS coins = {0};
    while (1){
        CARD deck[104];
        GAME_STATE game_state = init_game(deck, coins);
        print_card(deck[78]);
        int end_game = player_turn(deck, &game_state.player_hand, &game_state.top_card, &coins);
        int may_game = bot_turn(deck, &game_state.bot_hand, &game_state.dealer_hand, 
            &game_state.top_card, &coins);
        dealer_turn(deck, &game_state.dealer_hand, &game_state.player_hand, 
            &game_state.bot_hand, &game_state.top_card, &coins);;
        print_showdown(game_state.player_hand, game_state.dealer_hand, game_state.bot_hand, &coins);
    }
}
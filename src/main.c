#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <ncurses.h>

#include "deck.h"
#include "game_logic.h"
#include "terminal_ui.h"


int main(void){

    initscr(); 
    cbreak();
    start_color();
    move(25,95);
    printw("Blackjack game initated");
    mvprintw(26,95, "Press any key to play"); 
    getch();
    clear();
    COINS coins = {0};
    CARD deck[DECK_SIZE*NUM_DECKS];
    GAME_STATE game_state = init_game(deck, &coins);
    
    while (1){
        player_turn(deck, &game_state.player_hand, &game_state.top_card, &coins);
        refresh();
        bot_turn(deck, &game_state.bot_hand, &game_state.dealer_hand, 
            &game_state.top_card, &coins);
        dealer_turn(deck, &game_state.dealer_hand, &game_state.player_hand, 
            &game_state.bot_hand, &game_state.top_card, &coins);
        print_showdown(game_state.player_hand, game_state.dealer_hand, game_state.bot_hand, &coins);
        getch();
        init_new_round(deck, &coins, &game_state.top_card, &game_state.dealer_hand, 
        &game_state.player_hand, &game_state.bot_hand);
    }
    endwin();
    return 0;
}

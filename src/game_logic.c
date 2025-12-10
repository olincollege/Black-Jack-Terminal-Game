#include <stdio.h>

#include "game_logic.h"

GAME_STATE init_game (CARD deck[], COINS coins){
    GAME_STATE game;
    create_deck(deck);
    shuffle_deck(deck);
    game.top_card = 0;

    game.bot_hand = deal_player_cards(deck, game.top_card, "bot");
    game.top_card = game.top_card + 2;
    game.player_hand = deal_player_cards(deck, game.top_card, "player");
    game.top_card = game.top_card +2;
    game.dealer_hand = deal_player_cards(deck, game.top_card, "dealer");
    game.top_card = game.top_card + 2;
    print_start_game(game.bot_hand,game.player_hand,game.dealer_hand, coins);
    return game;
}

int hand_sum (PLAYER_HAND hand){
    int hand_sum = 0;
    for (int i = 0; i <= hand.count; ++i) {
        hand_sum += hand.cards[i].card_value;
    }
    for (int i = 0; i <= hand.count; ++i) {
        if (hand.cards[i].card_name == ACE && hand_sum < 12){
            hand_sum += 10;
        }
    }
    return hand_sum;
}

int player_turn(CARD deck[], PLAYER_HAND *hand, int *top_card, COINS *coins){
    int move;
    while ((move = ask_player_move()) == 1) {
        (*hand).count++;
        (*hand).cards[(*hand).count] = deck[*top_card];
        print_card((*hand).cards[(*hand).count]);
        (*top_card) ++;
        print_hand_sum(*hand);
        if (hand_sum(*hand) > 21){
            printf("YOU BUSTED SO HARDDDD\n YOU LOSEEEE \n");
            (*coins).player -= 1;
            return 1;
        };
    } 
    return 0;
}

int bot_turn(CARD deck[], PLAYER_HAND *bot_hand, PLAYER_HAND *dealer_hand, int *top_card, COINS *coins){
    int move;
    while ((move = bot_decision(*bot_hand, *dealer_hand)) == 1) {
        (*bot_hand).count++;
        (*bot_hand).cards[(*bot_hand).count] = deck[*top_card];
        print_card((*bot_hand).cards[(*bot_hand).count]);
        (*top_card) ++;
        print_hand_sum(*bot_hand);
        if (hand_sum(*bot_hand) > 21){
            printf("BOT BUSTED SO HARDDDD\n HE LOST \n");
            (*coins).bot -= 1;
            return 1;
        };
    } 
    return 0;
}

void dealer_turn(CARD deck[], PLAYER_HAND *dealer_hand, 
    PLAYER_HAND *player_hand, PLAYER_HAND *bot_hand, int *top_card, COINS *coins){
    print_hand(*dealer_hand, (*dealer_hand).count);
    while (hand_sum(*dealer_hand) < 17 && !(hand_sum(*dealer_hand) > 21)) {
        (*dealer_hand).count++;
        (*dealer_hand).cards[(*dealer_hand).count] = deck[*top_card];
        (*top_card) ++;
        printf("Dealer hits:\n");
        print_card((*dealer_hand).cards[(*dealer_hand).count]);
        print_hand_sum(*dealer_hand);
        }
    if (hand_sum(*dealer_hand) > 21 && hand_sum(*player_hand) < 22) {
        printf("Dealer busts YOU WINNN! \n ");
        (*coins).player += 1;
    }
    if (hand_sum(*dealer_hand) > 21 && hand_sum(*bot_hand) < 22) {
        printf("Dealer busts BOT WINNNS! \n ");
        (*coins).bot += 1;
    }

}



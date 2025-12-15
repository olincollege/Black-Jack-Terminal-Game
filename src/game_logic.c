#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "game_logic.h"

GAME_STATE init_game (CARD deck[], COINS *coins){
    GAME_STATE game;
    create_deck(deck);
    shuffle_deck(deck);
    ask_player_bet(coins);
    (*coins).bot_bet = 1;
    game.top_card = 0;
    game.bot_hand = deal_player_cards(deck, game.top_card, "bot");
    game.top_card = game.top_card + 2;
    game.player_hand = deal_player_cards(deck, game.top_card, "player");
    game.top_card = game.top_card +2;
    game.dealer_hand = deal_player_cards(deck, game.top_card, "dealer");
    game.top_card = game.top_card + 2;
    print_start_game(game.bot_hand,game.player_hand,game.dealer_hand, *coins);
    return game;
}




void init_new_round (CARD deck[], COINS *coins, int *top_card, PLAYER_HAND *dealer_hand, 
    PLAYER_HAND *player_hand, PLAYER_HAND *bot_hand){
    move(25,95);
    printw("Press any key to start new hand");
    getch();
    clear();
    if (*top_card > (DECK_SIZE * NUM_DECKS) - MIN_DECK_SIZE){
        create_deck(deck);
        shuffle_deck(deck);
        (*top_card) = 0;
        printf("Shuffling new deck\n\n");
    }
    (*coins).bot_bet = get_bot_bet(deck, *top_card);
    ask_player_bet(coins);

    (*bot_hand) = deal_player_cards(deck, (*top_card), "bot");
    (*top_card) = (*top_card) + 2;
    (*player_hand) = deal_player_cards(deck, (*top_card), "player");
    (*top_card) = (*top_card) +2;
    (*dealer_hand) = deal_player_cards(deck, *top_card, "dealer");
    (*top_card) = (*top_card )+ 2;
    print_start_game((*bot_hand),(*player_hand),(*dealer_hand), *coins);
    
}

int hand_sum (PLAYER_HAND hand){
    int hand_sum = 0;
    for (int i = 0; i <= hand.count; ++i) {
        hand_sum += hand.cards[i].card_value;
    }
    for (int i = 0; i <= hand.count; ++i) {
        if (hand.cards[i].card_name == ACE && hand_sum < ADD_ACE){
            hand_sum += ACE_ADD;
        }
    }
    return hand_sum;
}

void player_turn(CARD deck[], PLAYER_HAND *hand, int *top_card, COINS *coins){
    int move = 1;
    while ((move = ask_player_move()) == 1) {
        (*hand).count++;
        (*hand).y_cord += 1;
        (*hand).cards[(*hand).count] = deck[*top_card];
        move((*hand).y_cord + 3,(*hand).x_cord);
        print_card((*hand).cards[(*hand).count]);
        (*top_card) ++;
        print_hand_sum(*hand);
        move((*hand).y_cord+4,(*hand).x_cord);
        printw("                    ");
        if (hand_sum(*hand) > 21){
            move(PROMPT_Y,PROMPT_X);
            clrtoeol();
            printw("You Busted and lost");
            move(PROMPT_Y+1,PROMPT_X);
            clrtoeol();
            refresh();
            sleep(3);
            (*coins).player -= (*coins).player_bet;
            break;
        };
    } 
}

void bot_turn(CARD deck[], PLAYER_HAND *bot_hand, PLAYER_HAND *dealer_hand, int *top_card, COINS *coins){
    int move = 1;
    while ((move = bot_decision(*bot_hand, *dealer_hand, coins)) == 1) {
        (*bot_hand).count++;
        (*bot_hand).y_cord += 1;
        (*bot_hand).cards[(*bot_hand).count] = deck[*top_card];
        move((*bot_hand).y_cord + 3,(*bot_hand).x_cord);
        print_card((*bot_hand).cards[(*bot_hand).count]);
        refresh();
        move(PROMPT_Y+1,PROMPT_X);
        print_card((*bot_hand).cards[(*bot_hand).count]);
        refresh();
        (*top_card) ++;
        print_hand_sum(*bot_hand);
        move((*bot_hand).y_cord+4,(*bot_hand).x_cord);
        printw("                    ");
        refresh();
        sleep(3);
        if (hand_sum(*bot_hand) > 21){
             move(PROMPT_Y,PROMPT_X);
            clrtoeol();
            printw("Bot busted and lost");
            move(PROMPT_Y+1,PROMPT_X);
            clrtoeol();
            refresh();
            sleep(2);
            (*coins).bot -= (*coins).bot_bet;
            break;
        };
    } 
}

void dealer_turn(CARD deck[], PLAYER_HAND *dealer_hand, 
    PLAYER_HAND *player_hand, PLAYER_HAND *bot_hand, int *top_card, COINS *coins){
    print_hand(*dealer_hand, (*dealer_hand).count);
    while (hand_sum(*dealer_hand) < DEALER_HIT && !(hand_sum(*dealer_hand) > BUST_AMOUNT)) {
        (*dealer_hand).count++;
        (*dealer_hand).y_cord ++;
        (*dealer_hand).cards[(*dealer_hand).count] = deck[*top_card];
        (*top_card) ++;
        move(PROMPT_Y,PROMPT_X);
        clrtoeol();
        printw("Dealer hits:\n");
        move((*dealer_hand).y_cord + 3,(*dealer_hand).x_cord);
        print_card((*dealer_hand).cards[(*dealer_hand).count]);
        move(PROMPT_Y+1,PROMPT_X);
        clrtoeol();
        print_card((*dealer_hand).cards[(*dealer_hand).count]);
        refresh();
        move((*dealer_hand).y_cord + 5,(*dealer_hand).x_cord);
        print_hand_sum(*dealer_hand);
        move((*dealer_hand).y_cord+4,(*dealer_hand).x_cord);
        printw("                    ");
        print_hand_sum(*dealer_hand);
        refresh();
        sleep(2);
        }
    move(PROMPT_Y,PROMPT_X);
    clrtoeol();
    if (hand_sum(*dealer_hand) > BUST_AMOUNT && hand_sum(*player_hand) <= BUST_AMOUNT) {
        printw("Dealer busts you win");
        (*coins).player += (*coins).player_bet;
        sleep(2);
        refresh();
    }
    if (hand_sum(*dealer_hand) > BUST_AMOUNT && hand_sum(*bot_hand) <= BUST_AMOUNT) {
        move(PROMPT_Y+1,PROMPT_X);
        clrtoeol();
        printw("Dealer busts bot wins");
        (*coins).player += (*coins).bot_bet;
        sleep(2);
        refresh();
    }

}



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "terminal_ui.h"

#define SLEEP_TIME 1
#define DIGIT_BASE 10
#define BUFFER_SIZE 8
#define COIN_X 70
#define COIN_Y 30
#define CARD_WIDTH 15
#define SUM_LINE_Y 9



const char* card_name_string(CARD_NAME name) {
    switch (name) {
        case ACE:   return "Ace";
        case TWO:   return "Two";
        case THREE: return "Three";
        case FOUR:  return "Four";
        case FIVE:  return "Five";
        case SIX:   return "Six";
        case SEVEN: return "Seven";
        case EIGHT: return "Eight";
        case NINE:  return "Nine";
        case TEN:   return "Ten";
        case JACK:  return "Jack";
        case QUEEN: return "Queen";
        case KING:  return "King";
        default:    return "Unknown";
    }
}

const char* card_suit_string(CARD_SUIT suit) {
    switch (suit) {
        case DIAMONDS: return "Diamonds";
        case SPADES:   return "Spades";
        case CLUBS:    return "Clubs";
        case HEARTS:   return "Hearts";
        default:       return "Unknown";
    }
}

void print_card(CARD card) {
    printw("%s of %s\n",
        card_name_string(card.card_name),
        card_suit_string(card.card_suit)
    );
    //getch();
    sleep(SLEEP_TIME);
}

void print_hand_sum(PLAYER_HAND hand){
    move(hand.y_cord+5, hand.x_cord);
    int sum = hand_sum(hand);
    int temp_sum = 0;
    for (int i = 0; i <= hand.count; ++i) {
        temp_sum += hand.cards[i].card_value;
    }
    printw("Hand sum: %i", sum );
    for (int i = 0; i < (sum-temp_sum)/10; ++i) {
        printw(" or %i", temp_sum);
        temp_sum += 10;
    }
    printw("\n\n");
}

void print_hand(PLAYER_HAND hand, int count) {
    int x_cord; int y_cord;
    move(hand.y_cord,hand.x_cord);
    printw("%s's hand: \n", hand.name);
    y_cord = hand.y_cord + 2; x_cord = hand.x_cord;
    move(y_cord,x_cord);
    for (int i = 0; i <= count; ++i ){
        print_card(hand.cards[i]);
        y_cord += 1;
        move(y_cord,x_cord);
    }
    print_hand_sum(hand);
}

void print_start_game(PLAYER_HAND bot_hand, 
    PLAYER_HAND player_hand, PLAYER_HAND dealer_hand, COINS coins){
    move(PROMPT_Y+2,PROMPT_X);
    printw("Bot has betted %i\n\n", coins.bot_bet);
    move(COIN_Y,COIN_X);
    printw("Bot's coins: %i\n", coins.bot);
    move(COIN_Y+2,COIN_X);
    printw("Player coins: %i\n\n\n", coins.player);
    refresh();
    print_hand(bot_hand, 1);
    refresh();
    print_hand(player_hand, 1);
    refresh();
    move(dealer_hand.y_cord, dealer_hand.x_cord);
    printw("Dealer Shows:\n");
    move(dealer_hand.y_cord + 2, dealer_hand.x_cord);
    print_card(dealer_hand.cards[0]);
    refresh();
    }

int ask_player_move(){
    move(PROMPT_Y,PROMPT_X);
    clrtoeol();
    printw("What would you like to do, hit or stand (h/s)?");
    move(PROMPT_Y+2,PROMPT_X);
    clrtoeol();
    move(PROMPT_Y+1,PROMPT_X);
    clrtoeol();
    int turn = getch();
    if (turn == 'h' || move == 'H'){
        return 1;
    };
    if (turn == 's' || move == 'S'){
        return 0;
    };
    move(PROMPT_Y+1,PROMPT_X);
    printw("Invalid move, try again\n");
    ask_player_move();
}

void ask_player_bet(COINS *coins){
    move(PROMPT_Y,PROMPT_X);
    printw("How much would you like to bet (1-20)\n");
    move(PROMPT_Y+1,PROMPT_X);
    clrtoeol();
    scanw("%d", &((*coins).player_bet));
    if ((*coins).player_bet < 1 ||  (*coins).player_bet > 20){
        move(PROMPT_Y+2,PROMPT_X);
        printw("Invalid bet, Try again");
        ask_player_bet(coins);
    }
}

void print_showdown(PLAYER_HAND player_hand, PLAYER_HAND dealer_hand, PLAYER_HAND bot_hand, COINS *coins){
    int player_sum = hand_sum(player_hand);
    int dealer_sum = hand_sum(dealer_hand);
    int bot_sum = hand_sum(bot_hand);
    if (dealer_sum > BUST_AMOUNT){
        return;
    }
    move(PROMPT_Y,PROMPT_X);
    clrtoeol();
    printw("Dealer ends with %d\n", dealer_sum);
    move(PROMPT_Y+1,PROMPT_X);
    clrtoeol();
    printw("You end with %d\n\n", player_sum);
    move(PROMPT_Y+2,PROMPT_X);
    clrtoeol();
    printw("Bot ends with %d\n\n", bot_sum);
    refresh();
    sleep(3);
    move(PROMPT_Y+3,PROMPT_X);
    clrtoeol();
    if (dealer_sum > player_sum){ 
        printw("LMAO You lose\n");
        (*coins).player -= (*coins).player_bet;
    } else if (dealer_sum < player_sum && player_sum <= BUST_AMOUNT){
        printw("You actually won somehow\n");
        (*coins).player += (*coins).player_bet; 
    } else if (player_sum <= BUST_AMOUNT) {printw("You pushed\n");}
    refresh();
    move(PROMPT_Y+4,PROMPT_X);
    clrtoeol();
    if (dealer_sum > bot_sum){
        printw("The bot losttt\n");
        (*coins).bot -= (*coins).bot_bet;
    } else if (dealer_sum < bot_sum && bot_sum <= BUST_AMOUNT){
        printw("The bot won DUH\n");
        (*coins).bot += (*coins).bot_bet; 
    } else if (bot_sum <= BUST_AMOUNT) {printw("The bot pushed\n");}
    refresh();
}

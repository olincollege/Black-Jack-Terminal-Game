#include <stdio.h>
#include <unistd.h>

#include "terminal_ui.h"

#define SLEEP_TIME 1


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
    printf("%s of %s\n",
        card_name_string(card.card_name),
        card_suit_string(card.card_suit)
    );
    sleep(SLEEP_TIME);
}

void print_hand_sum(PLAYER_HAND hand){
    int sum = hand_sum(hand);
    int temp_sum = 0;
    for (int i = 0; i <= hand.count; ++i) {
        temp_sum += hand.cards[i].card_value;
    }
    printf("Hand sum: %i", sum );
    for (int i = 0; i < (sum-temp_sum)/10; ++i) {
        printf(" or %i", temp_sum);
        temp_sum += 10;
    }
    printf("\n\n");
}

void print_hand(PLAYER_HAND hand, int count) {
    printf("%s's hand: \n", hand.name);
    for (int i = 0; i <= count; ++i ){
        print_card(hand.cards[i]);
    }
    print_hand_sum(hand);
    sleep(SLEEP_TIME);
}

void print_start_game(PLAYER_HAND bot_hand, 
    PLAYER_HAND player_hand, PLAYER_HAND dealer_hand, COINS coins){
    printf("Bot's coins: %i\n", coins.bot);
    printf("Player coins: %i\n\n\n", coins.player);
    sleep(SLEEP_TIME);
    print_hand(bot_hand, 1);
    print_hand(player_hand, 1);
    printf("Dealer Shows:\n");
    print_card(dealer_hand.cards[0]);
    printf("\n");
    }

int ask_player_move(){
    printf("What would you like to do, hit or stand?\n");
    char move[10];
    fgets(move, sizeof(move), stdin);
    if (move[0] == 'h' || move[0] == 'H'){
        return 1;
    };
    if (move[0] == 's' || move[0] == 'S'){
        return 0;
    };
    printf("Invalid move, try again\n");
    ask_player_move();
}

void print_showdown(PLAYER_HAND player_hand, PLAYER_HAND dealer_hand, PLAYER_HAND bot_hand, COINS *coins){
    int player_sum = hand_sum(player_hand);
    int dealer_sum = hand_sum(dealer_hand);
    int bot_sum = hand_sum(bot_hand);
    if (dealer_sum > 21){
        return;
    }
    printf("Dealer ends with %d\n", dealer_sum);
    printf("You end with %d\n\n", player_sum);
    printf("Bot ends with %d\n\n", bot_sum);
    sleep(3);
    if (dealer_sum > player_sum){
        printf("LMAO You lose\n");
        (*coins).player -= 1;
    } else if (dealer_sum < player_sum && player_sum <22){
        printf("You actually won somehow\n");
        (*coins).player += 1; 
    } else if (player_sum < 22) {printf("You pushed\n");}
    if (dealer_sum > bot_sum){
        printf("The bot losttt\n");
        (*coins).bot -= 1;
    } else if (dealer_sum < bot_sum && bot_sum < 22){
        printf("The bot won DUH\n");
        (*coins).bot += 1; 
    } else if (bot_sum < 22) {printf("The bot pushed\n");}
}

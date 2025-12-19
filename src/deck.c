#include "deck.h"

#define NUM_DECK 2
#define DECK_SIZE 52
#define NUM_SUITS 4
#define FACE_VALUE 10
//define the coordinates for different screeen items
#define BOT_CARDS_X 50
#define BOT_CARDS_Y 5
#define PLAYER_CARDS_X 90
#define PLAYER_CARDS_Y 5
#define DEALER_CARDS_X 130
#define DEALER_CARDS_Y 5

//Assign each card to its hi-lo value
const int hi_lo_value(CARD_NAME name) {
    switch (name) {
        case ACE:   return -1;
        case TWO:   return 1;
        case THREE: return 1;
        case FOUR:  return 1;
        case FIVE:  return 1;
        case SIX:   return 1;
        case SEVEN: return 0;
        case EIGHT: return 0;
        case NINE:  return 0;
        case TEN:   return -1;
        case JACK:  return -1;
        case QUEEN: return -1;
        case KING:  return -1;
        default:    return 0;
    }
}


void create_deck(CARD deck[]) {
    //for every number of deck run this loop
    for (int loop = 0 ; loop < NUM_DECK; ++loop){
        //for every suit run this loop
        for (int i = 0; i < NUM_SUITS; ++i)
            //for every rank run this loop
            for (int index = 0; index < DECK_SIZE/NUM_SUITS; ++index ) {
                int deck_index = index + (13*i) + (loop * DECK_SIZE);
                //label them based on their index
                deck[deck_index].card_name = index;
                deck[deck_index].hi_lo = hi_lo_value(deck[deck_index].card_name);
                switch (deck[deck_index].card_name) {
                    //Face cards assigned 10, the rest are ordered
                    //so they can just be assigned their index
                    case QUEEN:
                    case KING:
                    case JACK:
                        deck[deck_index].card_value = FACE_VALUE;
                        break;
                    default:
                        deck[deck_index].card_value = index;
                        break;
                }
                deck[deck_index].card_suit = i;
        } 
    }  
}

void shuffle_deck(CARD deck[]) {
    srand(time(NULL));

    //after getting a random seed, assign each index a random value 
    //between the number of cards we have and switch the two indexes
    for (int i = 0; i < (NUM_DECK*DECK_SIZE); ++i) {
        int ran = rand() % (NUM_DECK*DECK_SIZE);

        CARD temp = deck[i];
        deck[i] = deck[ran];
        deck[ran] = temp;
    }
}

PLAYER_HAND deal_player_cards(CARD deck[], int top_card, char* name){
    PLAYER_HAND hand;
    //Give the player the first two cards on the deck
    hand.cards[0] = deck[top_card];
    hand.cards[1] = deck[top_card+1];
    hand.name = name;
    //intialize where each hand should be displayed on the screen
    if (strcmp(hand.name, "dealer")==0){
        hand.x_cord = DEALER_CARDS_X;hand.y_cord = DEALER_CARDS_Y;};
    if (strcmp(hand.name, "bot")==0)
        {hand.x_cord = BOT_CARDS_X;hand.y_cord = BOT_CARDS_Y;}
    if (strcmp(hand.name, "player")==0)
        {hand.x_cord = PLAYER_CARDS_X;hand.y_cord = PLAYER_CARDS_Y;}
    //each hand has 2 cards (starting at 0)
    hand.count = 1; 
    return hand;
}



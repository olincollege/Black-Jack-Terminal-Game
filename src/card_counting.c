#include "card_counting.h"


int get_bot_bet(CARD deck[], int top_card){
    int card_count = 0;
    //Figure out the card count of all the cards shown already
    for (int i = 0; i < top_card; ++i){
        card_count += deck[i].hi_lo;
    }
    double deck_remaining = ((NUM_DECKS*DECK_SIZE-top_card)/52.0);
    double card_count_index = (double)card_count/(deck_remaining);
    //Return bet based on normal hi-lo bet values
    if (card_count_index < 1) {return 1;}
    if (card_count_index < 2) {return 5;}
    if (card_count_index < 4) {return 10;}
    return 20;
    }
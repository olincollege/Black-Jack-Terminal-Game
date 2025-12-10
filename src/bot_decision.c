#include <stdio.h>

#include "bot_decision.h"

const char* hard_decision_table[17][10] = {
    /* player total 4 */  {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
    /* 5 */ {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
    /* 6 */ {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
    /* 7 */ {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
    /* 8 */ {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
    /* 9 */ {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
    /* 10 */ {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
    /* 11 */ {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
    /* 12 */ {HIT, HIT, STAND, STAND, STAND, HIT, HIT, HIT, HIT, HIT},
    /* 13 */ {STAND, STAND, STAND, STAND, STAND, HIT, HIT, HIT, HIT, HIT},
    /* 14 */ {STAND, STAND, STAND, STAND, STAND, HIT, HIT, HIT, HIT, HIT},
    /* 15 */ {STAND, STAND, STAND, STAND, STAND, HIT, HIT, HIT, HIT, HIT},
    /* 16 */ {STAND, STAND, STAND, STAND, STAND, HIT, HIT, HIT, HIT, HIT},
    /* 17 */ {STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND},
    /* 18*/  {STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND},
    /* 19 */ {STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND},
    /* 20 */ {STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND},
};

const char* soft_decision_table[9][10] = {
    /* A,2 */  {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
    /* A,3 */ {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
    /* A,4 */ {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
    /* A,5 */ {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
    /* A,6 */ {HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT},
    /* A,7 */ {STAND, STAND, STAND, STAND, STAND, STAND, STAND, HIT, HIT, HIT},
    /* A,8 */ {STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND},
    /* A,9 */ {STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND},
    /* A,10 */ {STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND, STAND},
};


int bot_decision(PLAYER_HAND bot_hand, PLAYER_HAND dealer_hand){
    const char* decision;
    int hard_total = hand_sum(bot_hand);
        if (hard_total == 21){return 0;}
    int soft_total_index = 0;
    int dealer_shows = dealer_hand.cards[0].card_value;
    if (dealer_shows == 1) {dealer_shows+=10;}
    for (int i = 0; i <= bot_hand.count; ++i) {
        if (bot_hand.cards[i].card_name == ACE){
            for (int i = 0; i <= bot_hand.count; ++i) {
                soft_total_index += bot_hand.cards[i].card_value;
            }
            soft_total_index -= 1;
            break;
        }
    }
    if (soft_total_index > 9){
        hard_total = soft_total_index + 1;
        soft_total_index = 0;
    }
    if (soft_total_index){
        decision = soft_decision_table[soft_total_index-4][dealer_shows-2];
    }
    else {
        decision = hard_decision_table[hard_total-4][dealer_shows-2];
    }
    if (decision[0] == 'h' || decision[0] == 'H'){
        printf("Bot hits and gets:\n");
        return 1;
    }
    if (decision[0] == 's' || decision[0] == 'S'){
        printf("Bot stands\n");
        return 0;
    };
    printf("something is wrong\n\n");
}
    
#include <criterion/criterion.h>
//#include <criterion/new/assert.h>

#include "../src/card_counting.h"

// Check that bot bet can correctly call when the bet should be 5
Test(get_bot_bet, accurate_card_count) {
  int top_card = 6;
  CARD deck[6];
  deck[0].hi_lo = 1; deck[1].hi_lo = 0;deck[2].hi_lo = 0;
  deck[3].hi_lo = 1;deck[4].hi_lo = -1; deck[5].hi_lo = 1;
  cr_assert_eq(get_bot_bet(deck, top_card), 5, "Expected bet: 5");
}

// Check that bot bet can tell when to bet the minimum
Test(get_bot_bet, minimum_card_count) {
  int top_card = 6;
  CARD deck[6];
  deck[0].hi_lo = 0; deck[1].hi_lo = 0;deck[2].hi_lo = 0;
  deck[3].hi_lo = -1;deck[4].hi_lo = 0; deck[5].hi_lo = 1;
  cr_assert_eq(get_bot_bet(deck, top_card), 1, "Expected bet: 1");
}

// Check that bot bet can tell when to bet the maximum
Test(get_bot_bet, maximum_card_count) {
  int top_card = 9;
  CARD deck[9];
  deck[0].hi_lo = 1; deck[1].hi_lo = 1;deck[2].hi_lo = 1;
  deck[3].hi_lo = 1;deck[4].hi_lo = 1; deck[5].hi_lo = 1;
  deck[6].hi_lo = 1;deck[7].hi_lo = 1; deck[8].hi_lo = 1;
  cr_assert_eq(get_bot_bet(deck, top_card), 20, "Expected bet: 20");
}



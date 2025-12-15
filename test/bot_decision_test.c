#include <criterion/criterion.h>
//#include <criterion/new/assert.h>
#include <ncurses.h>

#include "../src/bot_decision.h"

// Check that bot bet is as expected based on what cards have been shown
Test(get_bot_bet, accurate_card_count) {
  int top_card = 6;
  CARD deck[6];
  deck[0].hi_lo = 1; deck[1].hi_lo = 0;deck[2].hi_lo = 0;
  deck[3].hi_lo = 1;deck[4].hi_lo = -1; deck[5].hi_lo = 1;
  cr_assert_int_eq(get_bot_bet(deck, top_card), 5, "Expected bet: 5");
}

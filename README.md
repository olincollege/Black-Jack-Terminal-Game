# C Project Repository Template

This is an linux terminal based two deck Blackjack game that uses ncurses to improve the UI. You get to play alongside a card counting bot, that was designed to put in optimal moves based on hi-lo card counting strategy. The bot will use card counting 
to determine a bet of size 1-20. Other than that the game can be expected to be played as a normal blackjack game besides the fact you have infinite money in this one (sadly is probably not true in the real world).

I used print debugging along with GDB debugging during my test. However, print debugging was found much more useful for this application as the application was print based and most of the bugs I got were values not coming out right, so simply seeing the values at certain times was usually enough to tell me where it went wrong. One case that GDB was more useful was while debugging creating a second deck as I was seeing there was an abnornmal amount of King of Diamonds being created. I wanted to see where the create_deck function started breaking, but I did not want to add a print loop for every card as there was 104 cards total and it would be hard to tell what part of the loop was running when the bad cards started being made. So, I used breakpoints in the loop to let me know what part of the loops the code was breaking. Below I have document picture of me using GDB as well as other print debugging statements:


This is where I was going through loops with GDB.

![GDB Debug](images/gdb_going_through_loops.png) 



Printing what the top card was and the game progressed to see what function called was breaking it

![Top Card Debug](images/top_card_debug.png) 



Printed all the values that were being added to hand sum to see if they matched the cards that was in hand

![Hand Sum Debug](images/hand_sum_debug.png) 



After deck was created I checked a random card to make sure it was not Kind of Diamonds (there as a bug where half the deck was king of diamonds).

![Checking random cards in the deck](images/checking_random_cards.png) 






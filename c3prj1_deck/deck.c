#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

//  This should print out the contents of a hand.                                                                                                                                                           
void print_hand(deck_t * hand){
  for (size_t i = 0; i < hand->n_cards; i++) {
    print_card(*hand->cards[i]);
    printf(" ");
  }
}

//   This function should check if a deck                                                                                                                                                                   
//   contains a particular card or not.  If                                                                                                                                                                 
//   the deck does contain the card, this                                                                                                                                                                   
//   function should return 1.  Otherwise,                                                                                                                                                                  
//   it should return 0.                                                                                                                                                                                    
int deck_contains(deck_t * d, card_t c) {
  for (size_t i = 0; i < d->n_cards; i++) {
    card_t currCard = *d->cards[i];
    if (currCard.value == c.value && currCard.suit == c.suit) {
      return 1;
    }
  }
  return 0;
}
// This function takes in a deck an shuffles                                                                                                                                                                
// it, randomly permuting the order of the cards.                                                                                                                                                           
void shuffle(deck_t * d){
  card_t oldCard;
  for (size_t i = 0; i < d->n_cards; i++) {
    int r = rand() % (d->n_cards);
    oldCard = *d->cards[i];
    // because card_t * c = d->cards[i];                                                                                                                                                                    
    // 表示将指向card_t类型的指针数组中第i个元素                                                                                                                                                            
    // 的指针赋值给指向card_t类型的指针card                                                                                                                                                                 
    // so card_t a = *c; or card_t a = *d->cards[i];                                                                                                                                                        
    *d->cards[i] = *d->cards[r];
    *d->cards[r] = oldCard;
  }
}

//  This function should check that                                                                                                                                                                         
//  the passed in deck contains ever                                                                                                                                                                        
//  valid card exactly once.  If                                                                                                                                                                            
//  the deck has any problems, this function                                                                                                                                                                
//  should fail an assert.                                                                                                                                                                                  
void assert_full_deck(deck_t * d) {
  card_t currCard;
  for (size_t i = 0; i < 51; i++) {
    currCard = card_from_num(i);
    assert(deck_contains(d, currCard) == 1);
  }
}

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

//Add the particular card to the given deck (which will
//   involve reallocing the array of cards in that deck).
void add_card_to(deck_t * deck, card_t c) {
  deck = realloc(deck, (deck->n_cards + 1) * sizeof(*deck));
  deck->cards[deck->n_cards] = &c;
  deck->n_cards += 1;
}

//   Add a card whose value and suit are both 0, and return a pointer
//   to it in the deck.
//   This will add an invalid card to use as a placeholder
//   for an unknown card.
card_t * add_empty_card(deck_t * deck) {
  card_t * c = malloc(sizeof(*c));
  c->value = 0;
  c->suit = 0;
  add_card_to(deck, *c);
  return c;
}

//   Create a deck that is full EXCEPT for all the cards
//   that appear in excluded_cards.  For example,
//   if excluded_cards has Kh and Qs, you would create
//   a deck with 50 cards---all of them except Kh and Qs.
//   You will need to use malloc to allocate this deck.
//   (You will want this for the next function).
deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * d = malloc(sizeof(*d));
  d->n_cards = 52 - excluded_cards->n_cards;
 
  card_t * c = malloc(sizeof(*c));
  for (int i = 0; i < 52; i++) {
    *c = card_from_num(i);
    if (deck_contains(excluded_cards, *c) == 1) {
      continue;
    }
    d->cards = realloc(d->cards, i + 1);
    d->cards[i] = c;
  }
  free(c);
  return d;
}

//This function takes an array of hands (remember
//   that we use deck_t to represent a handa).  It then builds
//   the deck of cards that remain after those cards have
//   been removed from a full deck.  For example, if we have
//   two hands:
//      Kh Qs ?0 ?1 ?2 ?3 ?4
//      As Ac ?0 ?1 ?2 ?3 ?4
//   then this function should build a deck with 48
//   cards (all but As Ac Kh Qs).  You can just build
//   one deck with all the cards from all the hands
//   (remember you just wrote add_card_to),
//   and then pass it to make_deck_exclude.
deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * ans = malloc(sizeof(*ans));
  deck_t * excludeDeck = malloc(sizeof(*excludeDeck));
  card_t * c = malloc(sizeof(*c));
  
  for (size_t i = 0; i < n_hands; i++) {
    for (size_t j = 0; j < hands[i]->n_cards; j++) {
      if (deck_contains(excludeDeck, *hands[i]->cards[j]) == 1) {
	continue;
      }
      *c = *hands[i]->cards[j];
      excludeDeck->n_cards += 1;
      excludeDeck->cards = realloc(excludeDeck->cards, excludeDeck->n_cards * sizeof(*excludeDeck->cards));
      excludeDeck->cards[excludeDeck->n_cards - 1] = c;
    }
  }
  free(c);
  ans = make_deck_exclude(excludeDeck);
  free(excludeDeck);
  return ans;
}

//  Free the memory allocated to a deck of cards.
//  For example, if you do
//  deck_t * d = make_excluded_deck(something);
//  free_deck(d);
//  it should free all the memory allocated by make_excluded_deck.
void free_deck(deck_t * deck) {
  for (size_t i = 0; i < deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}

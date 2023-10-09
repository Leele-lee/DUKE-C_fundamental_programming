#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "future.h"

//   This adds ptr into the future cards for the given index (that is,
//   which ?n it is). So if this is a future card for ?3, then index
//   will be 3.  ptr will point at an existing placeholder card
//   (it will point into a hand at a card which was added
//   with add_empty_card).
void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  if (fc == NULL) {
    fc = malloc(sizeof(*fc));
    fc->decks = NULL;
    fc->n_decks = 0;
  }
  if (index >= fc->n_decks) {
    //need realloc fc->decks
    fc->decks = realloc(fc->decks, (index + 1) * sizeof(*fc->decks));
    for (size_t i = fc->n_decks; i < index + 1; i++) {
      fc->decks[i].n_cards = 0;
      fc->decks[i].cards = NULL;
    }
    fc->n_decks = index + 1;
  }
  fc->decks[index].cards = realloc(fc->decks[index].cards,
				   (fc->decks[index].n_cards + 1) * sizeof(*fc->decks[index].cards));
  fc->decks[index].cards[fc->decks[index].n_cards] = ptr;
  fc->decks[index].n_cards += 1;
}

//   This function takes a deck (which has been shuffled),
//   and a future_cards_t (which has been filled in with
//   all the pointers to placeholders) and draws cards from
//   the deck and assigns their values and suits to the
//   placeholders pointed to in fc.
void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  assert(deck != NULL);
  assert(fc != NULL);
  for (size_t i = 0; i < fc->n_decks; i++) {
    deck_t currD = fc->decks[i];
    if (currD.n_cards == 0) {
      fprintf(stderr,"Error: Invalid future card deck at index '%ld'\n",i);
      assert(currD.n_cards != 0);
    }
    for (size_t j = 0; j < currD.n_cards; j++) {
      currD.cards[j]->value = deck->cards[i]->value;
      currD.cards[j]->suit = deck->cards[i]->suit;
    }
  }
}







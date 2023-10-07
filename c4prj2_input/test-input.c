#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int main() {
  FILE * f = fopen("input1.txt", "r");
  size_t n_hands = 2;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->n_decks = 0;
  fc->decks = NULL;
  deck_t ** ans = malloc(n_hands * sizeof(*ans));
  ans = read_input(f, &n_hands, fc);
  for (size_t i = 0; i < n_hands; i++) {
    print_hand(ans[i]);
  }
 
  for (size_t i = 0; i < n_hands; i++) {
    /*for (size_t j = 0; j < ans[i]->n_cards; j++) {
      free(ans[i]->cards[j]);
    }*/
    free_deck(ans[i]);
  }
  
  free(fc);
  free(ans);
  return 0;
}

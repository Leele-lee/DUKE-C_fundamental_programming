#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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

  deck_t * testDeck = malloc(sizeof(* testDeck));
  testDeck->n_cards=0;
  testDeck->cards=NULL;
  
  card_t testCard;
  for (int i=0; i<51; i++){
    testCard = card_from_num(i);
    add_card_to(testDeck, testCard);
  }
  print_hand(testDeck);
  printf("\n");
  future_cards_from_deck(testDeck, fc);

  //print fc->decks
  print_hand(fc->decks);
  assert(fc->decks != NULL);
  printf("\n");
  fprintf(stdout, "fc n_decks is %zu\n", fc->n_decks);
  
  
  for (size_t i = 0; i < n_hands; i++) {
    print_hand(ans[i]);
    printf("\n");
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

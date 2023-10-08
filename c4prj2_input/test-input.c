#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"
/*
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
    //for (size_t j = 0; j < ans[i]->n_cards; j++) {
     // free(ans[i]->cards[j]);
   // }
    free_deck(ans[i]);
  }
  
  free(fc);
  free(ans);
  return 0;
}
*/

void free_future_cards(future_cards_t * fc) {
  if (fc == NULL) {
    printf("Nothing in the future cards!\n");
    return;
  }
  for (size_t i=0; i<fc->n_decks; i++) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    perror("Uasge: thisProgram inputFile\n");
    return EXIT_FAILURE;
  }

  deck_t ** hands = NULL;
  size_t n_hands = 0;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->n_decks = 0;
  fc->decks = NULL;
  FILE * f = fopen(argv[1], "r");
  hands = read_input(f, &n_hands, fc);

  if (hands == NULL) {
    perror("Error: hands is NULL!\n");
    return EXIT_FAILURE;
  }
  
  for (size_t i=0; i<n_hands; i++) {
    printf("\nPrint hand %zu :\n",i);
    print_hand(hands[i]);
    printf("\n");
  }

  for (size_t i=0; i<n_hands; i ++) {
    free_deck(hands[i]);
  }
  free(hands);

  free_future_cards(fc); 
  
  return EXIT_SUCCESS;
}

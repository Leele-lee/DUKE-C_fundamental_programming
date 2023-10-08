#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"

void test_contained(deck_t * deck, deck_t * hand) {
  for (size_t i=0; i<hand->n_cards; i++) {
    if (deck_contains(deck, *(hand->cards[i]))) {
      perror("cards in hand should not be included in the deck!\n");
      exit(EXIT_FAILURE);
    }
  }
}

void free_future_cards(future_cards_t * fc) {
  for (size_t i=0; i<fc->n_decks; i++) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);
}

int main() {
  // Test 0
  printf("Test 0:\n");
  deck_t * deck0;
  deck_t * hand0 = NULL;
  deck0 = make_deck_exclude(hand0);
  
  if (deck0 == NULL) {
    perror("deck0 should be full\n");
    return EXIT_FAILURE;
  }
  printf("Cards from deck:\n");
  print_hand(deck0);
  printf("\nCards from hand:\n");
  print_hand(hand0);
  printf("\nPassed!\n\n");
  
  // Test 1
  printf("Test 1:\n");
  deck_t * deck1;
  deck_t * hand11 = malloc(sizeof(*hand11));
  card_t card_10 = card_from_letters('6', 'c');
  card_t card_11 = card_from_letters('8', 'd');
  card_t card_12 = card_from_letters('K', 's');
  card_t cards_11[] = {card_10, card_11, card_12};
  hand11->n_cards = 0;
  hand11->cards = NULL;
  for (size_t i=0; i<3; i++) {
    add_card_to(hand11, cards_11[i]);
  }
  // Test deck exclude
  deck1 = make_deck_exclude(hand11);
  test_contained(deck1, hand11);
  printf("Cards from deck:\n");
  print_hand(deck1);
  printf("\nCards from hand:\n");
  print_hand(hand11);
  printf("\nDeck Exclude Passed!\n\n");

  // Test future card
  future_cards_t * fc1 = malloc(sizeof(*fc1));
  fc1->n_decks = 0;
  fc1->decks = NULL;
  card_t * emp_c_p = add_empty_card(hand11);
  printf("\nCards from hand with unknown cards:\n");
  print_hand(hand11);
  printf("\nTest empty card\n");
  printf("empty card value: %d \n",emp_c_p->value);
  printf("empty card suit: %d \n", emp_c_p->suit);
  add_future_card(fc1, 0, emp_c_p);
  if ( fc1 == NULL) {
    perror("Error: fc should not be NULL!\n");
    return EXIT_FAILURE;
  }
  future_cards_from_deck(deck1, fc1);
  printf("\nCards from hand after revealing unknown cards:\n");
  print_hand(hand11);
  printf("\nFuture Cards Passed!\n\n");

  
  // Tets 2
  printf("Test 2:\n");
  deck_t * deck2;
  deck_t hand21;
  hand21.n_cards = 3;
  card_t card_20 = card_from_letters('5', 'h');
  card_t card_21 = card_from_letters('Q', 'h');
  card_t card_22 = card_from_letters('2', 'd');
  card_t *cards_21[] = {&card_20, &card_21, &card_22};
  hand21.cards = cards_21;
  
  deck_t hand22;
  hand22.n_cards = 3;
  card_t card_23 = card_from_letters('4', 'h');
  card_t card_24 = card_from_letters('J', 's');
  card_t card_25 = card_from_letters('A', 'd');
  card_t *cards_22[] = {&card_23, &card_24, &card_25};
  hand22.cards = cards_22;

  deck_t * hands2[] = {&hand21, &hand22};
  deck2 = build_remaining_deck(hands2, 2);

  for (size_t i=0; i<2; i++) {
    test_contained(deck2, hands2[i]);
  }
  printf("Cards from deck:\n");
  print_hand(deck2);
  printf("\nCards from hand:\n");
  print_hand(&hand21);
  printf("\nCards from hand:\n");
  print_hand(&hand22);
  printf("\nPassed!\n\n");
  
  printf("Free memory\n");
  free_deck(deck0);
  free_deck(deck1);
  free_deck(deck2);
  free_deck(hand11);
  free_future_cards(fc1);
  printf("Finish testing!!\n");
  return EXIT_SUCCESS;
}

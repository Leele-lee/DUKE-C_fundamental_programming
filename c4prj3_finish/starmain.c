#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"


void free_future_cards(future_cards_t * fc) {
  for (size_t i=0; i<fc->n_decks; i++) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);
}

void print_result(unsigned int * wins, size_t n_hands, int n_simulations) {
  for (size_t i=0; i<n_hands; i++) {
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, wins[i], n_simulations, 100*wins[i]/(float)(n_simulations));
  }
  printf("And there were %u ties\n", wins[n_hands]);

}
size_t find_winner(deck_t ** hands, size_t n_hands) {
  deck_t * win_hand = hands[0];
  int hand_win_num = 0;
  int is_tie = 0;
  for (size_t hand_num=1; hand_num<n_hands; hand_num++) {
    int result_compare = compare_hands(win_hand, hands[hand_num]);
    if (result_compare < 0) {
      // hand 2 wins                                                                                                                                                                                        
      win_hand = hands[hand_num];
      is_tie = 0;
      hand_win_num = hand_num;
    }
    if (result_compare == 0) {
      // Tie                                                                                                                                                                                                
      is_tie = 1;
    }
  }
  if (is_tie == 1) {
    hand_win_num = n_hands;
  }
  return hand_win_num;
}
int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE                                                                                                                                                                                     
  if (argc != 2 && argc != 3) {
    printf("Prawidlowa skladnia to: %s file_input no_or_trials\n", argv[0]);
    return EXIT_FAILURE;
  }

  int n_simulations = 10000;
  if (argc == 3) {
    n_simulations = atoi(argv[2]);
  }

  FILE * f = fopen(argv[1], "r");

  // Read input file                                                                                                                                                                                        
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
  size_t n_hands = 0;
  deck_t ** hands = read_input(f, &n_hands, fc);

  // Build deck excluding cards from hands                                                                                                                                                                  
  deck_t *deck = build_remaining_deck(hands, n_hands);
  // Create an array to count how many times each hand win                                                                                                                                                  
  // (if tie, add value to the last elemenr)                                                                                                                                                                
  // Therefore, number of element should be n_hands + 1 (tie slot)                                                                                                                                          
  unsigned int * wins = calloc(n_hands + 1, sizeof(*wins));
    // Monte Carlo trial                                                                                                                                                                                      
  for (size_t simul=0; simul<n_simulations; simul++) {
    if (n_hands == 1) {
      wins[0] = n_simulations;
      break;
    }
    //Shuffle the deck                                                                                                                                                                                      
    shuffle(deck);
    // Assign unknown cards from the shuffled deck                                                                                                                                                          
    future_cards_from_deck(deck, fc);
    // Compare hands                                                                                                                                                                                        
    size_t hand_win_num = 0;
    hand_win_num = find_winner(hands, n_hands);
    wins[hand_win_num]++;
  }

  // Print evaluation of each hand                                                                                                                                                                          
  print_result(wins, n_hands, n_simulations);

  // Free allocated memory                                                                                                                                                                                  
  for (size_t i=0; i<n_hands; i++) {
    free_deck(hands[i]);
  }
  free(hands);
  free(wins);
  free_future_cards(fc);
  free_deck(deck);
  deck = NULL;

  // close file                                                                                                                                                                                             
  if (fclose(f) != 0) {
    perror("Error: Could not close file!\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

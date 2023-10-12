#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

void free_future(future_cards_t * fc) {
  for (size_t i = 0; i < fc->n_decks; i++) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);
}

//return the winner hand's index in handDecks                                                                                                                                                               
//if has tie at last return a num which is n_hands                                                                                                                                                          
int find_winner(deck_t ** handsDecks, size_t n_hands) {
  int maxIndex = 0;
  int tieNum = 0;
  for (size_t i = 1; i < n_hands; i++) {
    int cmp = compare_hands(handsDecks[i], handsDecks[maxIndex]);
    if (cmp > 0) {
      maxIndex = i;
      tieNum = 0;
    }
    if (cmp == 0) {
      tieNum = 1;
    }
  }
  // max winner is not tie                                                                                                                                                                                  
  if (tieNum == 1) {
    maxIndex = n_hands;
  }
  // has tie                                                                                                                                                                                                
  return maxIndex;
}
// For each hand, you should printf                                                                                                                                                                         
//       "Hand %zu won %u / %u times (%.2f%%)\n"                                                                                                                                                            
//        where the %zu is the hand number (0,1,..)  [zu is for size_t]                                                                                                                                     
//        the first %u is the number of wins for that hand                                                                                                                                                  
//        the second %u is the total number of trials                                                                                                                                                       
//        the %.2f is the percentage that this win/trials ratio gives                                                                                                                                       
//   Then you should printf one more line for the ties:                                                                                                                                                     
//     "And there were %u ties\n"                                                                                                                                                                           
//        Where the %u is just a count of how many ties there were                                                                                                                                          
void print_result(unsigned winArr[], size_t n_hands, int num_trials) {
  for (size_t i = 0; i < n_hands; i++) {
    fprintf(stdout, "Hand %zu won %u / %u times (%.2f%%)\n", i, winArr[i], num_trials, 100 * winArr[i] / (float)num_trials);
    
  }
  fprintf(stdout, "And there were %u ties\n", winArr[n_hands]);
}

int main(int argc, char ** argv) {

  //Check command line arguments/report errors                                                                                                                                                              
  if (argc != 2 && argc != 3) {
    fprintf(stderr, "should input: poker %s [num_trials](optional)", argv[0]);
    return EXIT_FAILURE;
  }

  int num_trials;
  if (argc == 2) {
    num_trials = 10000;
  } else {
    num_trials = atoi(argv[2]);
  }

  //Open the input file and read the hands in it                                                                                                                                                            
  // (you just wrote read_input!)                                                                                                                                                                           
  FILE * f = fopen(argv[1], "r");

  size_t n_hands = 0;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->n_decks = 0;
  fc->decks = NULL;

  deck_t ** handsDecks = read_input(f, &n_hands, fc);
  //Create a deck with the remaining cards                                                                                                                                                                  
  //   (you just wrote build_remaining_deck)                                                                                                                                                                
  deck_t * remaining_cards = build_remaining_deck(handsDecks, n_hands);

  //Create an array to count how many times each hand                                                                                                                                                       
  //   wins, with one more element for if there was a tie                                                                                                                                                   
  //   (so if there are 2 hands, you should have 3 elements).                                                                                                                                               
  //   and initialize all its values to 0.                                                                                                                                                                  
  unsigned winArr[n_hands + 1];
  for (int i=0; i<n_hands+1; i++){
    winArr[i]=0;
  }

  //  int i = 0;
  //Do each Monte Carlo trial (repeat num_trials times)                                                                                                                                                     
  //     - Shuffle the deck of remaining cards                                                                                                                                                              
  //      (you wrote shuffle in Course 3)                                                                                                                                                                   
  for (size_t i = 0; i < num_trials; i++) {
    if (n_hands == 1) {
      winArr[0] = num_trials;
      break;
    }
    shuffle(remaining_cards);
    //i++;

    //  - Assign unknown cards from the shuffled deck                                                                                                                                                       
    //    (you just wrote future_cards_from_deck)                                                                                                                                                           
    future_cards_from_deck(remaining_cards, fc);
        //  - Use compare_hands (from Course 3) to                                                                                                                                                              
    //    figure out which hand won. Note that                                                                                                                                                              
    //    with potentially more than 2 hands,                                                                                                                                                               
    //    this is much like finding the max of                                                                                                                                                              
    //    an array, but using compare_hands                                                                                                                                                                 
    //    instead of >.                                                                                                                                                                                     
    int winnerIndex = find_winner(handsDecks, n_hands);

    //      - Increment the win count for the winning                                                                                                                                                       
    //    hand (or for the "ties" element of the array                                                                                                                                                      
    //    if there was a tie).                                                                                                                                                                              
    winArr[winnerIndex]++;
  }

  //  - After you do all your trials, you just need                                                                                                                                                         
  // to print your results, free any memory                                                                                                                                                                 
  // you allocated, and close any open files.                                                                                                                                                               
  print_result(winArr, n_hands, num_trials);

  //free                                                                                                                                                                                                    
  for (size_t i = 0; i < n_hands; i++) {
    free_deck(handsDecks[i]);
  }
  free(handsDecks);
  free_future(fc);
  free_deck(remaining_cards);
    //close file                                                                                                                                                                                              
  if (fclose(f) != 0) {
    perror("Error: Could not close file!\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}


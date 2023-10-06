#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "deck.h"
#include "future.h"
#include "input.h"
#include "cards.h"

//This function reads the input from f.  Recall that the input
//   file has one hand per line (and that we represent a hand
//   with a deck_t).  You should allocate a deck_t for each hand
//   and place it into an array of pointers to deck_ts, which is your
//   answer.

//abstracted out the code to take one single line
//   and parse it into a hand:
deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * d = malloc(sizeof(*d));
  char * line = malloc(strlen(str) * sizeof(*line));
  strcpy(line, str);
  card_t * c = malloc(sizeof(*c));
  // get card info which is limit by ' '
  char * info;
  info = strtok(line, " ");
  size_t i = 0;
  while (info != NULL) {
    assert(strlen(info) == 2);
    char value = info[0];
    char suit = info[1];
    if (value != '?') {
      *c = card_from_letters(value, suit);
      //d->cards = realloc((i + 1) * sizeof(*d->cards));
      add_card_to(d, *c);
    } else {
      c = add_empty_card(d);
      size_t index = suit - '0'; //change char into size_t
      add_future_card(fc, index, c);
    }
    i++;
    info = strtok(NULL, " ");
  }
  free(line);
  if (i < 5) {
    fprintf(stderr, "Error: Invalid number of cards in input file\n");
    assert(i >= 5);
  }
  return d;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  assert(f != NULL);
  char * curr = NULL;
  size_t sz;
  size_t i = 0;
  while (getline(&curr, &sz, f) >= 0) {
    
  }
}

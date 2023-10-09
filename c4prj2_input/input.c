#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
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
/*deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * d = malloc(sizeof(*d));
  d->n_cards = 0;
  d->cards = NULL;
  char * line = malloc((strlen(str) + 1) * sizeof(*line));
  strcpy(line, str);
  //card_t * c = malloc(sizeof(*c));
  // get card info which is limit by ' '
  char * info;
  info = strtok(line, " ");
  size_t i = 0;
  while (info != NULL) {
    //assert(strlen(info) == 2);
    char value = info[0];
    char suit = info[1];
    if (value != '?') {
      card_t c = card_from_letters(value, suit);
      //d->cards = realloc((i + 1) * sizeof(*d->cards));
      add_card_to(d, c);
    } else {
      //c = add_empty_card(d);
      size_t index = suit - '0'; //change char into size_t
      add_future_card(fc, index, add_empty_card(d));
    }
    i++;
    info = strtok(NULL, " ");
  }
  free(line);
  if (i < 5) {
    fprintf(stderr, "Hands smaller than 5 cards\n");
    assert(i >= 5);
  }
  return d;
}
*/

deck_t * hand_from_string(const char * str, future_cards_t * fc){
  deck_t* deck=malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards=0;
  for(int i=0;i<strlen(str);i++){
    if((str[i] == '\n')||(str[i] == ' '))continue;
    else{
      if(str[i] == '?'){
        i++;
        char num[strlen(str)];
        int n=0;
        while(!((str[i] == '\n')||(str[i] == ' '))) {
          num[n]=str[i];
          i++;n++;}
        num[n]='\0';
        add_future_card(fc,atoi(num),add_empty_card(deck)) ;

      }
      else{
        card_t x = card_from_letters(str[i],str[i+1]);
        add_card_to(deck,x);
        i++;}
    }
  }
  if (deck->n_cards < 5 ){
    return NULL;
    fprintf(stderr,"asas");}
  return deck;
}

/*deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  assert(f != NULL);
  deck_t ** ans = NULL;
  char * line = NULL;
  size_t sz;
  size_t i = 0;
  while (getline(&line, &sz, f) >= 0) {
    ans = realloc(ans, (i + 1) * sizeof(*ans));
    deck_t * temp = hand_from_string(line, fc);
    if (temp != NULL) {
      ans[i] = temp;
      i++;
    } else {
      continue;
    }
    //    ans[i] = hand_from_string(line, fc);
    //    assert(ans[i]->n_cards != 0);
    
  }
  *n_hands = i;
  free(line);
  return ans;
}
*/
deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
  deck_t **arr=NULL;
  size_t n_hand=0;
  char *line=NULL;
  size_t sz=0;
  while(getline(&line,&sz,f)>=0){
    arr=realloc(arr,(n_hand+1)*sizeof(*arr));
    deck_t*deck=hand_from_string(line,fc);
    if (deck == NULL)continue;
    arr[n_hand]=deck;
    n_hand ++;
  }
  free(line);
  *n_hands=n_hand;
  return arr;
}



CFLAGS= -ggdb3 -Wall -Werror -pedantic -std=gnu99 -g

test-future: input.o future.o deck.o eval.o cards.o test-future.o
	gcc -o test-future test-future.c input.o future.o deck.o eval.o cards.o $(CLAGS) 

input.o:input.c
	gcc -c input.c $(CFLAGS)

future.o:future.c
	gcc -c future.c $(CFLAGS)

deck.o: deck.c
	gcc -c deck.c $(CFLAGS)

eval.o: eval.c
	gcc -c eval.c $(CFLAGS)

cards.o: cards.c
	gcc -c cards.c $(CFLAGS)

test-future.o: test-future.c
	gcc -c test-future.c $(CFLAGS)

deck.o:deck.h
eval.o:eval.h
cards.o:cards.h
future.o:future.h
input.o:input.h

CC=gcc
CFLAGS=-Wall -Werror -ggdb3 -std=gnu99 -pedantic $(OTHERFLAGS)
poker: cards.o  deck.o  eval.o  future.o  input.o  main.o
	gcc -o $@ $(CFLAGS) $^
deck.o: deck.c
	gcc -c $< $(CFLAGS)
eval.o: eval.c
	gcc -c $< $(CFLAGS)
future.o: future.c
	gcc -c $< $(CFLAGS)
input.o: input.c
	gcc -c $< $(CFLAGS)
main.o: main.c
	gcc -c $< $(CFLAGS)
clean:
	rm -rf *.o poker *~


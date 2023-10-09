CFLAGS =-std=gnu99 -ggdb3 -pedantic -Wall -Werror
# test-future: test-future.o cards.o deck.o eval.o future.o input.o
# 	gcc $(CFLAGS) -o $@ $^
# test-future.o: test-future.c 
# 	gcc -c $< $(CFLAGS)
test-input: test-input.o cards.o deck.o eval.o future.o input.o
	gcc $(CFLAGS) -o $@ $^
test-input.o: test-input.c 
	gcc -c $< $(CFLAGS)
deck.o: deck.c
	gcc -c $< $(CFLAGS)
eval.o: eval.c
	gcc -c $< $(CFLAGS)
cards.o: cards.c
	gcc -c $< $(CFLAGS)
future.o: future.c
	gcc -c $< $(CFLAGS)
input.o: input.c
	gcc -c $< $(CFLAGS)
clean:
	rm -rf *.o test_c4 *~ test-future test-input

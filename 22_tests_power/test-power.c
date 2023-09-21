#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);

// calls power, checks that the result is expected_ans,
// and if not, prints a message and calls exit(EXIT_FAILURE).
void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned act = power(x, y);
  if (act != expected_ans) {
    printf("expext: %d, but get %d.", expected_ans, act);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 0, 1);
  run_check(0, 3, 0);
  run_check(-3, 2, 9);
  run_check(-3, 0, 1);
  run_check(99, 0, 1);
  run_check(99, 1, 99);
  run_check(1, 99, 1);
  run_check(2, 31, 2147483648);
  return EXIT_SUCCESS;
}

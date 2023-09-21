#include <stdlib.h>
#include <stdio.h>

struct _retire_info {
  int months;
  // for how many dollars are contributed (or spend if negative) from the account per month                                                                                                                 
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double retirement_helper (int startAge, double initial, retire_info working_or_retired,int working_months);

void retirement (int startAge, double initial, retire_info working, retire_info retired){
  double after_working_balancd = retirement_helper (startAge, initial, working, working.months);
  retirement_helper(startAge + working.months, after_working_balancd, retired, working.months);
}

double retirement_helper (int startAge, double initial, retire_info working_or_retired, int working_months) {
  double balance = initial;
  int start_months;
  int end_months;
  if (working_or_retired.contribution >= 0) {
    start_months = 0;
    end_months = working_months;
  } else {
    start_months = working_months;
    end_months = start_months + working_or_retired.months;
  }
  while (end_months > start_months) {
    printf("Age %3d month %2d you have $%.2lf\n", startAge/12, startAge % 12, balance);
    if (working_or_retired.contribution >= 0) {
      balance = balance + balance * working_or_retired.rate_of_return + working_or_retired.contribution;
    } else {
      balance = balance + balance * working_or_retired.rate_of_return + working_or_retired.contribution;
    }
    end_months -= 1;
    startAge += 1;
  }
  return balance;
}
int main (void) {
  retire_info working;
  retire_info retired;

  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045/12;

  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12;

  retirement(327, 21345, working, retired);

  return EXIT_SUCCESS;
}


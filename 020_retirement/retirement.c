#include <stdio.h>
#include <stdlib.h>

// model both savings while working and expenses while retired
struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double get_balance(retire_info x, double init) {
  double bal = init;
  bal += bal * (x.rate_of_return / 12);
  bal += x.contribution;
  return bal;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance = initial;
  for (int i = 0; i < working.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n", startAge / 12, startAge % 12, balance);
    balance = get_balance(working, balance);
    startAge += 1;
  }
  for (int j = 0; j < retired.months; j++) {
    printf("Age %3d month %2d you have $%.2f\n", startAge / 12, startAge % 12, balance);
    balance = get_balance(retired, balance);
    startAge += 1;
  }
}

int main(void) {
  retire_info work;
  work.months = 489;
  work.contribution = 1000;
  work.rate_of_return = 0.045;

  retire_info reti;
  reti.months = 384;
  reti.contribution = -4000;
  reti.rate_of_return = 0.01;

  int age = 327;
  double savings = 21345;
  retirement(age, savings, work, reti);
  return EXIT_SUCCESS;
}

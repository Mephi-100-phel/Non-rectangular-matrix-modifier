#include <stdio.h>
#include <stdlib.h>
#include "insert.h"
#include "matrix.h"
#include "errors.h"

int getInt(int* x, int (*check)(int)) {
  if (x == NULL) {
    return INVALID_POINTER_ERR;
  }
  int helper = 0;
  do {
    helper = scanf("%d", x);
    if (helper == EOF) {
      return EOF;
    }
    if (helper != 1 || check(*x) == 0) {
      printf("Некорректный ввод\n");
      printf("Повторите ввод: ");
      scanf("%*[^\n]");
    }
  } while (helper != 1 || check(*x) == 0);
  scanf("%*[^\n]");
  scanf("%*c");
  return NO_ERR;
}

int any(int x) {
  return 1;
}

int pos(int x) {
  return (x > 0) ? 1 : 0;
}

int pos_or_zero(int x) {
  return (x >= 0) ? 1 : 0;
}

int neg_or_zero(int x) {
  return (x <= 0) ? 1 : 0;
}

int neg(int x) {
  return (x < 0) ? 1 : 0;
}

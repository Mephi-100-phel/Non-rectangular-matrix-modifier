#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "errors.h"
#include "insert.h"
#include "process.h"

int main(void) {
  int helper = 0;
  Matrix *matr = getMatrix();
  if (matr == NULL) {
    return NO_ERR;
  }
  printf("\nВведённая матрица:\n");
  print_matrix(matr);
  Matrix *new_matr = new_matrix(matr);
  if (new_matr == NULL) {
    return NO_ERR;
  }
  printf("Обработанная матрица:\n");
  print_matrix(new_matr);
  clear_matrix(new_matr);
  clear_matrix(matr);
  return NO_ERR;
}

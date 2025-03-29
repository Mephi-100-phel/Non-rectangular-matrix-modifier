#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "matrix.h"
#include "errors.h"
#include "process.h"

int max_index(Line* line) {
  int line_len = line->len, max = INT_MIN, index = -1;
  int *f_line = line->line;
  for (int i = 0; i < line_len; i++) {
    if (max <= f_line[i]) {
      max = f_line[i];
      index = i;
    }
  }
  return index;
}

Matrix* new_matrix(Matrix* input_matr) {
  if (input_matr == NULL) {
    return NULL;
  }
  Matrix *out_matr = create_matrix();
  Line **input_f_matr = input_matr->matrix;
  out_matr->len = input_matr->len;
  int matr_len = out_matr->len;
  Line **matr = (Line**)calloc(matr_len, sizeof(Line*));
  for (int i = 0; i < matr_len; i++) {
    int line_len = max_index(input_f_matr[i]) + 1;
    Line *out_line = Linencpy(input_f_matr[i], line_len);
    matr[i] = out_line;
  }
  out_matr->matrix = matr;
  return out_matr;
}

Line* Linencpy(Line *src_line, int n) {
  if (src_line == NULL) {
    return NULL;
  }
  int *src_f_line = src_line->line;
  int *out_f_line = (int*)calloc(n, sizeof(int));
  for (int i = 0; i < n; i++) {
    out_f_line[i] = src_f_line[i];
  }
  Line *out_line = create_line();
  out_line->len = n;
  out_line->line = out_f_line;
  return out_line;
}

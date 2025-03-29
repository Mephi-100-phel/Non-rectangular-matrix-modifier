#include <stdio.h>
#include <stdlib.h>
#include "insert.h"
#include "matrix.h"
#include "errors.h"

Matrix* create_matrix(void) {
  return (Matrix*)calloc(1, sizeof(Matrix));
}

Line* create_line(void) {
  return (Line*)calloc(1, sizeof(Line));
}

Line* getLine(int len) {
  if (len == 0) {
    Line *out = (Line*)calloc(1, sizeof(Line));
    int *line = (int*)calloc(1, sizeof(int));
    out->line = line;
    return out;
  }
  int helper = 0;
  int* line = (int*)calloc(len, sizeof(int));
  for (int i = 0; i < len; i++) {
    int elem = 0;
    printf("Введите элемент: ");
    helper = getInt(&elem, any);
    if (helper == EOF || helper == INVALID_POINTER_ERR) {
      free(line);
      return NULL;
    }
    line[i] = elem;
  }
  Line *out = create_line();
  out->line = line;
  out->len = len;
  return out;
}

Matrix* getMatrix(void) {
  int helper = 0, matr_len = 0;
  printf("Введите количество строк: ");
  helper = getInt(&matr_len, pos_or_zero);
  if (matr_len == 0) {
    printf("*ТУТ НИЧЕГО НЕТ*\n");
    return NULL;
  }
  if (helper == EOF || helper == INVALID_POINTER_ERR) {
    return NULL;
  }
  Line **matr = (Line**)calloc(matr_len, sizeof(Line*));
  for (int i = 0; i < matr_len; i++) {
    int line_len = 0;
    printf("Введите длину строки: ");
    helper = getInt(&line_len, pos_or_zero);
    if (helper == EOF || helper == INVALID_POINTER_ERR) {
      matr[i] = NULL;
      EOF_clear(matr);
      return NULL;
    } 
    Line *line = getLine(line_len);
    if (line == NULL) {
      matr[i] = line;
      EOF_clear(matr);
      return NULL;
    }
    matr[i] = line;
  }
  Matrix *out = create_matrix();
  out->len = matr_len;
  out->matrix = matr;
  return out;
}

void EOF_clear(Line **matr) {
  int i = 0;
  while (matr[i] != NULL) {
    Line *f_line = matr[i];
    free(f_line->line);
    free(f_line);
    i++;
  }
  free(matr);
}

int print_matrix(Matrix* matr) {
  if (matr == NULL) {
    return INVALID_POINTER_ERR;
  }
  int matr_len = matr->len, helper = 0;
  Line **lines = matr->matrix;
  if (lines == NULL) {
    return INVALID_POINTER_ERR;
  }
  for (int i = 0; i < matr_len; i++) {
    helper = print_line(lines[i]);
    if (helper == INVALID_POINTER_ERR) {
      printf("ERROR\n");
    }
  }
  printf("\n");
  return NO_ERR;
}

int print_line(Line* line) {
  if (line == NULL) {
    return INVALID_POINTER_ERR;
  }
  int line_len = line->len;
  if (line_len == 0) {
    printf("-\n");
    return NO_ERR;
  }
  int *f_line = line->line;
  if (f_line == NULL) {
    return INVALID_POINTER_ERR;
  }
  for (int i = 0; i < line_len - 1; i++) {
    printf("%d ", f_line[i]);
  }
  printf("%d\n", f_line[line_len - 1]);
  return NO_ERR;
}

void clear_matrix(Matrix* matr) {
  if (matr != NULL && matr->matrix != NULL) {
    int matr_len = matr->len;
    Line **lines = matr->matrix;
    for (int i = 0; i < matr_len; i++) {
      if (lines[i]->line != NULL) {
        free(lines[i]->line);
      }
      if (lines[i] != NULL) {
        free(lines[i]);
      }
    }
    free(lines);
    free(matr);
  } 
  else if (matr != NULL) {
    free(matr);
  }
}

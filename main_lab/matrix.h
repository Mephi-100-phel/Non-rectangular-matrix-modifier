#ifndef MATRIX_H
#define MATRIX_H

typedef struct Line {
  int len;
  int *line;
} Line;

typedef struct Matrix {
  int len;
  Line **matrix;
} Matrix;

Matrix* create_matrix(void);
Line* create_line(void);
Line* getLine(int);
Matrix* getMatrix(void);
void EOF_clear(Line**);
int print_matrix(Matrix*);
int print_line(Line*);
void clear_matrix(Matrix*);

#endif

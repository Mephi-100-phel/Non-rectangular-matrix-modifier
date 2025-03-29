#ifndef MATRIX_H
#define MATRIX_H

typedef struct Line {
  size_t len;
  size_t offset;
} Line;

typedef struct Matrix {
  FILE* file;
  char* file_name;
  Line** matr;
  size_t len;
} Matrix;

int get_matrix(Matrix*, Matrix*);
int write_data(Matrix*, Matrix*);
int write_metadata(Matrix*);
int process_matrix(Matrix*, Matrix*);
Matrix* create_matrix(void);
Line* create_line(void);
int matrix_fill(Matrix*);
void clear_matrix(Matrix*);

#endif

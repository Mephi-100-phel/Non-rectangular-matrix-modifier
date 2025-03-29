#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "errors.h"

int main(int argc, char** argv) {
  if (argc > 3) {
    printf("Too many args\n");
    return TOO_MANY_ARGS;
  }
  if (argc == 1) {
    printf("No input file\n");
    return NO_FILE;
  }
  int helper = 0;
  Matrix* proc_matr = create_matrix();
  Matrix* out_matr = create_matrix();
  if (argc == 2) {
    out_matr->file_name = "processed_matrix.bin";
  }
  else {
    proc_matr->file_name = argv[1];
    out_matr->file_name = argv[2];
  }
  helper = get_matrix(proc_matr, out_matr);
  clear_matrix(proc_matr);
  clear_matrix(out_matr);
  return NO_ERR;
}

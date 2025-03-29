#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "matrix.h"
#include "errors.h"

#define IsInvPtr(helper) {if (helper == INVALID_POINTER) return INVALID_POINTER;}

int get_matrix(Matrix* ins_matr, Matrix* out_matr) {
  if (ins_matr == NULL || ins_matr->file_name == NULL) {
    return INVALID_POINTER;
  }
  ins_matr->file = fopen(ins_matr->file_name, "r");
  out_matr->file = fopen(out_matr->file_name, "w");
  fread(&(ins_matr->len), sizeof(size_t), 1, ins_matr->file);
  ins_matr->matr = (Line**)calloc(ins_matr->len, sizeof(Line*));
  int helper = matrix_fill(ins_matr);
  IsInvPtr(helper);
  helper = process_matrix(ins_matr, out_matr);
  IsInvPtr(helper);
  helper = write_metadata(out_matr);
  helper = write_data(ins_matr, out_matr);
  IsInvPtr(helper);
  return NO_ERR;
}

int matrix_fill(Matrix* matr) {
  if (matr == NULL) {
    return INVALID_POINTER;
  }
  for (int i = 0; i < matr->len; i++) {
    Line* line = create_line();
    fread(&(line->len), sizeof(size_t), 1, matr->file);
    fread(&(line->offset), sizeof(size_t), 1, matr->file);
    (matr->matr)[i] = line;
  }
  return NO_ERR;
}

int write_data(Matrix* src_matr, Matrix* dest_matr) {
  if (src_matr == NULL || dest_matr == NULL) {
    return INVALID_POINTER;
  }
  int elem = 0;
  for (int i = 0; i < src_matr->len; i++) {
    Line* src_line = (src_matr->matr)[i];
    Line* dest_line = (dest_matr->matr)[i];
    fseek(src_matr->file, src_line->offset, SEEK_SET);
    fseek(dest_matr->file, dest_line->offset, SEEK_SET);
    for (int ind = 0; ind < dest_line->len; ind++) {
      fread(&elem, sizeof(int), 1, src_matr->file);
      fwrite(&elem, sizeof(int), 1, dest_matr->file);
    }
  }
  return NO_ERR;
}

int process_matrix(Matrix* ins_matr, Matrix* out_matr) {
  if (ins_matr == NULL || out_matr == NULL) {
    return INVALID_POINTER;
  }
  int total_offset_decrese = 0;
  out_matr->len = ins_matr->len;
  out_matr->matr = (Line**)calloc(out_matr->len, sizeof(Line*));
  for (int i = 0; i < out_matr->len; i++) {
    int max_elem_ind = -1, max = INT_MIN, elem = 0, prev_max = 0;
    Line* line = (ins_matr->matr)[i];
    fseek(ins_matr->file, line->offset, SEEK_SET);
    for (int ind = 0; ind < line->len; ind++) {
      fread(&elem, sizeof(int), 1, ins_matr->file);
      prev_max = max;
      max = (max < elem) ? elem : max;
      max_elem_ind = (prev_max != max || elem == max) ? ind : max_elem_ind;
    } 
    (out_matr->matr)[i] = create_line();
    ((out_matr->matr)[i])->len = max_elem_ind + 1;
    ((out_matr->matr)[i])->offset = line->offset - total_offset_decrese;
    total_offset_decrese += (line->len - max_elem_ind - 1) * sizeof(int);
  }
  return NO_ERR;
}

int write_metadata(Matrix* matr) {
  if (matr == NULL || matr->file == NULL) {
    return INVALID_POINTER;
  }
  fwrite(&(matr->len), sizeof(size_t), 1, matr->file);
  for (int i = 0; i < matr->len; i++) {
    Line* line = (matr->matr)[i];
    fwrite(&(line->len), sizeof(size_t), 1, matr->file);
    fwrite(&(line->offset), sizeof(size_t), 1, matr->file);
  }
  return NO_ERR;
}

Matrix* create_matrix(void) {
  return (Matrix*)calloc(1, sizeof(Matrix));
}

Line* create_line(void) {
  return (Line*)calloc(1, sizeof(Line));
}

void clear_matrix(Matrix* matr) {
  if (matr != NULL) {
    for (int i = 0; i < matr->len; i++) {
      free((matr->matr)[i]);
    }
    free(matr->matr);
    fclose(matr->file);
  }
  free(matr);
}

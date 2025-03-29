#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  size_t matr_len = random() % 12, line_write_offset = 0, metadata_write_offset = sizeof(size_t);
  FILE* file = fopen(argv[1], "w+");
  printf("%d\n", matr_len);
  fwrite(&matr_len, sizeof(size_t), 1, file);
  line_write_offset = sizeof(size_t) + matr_len * 2 * sizeof(size_t);
  for (int i = 0; i < matr_len; i++) {
    fseek(file, metadata_write_offset, SEEK_SET);
    size_t line_len = random() % 15;
    printf("%d ", line_len);
    fwrite(&line_len, sizeof(size_t), 1, file);
    printf("%d ", line_write_offset);
    fwrite(&line_write_offset, sizeof(size_t), 1, file);
    printf("%d ", metadata_write_offset);
    fseek(file, line_write_offset, SEEK_SET);
    for (int m = 0; m < line_len; m++) {
      int elem = random() % 10;
      printf("%d ", elem);
      fwrite(&elem, sizeof(int), 1, file);
    }
    printf("\n");
    line_write_offset += sizeof(int) * line_len;
    metadata_write_offset += sizeof(size_t) * 2;
  }
  return 0;
}

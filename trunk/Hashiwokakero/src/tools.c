#include "tools.h"

void generate_game_file(Grid* grid,
                        unsigned size_grid,
                        unsigned nb_island,
                        char* g_value) {
  FILE* output = NULL;
  remove("output.txt");
  output = fopen("output.txt", "w+");
  FILE* output_final = NULL;
  output_final = fopen(g_value, "w");
  if (output_final == NULL) { /* Check if the file exists. */
    fprintf(stderr, "Error writing file.\n");
    exit(EXIT_FAILURE);
  }
  char buf[1];
  for (unsigned i = 0; i < size_grid * size_grid; ++i) {
    fwrite("_", sizeof(char), 1, output);
  }
  rewind(output);
  for (unsigned i = 0; i < nb_island; ++i) {
    int position = get_x(grid->islands[i].position) +
                   size_grid * get_y(grid->islands[i].position);
    char value = get_value(grid->islands[i].information_island) + INT_TO_CHAR;
    fseek(output, position, SEEK_SET);
    fwrite(&value, sizeof(char), 1, output);
    rewind(output);
  }
  for (unsigned i = 0; i < grid->pos; ++i) {
    int position = grid->bridges_x[i] + size_grid * grid->bridges_y[i];
    fseek(output, position, SEEK_SET);
    if (grid->bridges_d[i] == 0) {
      fwrite("S", sizeof(char), 1, output);
    } else {
      fwrite("D", sizeof(char), 1, output);
    }
    rewind(output);
  }
  for (unsigned i = 0; i < size_grid; ++i) {
    for (unsigned j = 0; j < size_grid; ++j) {
      fread(&buf, sizeof(char), 1, output);
      fwrite(&buf, sizeof(char), 1, output_final);
    }
    fwrite("\n", sizeof(char), 1, output_final);
  }
  remove("output.txt");
  fclose(output);
  fclose(output_final);
}

unsigned distance(unsigned a, unsigned b) {
  if (a < b)
    return b - a;
  return a - b;
}

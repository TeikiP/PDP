#include "island.h"
#include "processing.h"
#include "tools.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE_GRID \
  255 /* constant for the max of the size of the grid we want */

/* Checks the file and returns the number of islands */
unsigned get_nb_island(FILE* _file) {
  unsigned nb_island = 0;
  if (_file == NULL) /* Check if the file exists. */
    printf("Error reading file.\n");
  else {
    char char_read;
    char_read = fgetc(_file);
    while (char_read != EOF) {
      if ((char_read - INT_TO_CHAR < 9) && (char_read - INT_TO_CHAR > 0)) {
        nb_island++;
      }
      char_read = fgetc(_file);
    }
  }
  return nb_island;
}

/* Checks the file and returns the number of islands */
unsigned get_size_grid(FILE* _file) {
  unsigned size_grid = 0;
  if (_file == NULL) /* Check if the file exists. */
    printf("Error reading file.\n");
  else {
    char char_read;
    char_read = fgetc(_file);
    while (char_read != '\n') {
      size_grid++;
      char_read = fgetc(_file);
    }
  }
  return size_grid;
}

/* Checks the file and fills the Grid with the different islands
 *    and their informations */
void fill_grid(FILE* _file, Grid* grid, unsigned size_grid) {
  char char_read;
  unsigned i = 0;
  unsigned j = 0;
  unsigned a = 0;
  unsigned cpt_to_validate = 0;
  char_read = fgetc(_file);
  while (char_read != EOF) {
    if (char_read == '_') { /* Replaces _ by 0 in Grid. */
      j++;
      cpt_to_validate++;
    } else if (char_read == '\n') {
      if (j != size_grid) {
        fprintf(stderr, "Invalid size of the grid.\n");
        free(grid->bridges_x);
        free(grid->bridges_y);
        free(grid->islands);
        free(grid);
        fclose(_file);
        exit(EXIT_FAILURE);
      }
      i++;
      j = 0;
    } else if ((char_read - INT_TO_CHAR < 9) && (char_read - INT_TO_CHAR > 0)) {
      set_x(&(grid->islands[a].position), j);
      set_y(&(grid->islands[a].position), i);
      grid->islands[a].information_island = char_read - INT_TO_CHAR;
      j++;
      a++;
      cpt_to_validate++;
    } else {
      fprintf(stderr, "Invalid character : %c\n", char_read);
      free(grid->bridges_x);
      free(grid->bridges_y);
      free(grid->islands);
      free(grid);
      fclose(_file);
      exit(EXIT_FAILURE);
    }
    char_read = fgetc(_file);
  }
  if (cpt_to_validate != size_grid * size_grid) {
    free(grid->bridges_x);
    free(grid->bridges_y);
    free(grid->islands);
    free(grid);
    fclose(_file);
    fprintf(stderr, "Invalid size of the grid.\n");
    exit(EXIT_FAILURE);
  }
}

/* Print the grid in the terminal */
void print_grid(Grid* grid, unsigned nb_island, int verbose) {
  if (verbose == 1) {
    for (unsigned i = 0; i < nb_island; i++) {
      printf("Island[%d], position %d %d: ", i,
             get_x(grid->islands[i].position),
             get_y(grid->islands[i].position));
      if (get_nb_bridge_left(grid->islands[i].information_island) > 0) {
        printf("left bridges: %d, ",
               get_nb_bridge_left(grid->islands[i].information_island));
      }
      if (get_nb_bridge_right(grid->islands[i].information_island) > 0) {
        printf("right bridges: %d, ",
               get_nb_bridge_right(grid->islands[i].information_island));
      }
      if (get_nb_bridge_up(grid->islands[i].information_island) > 0) {
        printf("up bridges: %d, ",
               get_nb_bridge_up(grid->islands[i].information_island));
      }
      if (get_nb_bridge_down(grid->islands[i].information_island) > 0) {
        printf("down bridges: %d, ",
               get_nb_bridge_down(grid->islands[i].information_island));
      }
      printf("\n");
    }

    printf("Total number of islands : %d\nNumber of finished islands : %d\n",
           nb_island, get_nb_island_finished(grid, nb_island));
  }
  if (is_game_over(grid, nb_island) == 1) {
    printf("Solved.\n");
  } else {
    printf("Unsolved.\n");
  }
  printf("Is the grid correct : %d\n", is_correct(grid, nb_island));
}

/* Checks the Grid and find the neighbors of each island
 * and store the information in the islands */
void fill_grid_neighbor(Grid* grid, unsigned size_grid, unsigned nb_island) {
  unsigned position_neighbor = nb_island + 1;
  for (unsigned i = 0; i < nb_island; i++) {
    if ((get_x(grid->islands[i].position) != 0) &&
        (grid->islands[i].left_neighbor == NULL)) {
      for (unsigned j = 0; j < nb_island && j != i; j++) {
        if ((get_y(grid->islands[j].position) ==
             get_y(grid->islands[i].position)) &&
            (get_x(grid->islands[j].position) <
             get_x(grid->islands[i].position))) {
          if (position_neighbor == nb_island + 1)
            position_neighbor = j;
          else {
            if ((distance(get_x(grid->islands[position_neighbor].position),
                          get_x(grid->islands[i].position))) >
                (distance(get_x(grid->islands[j].position),
                          get_x(grid->islands[i].position))))
              position_neighbor = j;
          }
        }
      }
      if (position_neighbor < nb_island + 1) {
        if ((get_value(grid->islands[i].information_island) != 1) ||
            (get_value(grid->islands[position_neighbor].information_island) !=
             1) ||
            (nb_island == 2)) {
          grid->islands[i].left_neighbor = &(grid->islands[position_neighbor]);
          grid->islands[position_neighbor].right_neighbor = &(grid->islands[i]);
        }
      }
      position_neighbor = nb_island + 1;
    }
    if ((get_x(grid->islands[i].position) != size_grid) &&
        (grid->islands[i].right_neighbor == NULL)) {
      for (unsigned j = 0; j < nb_island && j != i; j++) {
        if ((get_y(grid->islands[j].position) ==
             get_y(grid->islands[i].position)) &&
            (get_x(grid->islands[j].position) >
             get_x(grid->islands[i].position))) {
          if (position_neighbor == nb_island + 1)
            position_neighbor = j;
          else {
            if ((distance(get_x(grid->islands[position_neighbor].position),
                          get_x(grid->islands[i].position))) >
                (distance(get_x(grid->islands[j].position),
                          get_x(grid->islands[i].position))))
              position_neighbor = j;
          }
        }
      }
      if (position_neighbor < nb_island + 1) {
        if ((get_value(grid->islands[i].information_island) != 1) ||
            (get_value(grid->islands[position_neighbor].information_island) !=
             1) ||
            (nb_island == 2)) {
          grid->islands[i].right_neighbor = &(grid->islands[position_neighbor]);
          grid->islands[position_neighbor].left_neighbor = &(grid->islands[i]);
        }
      }
      position_neighbor = nb_island + 1;
    }
    if ((get_y(grid->islands[i].position) != 0) &&
        (grid->islands[i].up_neighbor == NULL)) {
      for (unsigned j = 0; j < nb_island && j != i; j++) {
        if ((get_x(grid->islands[j].position) ==
             get_x(grid->islands[i].position)) &&
            (get_y(grid->islands[j].position) <
             get_y(grid->islands[i].position))) {
          if (position_neighbor == nb_island + 1)
            position_neighbor = j;
          else {
            if ((distance(get_y(grid->islands[position_neighbor].position),
                          get_y(grid->islands[i].position))) >
                (distance(get_y(grid->islands[j].position),
                          get_y(grid->islands[i].position))))
              position_neighbor = j;
          }
        }
      }
      if (position_neighbor < nb_island + 1) {
        if ((get_value(grid->islands[i].information_island) != 1) ||
            (get_value(grid->islands[position_neighbor].information_island) !=
             1) ||
            (nb_island == 2)) {
          grid->islands[i].up_neighbor = &(grid->islands[position_neighbor]);
          grid->islands[position_neighbor].down_neighbor = &(grid->islands[i]);
        }
      }
      position_neighbor = nb_island + 1;
    }
    if ((get_y(grid->islands[i].position) != size_grid) &&
        (grid->islands[i].down_neighbor == NULL)) {
      for (unsigned j = 0; j < nb_island && j != i; j++) {
        if ((get_x(grid->islands[j].position) ==
             get_x(grid->islands[i].position)) &&
            (get_y(grid->islands[j].position) >
             get_y(grid->islands[i].position))) {
          if (position_neighbor == nb_island + 1)
            position_neighbor = j;
          else {
            if ((distance(get_y(grid->islands[position_neighbor].position),
                          get_y(grid->islands[i].position))) >
                (distance(get_y(grid->islands[j].position),
                          get_y(grid->islands[i].position))))
              position_neighbor = j;
          }
        }
      }
      if (position_neighbor < nb_island + 1) {
        if ((get_value(grid->islands[i].information_island) != 1) ||
            (get_value(grid->islands[position_neighbor].information_island) !=
             1) ||
            (nb_island == 2)) {
          grid->islands[i].down_neighbor = &(grid->islands[position_neighbor]);
          grid->islands[position_neighbor].up_neighbor = &(grid->islands[i]);
        }
      }
      position_neighbor = nb_island + 1;
    }
  }
}

/* Generates a grid with the chosen size and the chosen number of islands and
* prints it in the file at the chosen location */
void simple_generator(unsigned size_grid,
                      unsigned nb_island,
                      char* d_value,
                      unsigned verbose) {
  Grid* grid = malloc(sizeof(Grid));
  if (grid == NULL) {
    fprintf(stderr, "Allocation error.\n");
    exit(EXIT_FAILURE);
  }
  if (d_value == NULL) {
    fprintf(stderr, "No output file specified. Closing.\n");
    free(grid);
    exit(EXIT_FAILURE);
  }

  initialize(grid, size_grid, nb_island);

  unsigned x, y, nb_island_chosen;

  srand(time(NULL));

  unsigned pos_island_chosen = 0;
  unsigned dir_chosen = 0;
  unsigned dist_chosen = 0;
  unsigned nb_bridge_chosen = 0;
  unsigned failure = 0;
  unsigned nb_try = 0;
  unsigned does_island_exist = 0;
  while (nb_try < size_grid * 10) {
    x = rand() % size_grid;
    y = rand() % size_grid;
    set_x(&(grid->islands[0].position), x);
    set_y(&(grid->islands[0].position), y);
    nb_island_chosen = 1;
    while (nb_island_chosen < nb_island) {
      pos_island_chosen = rand() % nb_island_chosen;
      dir_chosen = rand() % (RIGHT + 1);
      if (dir_chosen == UP &&
          get_y(grid->islands[pos_island_chosen].position) > 1 &&
          grid->islands[pos_island_chosen].up_neighbor == NULL) {
        dist_chosen =
            rand() % (get_y(grid->islands[pos_island_chosen].position) - 1) + 1;
        if (dist_chosen > nb_try)
          dist_chosen -= nb_try;
        else if (dist_chosen > 1)
          dist_chosen = rand() % 2 + 1;
        set_x(&(grid->islands[nb_island_chosen].position),
              get_x(grid->islands[pos_island_chosen].position));
        set_y(
            &(grid->islands[nb_island_chosen].position),
            get_y(grid->islands[pos_island_chosen].position) - dist_chosen - 1);
        if (is_locked(&(grid->islands[pos_island_chosen]),
                      &(grid->islands[nb_island_chosen]), UP, grid) == 0 &&
            is_island_on_the_way(&(grid->islands[pos_island_chosen]),
                                 &(grid->islands[nb_island_chosen]), UP, grid,
                                 nb_island_chosen - 1) == 0 &&
            is_place_unavailable(grid->islands[nb_island_chosen], grid,
                                 size_grid, nb_island_chosen - 1) == 0) {
          does_island_exist =
              island_exist(get_x(grid->islands[nb_island_chosen].position),
                           get_y(grid->islands[nb_island_chosen].position),
                           grid, nb_island_chosen - 1);
          if (does_island_exist == nb_island_chosen) {
            nb_bridge_chosen = rand() % 2 + 1;
            set_nb_bridge_up(
                &(grid->islands[pos_island_chosen].information_island),
                nb_bridge_chosen);
            set_nb_bridge_down(
                &(grid->islands[nb_island_chosen].information_island),
                nb_bridge_chosen);

            grid->islands[pos_island_chosen].up_neighbor =
                &(grid->islands[nb_island_chosen]);
            grid->islands[nb_island_chosen].down_neighbor =
                &(grid->islands[pos_island_chosen]);
            lock(&(grid->islands[pos_island_chosen]),
                 grid->islands[pos_island_chosen].up_neighbor, UP, grid);

            nb_island_chosen++;
            failure = 0;
          } else if (grid->islands[does_island_exist].position ==
                     grid->islands[nb_island_chosen].position) {
            nb_bridge_chosen = rand() % 2 + 1;
            set_nb_bridge_up(
                &(grid->islands[pos_island_chosen].information_island),
                nb_bridge_chosen);
            set_nb_bridge_down(
                &(grid->islands[does_island_exist].information_island),
                nb_bridge_chosen);

            grid->islands[pos_island_chosen].up_neighbor =
                &(grid->islands[does_island_exist]);
            grid->islands[does_island_exist].down_neighbor =
                &(grid->islands[pos_island_chosen]);
            lock(&(grid->islands[pos_island_chosen]),
                 grid->islands[pos_island_chosen].up_neighbor, UP, grid);
            failure = 0;
          }
        } else {
          failure++;
        }

      } else if (dir_chosen == DOWN &&
                 get_y(grid->islands[pos_island_chosen].position) <
                     size_grid - 2 &&
                 grid->islands[pos_island_chosen].down_neighbor == NULL) {
        dist_chosen =
            rand() % (size_grid -
                      get_y(grid->islands[pos_island_chosen].position) - 2) +
            1;
        if (dist_chosen > nb_try)
          dist_chosen -= nb_try;
        else if (dist_chosen > 1)
          dist_chosen = rand() % 2 + 1;
        set_x(&(grid->islands[nb_island_chosen].position),
              get_x(grid->islands[pos_island_chosen].position));
        set_y(
            &(grid->islands[nb_island_chosen].position),
            get_y(grid->islands[pos_island_chosen].position) + dist_chosen + 1);
        if (is_locked(&(grid->islands[pos_island_chosen]),
                      &(grid->islands[nb_island_chosen]), DOWN, grid) == 0 &&
            is_island_on_the_way(&(grid->islands[pos_island_chosen]),
                                 &(grid->islands[nb_island_chosen]), DOWN, grid,
                                 nb_island_chosen - 1) == 0 &&
            is_place_unavailable(grid->islands[nb_island_chosen], grid,
                                 size_grid, nb_island_chosen - 1) == 0) {
          does_island_exist =
              island_exist(get_x(grid->islands[nb_island_chosen].position),
                           get_y(grid->islands[nb_island_chosen].position),
                           grid, nb_island_chosen - 1);
          if (does_island_exist == nb_island_chosen) {
            nb_bridge_chosen = rand() % 2 + 1;
            set_nb_bridge_down(
                &(grid->islands[pos_island_chosen].information_island),
                nb_bridge_chosen);
            set_nb_bridge_up(
                &(grid->islands[nb_island_chosen].information_island),
                nb_bridge_chosen);

            grid->islands[pos_island_chosen].down_neighbor =
                &(grid->islands[nb_island_chosen]);
            grid->islands[nb_island_chosen].up_neighbor =
                &(grid->islands[pos_island_chosen]);
            lock(&(grid->islands[pos_island_chosen]),
                 grid->islands[pos_island_chosen].down_neighbor, DOWN, grid);

            nb_island_chosen++;
            failure = 0;
          } else if (grid->islands[does_island_exist].position ==
                     grid->islands[nb_island_chosen].position) {
            nb_bridge_chosen = rand() % 2 + 1;
            set_nb_bridge_down(
                &(grid->islands[pos_island_chosen].information_island),
                nb_bridge_chosen);
            set_nb_bridge_up(
                &(grid->islands[does_island_exist].information_island),
                nb_bridge_chosen);

            grid->islands[pos_island_chosen].down_neighbor =
                &(grid->islands[does_island_exist]);
            grid->islands[does_island_exist].up_neighbor =
                &(grid->islands[pos_island_chosen]);
            lock(&(grid->islands[pos_island_chosen]),
                 grid->islands[pos_island_chosen].down_neighbor, DOWN, grid);
            failure = 0;
          }
        } else {
          failure++;
        }
      } else if (dir_chosen == LEFT &&
                 get_x(grid->islands[pos_island_chosen].position) > 1 &&
                 grid->islands[pos_island_chosen].left_neighbor == NULL) {
        dist_chosen =
            rand() % (get_x(grid->islands[pos_island_chosen].position) - 1) + 1;
        if (dist_chosen > nb_try)
          dist_chosen -= nb_try;
        else if (dist_chosen > 1)
          dist_chosen = rand() % 2 + 1;
        set_x(
            &(grid->islands[nb_island_chosen].position),
            get_x(grid->islands[pos_island_chosen].position) - dist_chosen - 1);
        set_y(&(grid->islands[nb_island_chosen].position),
              get_y(grid->islands[pos_island_chosen].position));
        if (is_locked(&(grid->islands[pos_island_chosen]),
                      &(grid->islands[nb_island_chosen]), LEFT, grid) == 0 &&
            is_island_on_the_way(&(grid->islands[pos_island_chosen]),
                                 &(grid->islands[nb_island_chosen]), LEFT, grid,
                                 nb_island_chosen - 1) == 0 &&
            is_place_unavailable(grid->islands[nb_island_chosen], grid,
                                 size_grid, nb_island_chosen - 1) == 0) {
          does_island_exist =
              island_exist(get_x(grid->islands[nb_island_chosen].position),
                           get_y(grid->islands[nb_island_chosen].position),
                           grid, nb_island_chosen - 1);
          if (does_island_exist == nb_island_chosen) {
            nb_bridge_chosen = rand() % 2 + 1;
            set_nb_bridge_left(
                &(grid->islands[pos_island_chosen].information_island),
                nb_bridge_chosen);
            set_nb_bridge_right(
                &(grid->islands[nb_island_chosen].information_island),
                nb_bridge_chosen);

            grid->islands[pos_island_chosen].left_neighbor =
                &(grid->islands[nb_island_chosen]);
            grid->islands[nb_island_chosen].right_neighbor =
                &(grid->islands[pos_island_chosen]);
            lock(&(grid->islands[pos_island_chosen]),
                 grid->islands[pos_island_chosen].left_neighbor, LEFT, grid);

            nb_island_chosen++;
            failure = 0;
          } else if (grid->islands[does_island_exist].position ==
                     grid->islands[nb_island_chosen].position) {
            nb_bridge_chosen = rand() % 2 + 1;
            set_nb_bridge_left(
                &(grid->islands[pos_island_chosen].information_island),
                nb_bridge_chosen);
            set_nb_bridge_right(
                &(grid->islands[does_island_exist].information_island),
                nb_bridge_chosen);

            grid->islands[pos_island_chosen].left_neighbor =
                &(grid->islands[does_island_exist]);
            grid->islands[does_island_exist].right_neighbor =
                &(grid->islands[pos_island_chosen]);
            lock(&(grid->islands[pos_island_chosen]),
                 grid->islands[pos_island_chosen].left_neighbor, LEFT, grid);
            failure = 0;
          }
        } else {
          failure++;
        }
      } else if (dir_chosen == RIGHT &&
                 get_x(grid->islands[pos_island_chosen].position) <
                     size_grid - 2 &&
                 grid->islands[pos_island_chosen].right_neighbor == NULL) {
        dist_chosen =
            rand() % (size_grid -
                      get_x(grid->islands[pos_island_chosen].position) - 2) +
            1;
        if (dist_chosen > nb_try)
          dist_chosen -= nb_try;
        else if (dist_chosen > 1)
          dist_chosen = rand() % 2 + 1;
        set_x(
            &(grid->islands[nb_island_chosen].position),
            get_x(grid->islands[pos_island_chosen].position) + dist_chosen + 1);
        set_y(&(grid->islands[nb_island_chosen].position),
              get_y(grid->islands[pos_island_chosen].position));
        if (is_locked(&(grid->islands[pos_island_chosen]),
                      &(grid->islands[nb_island_chosen]), RIGHT, grid) == 0 &&
            is_island_on_the_way(&(grid->islands[pos_island_chosen]),
                                 &(grid->islands[nb_island_chosen]), RIGHT,
                                 grid, nb_island_chosen - 1) == 0 &&
            is_place_unavailable(grid->islands[nb_island_chosen], grid,
                                 size_grid, nb_island_chosen - 1) == 0) {
          does_island_exist =
              island_exist(get_x(grid->islands[nb_island_chosen].position),
                           get_y(grid->islands[nb_island_chosen].position),
                           grid, nb_island_chosen - 1);
          if (does_island_exist == nb_island_chosen) {
            nb_bridge_chosen = rand() % 2 + 1;
            set_nb_bridge_right(
                &(grid->islands[pos_island_chosen].information_island),
                nb_bridge_chosen);
            set_nb_bridge_left(
                &(grid->islands[nb_island_chosen].information_island),
                nb_bridge_chosen);

            grid->islands[pos_island_chosen].right_neighbor =
                &(grid->islands[nb_island_chosen]);
            grid->islands[nb_island_chosen].left_neighbor =
                &(grid->islands[pos_island_chosen]);
            lock(&(grid->islands[pos_island_chosen]),
                 grid->islands[pos_island_chosen].right_neighbor, RIGHT, grid);

            nb_island_chosen++;
            failure = 0;
          } else if (grid->islands[does_island_exist].position ==
                     grid->islands[nb_island_chosen].position) {
            nb_bridge_chosen = rand() % 2 + 1;
            set_nb_bridge_right(
                &(grid->islands[pos_island_chosen].information_island),
                nb_bridge_chosen);
            set_nb_bridge_left(
                &(grid->islands[does_island_exist].information_island),
                nb_bridge_chosen);

            grid->islands[pos_island_chosen].right_neighbor =
                &(grid->islands[does_island_exist]);
            grid->islands[does_island_exist].left_neighbor =
                &(grid->islands[pos_island_chosen]);
            lock(&(grid->islands[pos_island_chosen]),
                 grid->islands[pos_island_chosen].right_neighbor, RIGHT, grid);
            failure = 0;
          }
        } else {
          failure++;
        }
      } else {
        failure++;
      }
      if (failure >= size_grid * size_grid * 2) {
        nb_try++;
        failure = 0;
        if (nb_try < size_grid * 10) {
          reset_grid(grid, size_grid, nb_island);
        }
        break;
      }
    }
    if (nb_island_chosen == nb_island) {
      break;
    }
  }
  for (unsigned i = 0; i < nb_island; i++) {
    set_value(&(grid->islands[i].information_island),
              get_nb_bridge(grid->islands[i]));
  }

  print_grid(grid, nb_island, verbose);

  for (unsigned i = 0; i < (size_grid * size_grid); i++) {
    grid->bridges_x[i] = 0;
    grid->bridges_y[i] = 0;
    grid->bridges_d[i] = 0;
  }
  grid->pos = 0;

  generate_game_file(grid, size_grid, nb_island_chosen, d_value);

  if (nb_island_chosen != nb_island) {
    fprintf(stderr,
            "The generator failed to find the number of islands asked.\n");
    fprintf(stderr, "The islands he found are still displayed.\n");
    fprintf(stderr,
            "You can try with a higher size for the grid if it doesn't work "
            "and that you want this number of islands\n");
  }

  free(grid->bridges_x);
  free(grid->bridges_y);
  free(grid->bridges_d);
  free(grid->islands);
  free(grid);
}

/* Tries to solve the chosen grid with heuristics only */
void simple_solver(Grid* grid, unsigned nb_island) {
  for (unsigned i = 0; i < nb_island; i++) {
    heuristic_n1(&(grid->islands[i]), grid);
    heuristic_n2(&(grid->islands[i]), grid);
    heuristic_n3(&(grid->islands[i]), grid);
  }
  while (grid->heuristic_used > 0) {
    grid->heuristic_used = 0;
    for (unsigned i = 0; i < nb_island; i++) {
      heuristic_neighbor_finished(&(grid->islands[i]), grid);
    }
  }
}

/* Tries to solve the chosen grid with simple_solver and then the backtracking
 */
void complex_solver(Grid* grid,
                    unsigned size_grid,
                    unsigned nb_island,
                    unsigned verbose,
                    time_t timer,
                    int max_time,
                    int time_flag) {
  simple_solver(grid, nb_island);

  if (is_correct(grid, nb_island) != 1) {
    print_grid(grid, nb_island, 1);
    fprintf(stderr, "Simple solver found an incorrect grid error. ");
    fprintf(stderr, "Impossible for the backtracking to work.\n");
    free(grid->bridges_x);
    free(grid->bridges_y);
    free(grid->islands);
    free(grid);
    exit(EXIT_FAILURE);
  }

  Stack s = create_stack();

  insert_value(s, *grid, size_grid, nb_island);

  grid->chosen_island = choose_and_draw_bridge(grid, nb_island);

  time_t timer2;

  while (is_game_over(grid, nb_island) != 1) {
    timer2 = time(NULL);
    if (time_flag == 1 && (timer2 - timer) > max_time) {
      print_grid(&(s->tab[s->size - 1]), nb_island, 1);
      fprintf(stderr,
              "Time's up! Sorry. Here's the last grid found by the solver.\n");
      break;
      // exit(EXIT_FAILURE);
    }
    for (unsigned i = 0; i < grid->pos; ++i) {
    }
    if ((is_correct(grid, nb_island) == 1) && (grid->chosen_island != NULL)) {
      insert_value(s, *grid, size_grid, nb_island);
      for (unsigned i = 0; i < nb_island; i++) {
        grid->islands[i].information_backtracking = 0;
      }
    }

    if (grid->chosen_island == NULL) {
      for (unsigned i = 0; i < nb_island; i++) {
        grid->islands[i].information_backtracking = 0;
      }
      copy_game(s->tab[s->size - 1], grid, size_grid, nb_island);
      delete_game(s, &(s->tab[s->size - 1]));
      copy_game_but_not_backtracking(s->tab[s->size - 1], grid, size_grid,
                                     nb_island);
    }

    if (is_correct(grid, nb_island) != 1) {
      copy_game_but_not_backtracking(s->tab[s->size - 1], grid, size_grid,
                                     nb_island);
    }

    grid->chosen_island = choose_and_draw_bridge(grid, nb_island);

    if (grid->chosen_island != NULL) {
      if (verbose == 1) {
        printf("Chosen island: %d %d\n", get_x(grid->chosen_island->position),
               get_y(grid->chosen_island->position));
        printf("Top bridges amount: %d\n",
               get_nb_bridge_up(grid->chosen_island->information_island));
        printf("Down bridges amount: %d\n",
               get_nb_bridge_down(grid->chosen_island->information_island));
        printf("Left bridges amount: %d\n",
               get_nb_bridge_left(grid->chosen_island->information_island));
        printf("Right bridges amount: %d\n",
               get_nb_bridge_right(grid->chosen_island->information_island));
        printf("Backtracking information: %d\n",
               grid->chosen_island->information_backtracking);
      }

      grid->heuristic_used = 1;
      while (grid->heuristic_used > 0) {
        grid->heuristic_used = 0;
        for (unsigned i = 0; i < nb_island; i++) {
          heuristic_neighbor_finished(&(grid->islands[i]), grid);
        }
      }
    }
    print_grid(grid, nb_island, verbose);
    if (verbose == 1) {
      printf("taille Stack %d\n", s->size);
    }
  }

  delete_stack(s);
}

/* Main */

int main(int argc, char** argv) {
  time_t timer;
  int c;
  int time_flag = 0;
  int max_time = 0;
  int solver = 0;
  int generate = 0;
  int verbose = 0;
  int output = 0;
  char* o_value = NULL;
  char* f_value = NULL;
  char* s_value = NULL;
  char* i_value = NULL;
  char* d_value = NULL;
  char* t_value = NULL;
  int size = 0;
  int islands = 0;
  timer = time(NULL);

  while ((c = getopt(argc, argv, "o:gvf:s:i:d:t:")) != -1)
    switch (c) {
      case 'o':
        o_value = optarg;
        output = 1;
        break;
      case 't':
        t_value = optarg;
        time_flag = 1;
        max_time = atoi(t_value);
        break;
      case 'g':
        generate = 1;
        break;
      case 'v':
        verbose = 1;
        break;
      case 'f':
        solver = 1;
        f_value = optarg;
        break;
      case 'i':
        i_value = optarg;
        islands = atoi(i_value);
        break;
      case 'd':
        d_value = optarg;
        break;
      case 's':
        s_value = optarg;
        size = atoi(s_value);
        break;
      case '?':
        fprintf(stderr, "Unknown option `-%c'.\n", c);
        return 1;
    }

  /* Checks if there are enough arguments */
  if (argc < 2) {
    fprintf(stderr, "Not enough arguments.\n");
    exit(EXIT_FAILURE);
  }

  if (generate == 1) {
    if (size > MAX_SIZE_GRID) {
      fprintf(stderr, "Error size of the grid too high.\n");
      exit(EXIT_FAILURE);
    }
    if (size < 2) {
      fprintf(stderr, "Error size of the grid too small.\n");
      exit(EXIT_FAILURE);
    }
    if (islands > (size * size / 2)) {
      fprintf(stderr,
              "Impossible to create a grid with a number of islands superior "
              "or equals to "
              "half the size of the grid\n");
      exit(EXIT_FAILURE);
    }
    if (islands < 1) {
      fprintf(stderr, "Error number of islands not defined.\n");
      fprintf(stderr,
              "The number of islands will be chosen randomly between 1 and the "
              "quarter of the size of the grid.\n");
      srand(time(NULL));
      islands = rand() % (size * size / 4) + 1;
    }
    simple_generator(size, islands, d_value, verbose);
  }

  if (solver == 1) {
    /* Opens the file and check if it succeeded. */
    FILE* inputFile;
    inputFile = fopen(f_value, "r");
    if (inputFile == NULL) { /* Check if the file exists. */
      fprintf(stderr, "Error reading file.\n");
      exit(EXIT_FAILURE);
    }

    unsigned size_grid = get_size_grid(inputFile);
    if (size_grid > MAX_SIZE_GRID) {
      fprintf(stderr, "Error size of the grid too high.\n");
      fclose(inputFile);
      exit(EXIT_FAILURE);
    }

    rewind(inputFile);
    unsigned nb_island = get_nb_island(inputFile); /* number of islands */
    if (nb_island < 1) {
      fprintf(stderr, "Error : no islands found.\n");
      fclose(inputFile);
      exit(EXIT_FAILURE);
    }
    rewind(inputFile);

    /* Allocation pour grid */
    Grid* grid = malloc(sizeof(Grid));
    if (grid == NULL) {
      fprintf(stderr, "Allocation error.\n");
      fclose(inputFile);
      exit(EXIT_FAILURE);
    }

    /* Initialize the Grid and fills it with informations of the islands */
    initialize(grid, size_grid, nb_island);
    fill_grid(inputFile, grid, size_grid);
    fill_grid_neighbor(grid, size_grid, nb_island);
    fclose(inputFile);

    /* Uses a complex solver to try to solve the Grid */
    complex_solver(grid, size_grid, nb_island, verbose, timer, max_time,
                   time_flag);
    bridge_doubler(grid, nb_island);

    /* Prints the result */
    print_grid(grid, nb_island, 1);
    /* Generate the state of the grid */
    if (output == 1) {
      generate_game_file(grid, size_grid, nb_island, o_value);
    }
    free(grid->bridges_x);
    free(grid->bridges_y);
    free(grid->bridges_d);
    free(grid->islands);
    free(grid);
  }
  return (0);
}

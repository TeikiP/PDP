#include <stdio.h>
#include <stdlib.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define INT_TO_CHAR 48 /* constant to translate an int into a char*/

int nb_island;              /* number of islands */
int pos = 0;

/* structure to store the informations of the islands */
typedef struct Island Island;
/* structure to store all the islands */
typedef struct Island_list Island_list;

struct Island_list {
  Island* islands;
};

struct Island {
  int x;  /* Position X */
  int y;  /* Position Y */

  int value;
  int finished;

  /* Neighbor */
  Island* up_neighbor;
  Island* down_neighbor;
  Island* left_neighbor;
  Island* right_neighbor;

  /* Linked island */
  Island* linked_up_island;
  Island* linked_down_island;
  Island* linked_left_island;
  Island* linked_right_island;

  /* Number of bridges */
  int nb_bridge_up;
  int nb_bridge_down;
  int nb_bridge_left;
  int nb_bridge_right;
};

/* Initialize every field of the the Island_list structure to NULL or 0 so it's ready
 * to be used. */
void initialize(Island_list* island_list) {
  for (int i = 0; i < nb_island; i++) {
    island_list->islands[i].up_neighbor = NULL;
    island_list->islands[i].down_neighbor = NULL;
    island_list->islands[i].left_neighbor = NULL;
    island_list->islands[i].right_neighbor = NULL;

    island_list->islands[i].linked_up_island = NULL;
    island_list->islands[i].linked_down_island = NULL;
    island_list->islands[i].linked_left_island = NULL;
    island_list->islands[i].linked_right_island = NULL;

    island_list->islands[i].nb_bridge_up = 0;
    island_list->islands[i].nb_bridge_down = 0;
    island_list->islands[i].nb_bridge_left = 0;
    island_list->islands[i].nb_bridge_right = 0;

    island_list->islands[i].finished = 0;
  }
}

/* Checks the absolute distance between two integers. */
int distance(int a, int b) {
  if (a < b)
    return b - a;
  return a - b;
}

/* Checks if the game is solved. Returns 1 if it's the case, 0 if not. */
int is_game_over(Island_list* island_list) {
  int cpt_bridges = 0;
  int cpt_values = 0;
  for (int i = 0; i < nb_island; i++) {
    cpt_values += island_list->islands[i].value;
    cpt_bridges +=
        island_list->islands[i].nb_bridge_down + island_list->islands[i].nb_bridge_up +
        island_list->islands[i].nb_bridge_left + island_list->islands[i].nb_bridge_right;
  }
  if (cpt_values == cpt_bridges)
    return 1;
  return 0;
}

/* Concatenate two integers. Used to encode 2 pairs of coordonates inside the
 * bridges array. */
int concatenate(int x, int y) {
  int pow = 10;
  while (y >= pow)
    pow *= 10;
  return x * pow + y;
}

/* Locks the way where a bridge is drawn. It simply copies the concatenation of
 * the coordonates inside the array bridge. */
void lock(Island* islands, Island* islandt, int dir, int bridges[]) {
  int xs = islands->x;
  int ys = islands->y;
  int xt = islandt->x;
  int yt = islandt->y;
  if (dir == 0) {
    for (ys -= 1; ys > yt; ys--) {
      bridges[pos] = concatenate(xs, ys);
      pos++;
    }
  }
  if (dir == 1) {
    for (ys += 1; ys < yt; ys++) {
      bridges[pos] = concatenate(xs, ys);
      pos++;
    }
  }
  if (dir == 2) {
    for (xs -= 1; xs > xt; xs--) {
      bridges[pos] = concatenate(xs, ys);
      pos++;
    }
  }
  if (dir == 3) {
    for (xs += 1; xs < xt; xs++) {
      bridges[pos] = concatenate(xs, ys);
      pos++;
    }
  }
}

/* Checks if a way is locked, and delete the neighbor if it's the case. */
int is_locked(Island* islands, Island* islandt, int dir, int bridges[]) {
  int xs = islands->x;
  int ys = islands->y;
  int xt = islandt->x;
  int yt = islandt->y;
  if (dir == 0) {
    for (ys -= 1; ys > yt; ys--) {
      for (int i = 0; i <= pos; i++) {
        if (bridges[i] == concatenate(xs, ys)) {
          if (islands->linked_up_island != NULL) {
            break;
          }
          islands->up_neighbor = NULL;
          islandt->down_neighbor = NULL;
          return 1;
        }
      }
    }
  }
  if (dir == 1) {
    for (ys += 1; ys < yt; ys++) {
      for (int i = 0; i <= pos; i++) {
        if (bridges[i] == concatenate(xs, ys)) {
          if (islands->linked_down_island != NULL) {
            break;
          }
          islands->down_neighbor = NULL;
          islandt->up_neighbor = NULL;
          return 1;
        }
      }
    }
  }
  if (dir == 2) {
    for (xs -= 1; xs > xt; xs--) {
      for (int i = 0; i <= pos; i++) {
        if (bridges[i] == concatenate(xs, ys)) {
          if (islands->linked_left_island != NULL) {
            break;
          }
          islands->left_neighbor = NULL;
          islandt->right_neighbor = NULL;
          return 1;
        }
      }
    }
  }
  if (dir == 3) {
    for (xs += 1; xs < xt; xs++) {
      for (int i = 0; i <= pos; i++) {
        if (bridges[i] == concatenate(xs, ys)) {
          if (islands->linked_right_island != NULL) {
            break;
          }
          islands->right_neighbor = NULL;
          islandt->left_neighbor = NULL;
          return 1;
        }
      }
    }
  }
  return 0;
}

/* Checks the file and returns the number of islands */
int get_nb_island(FILE* _file) {
  int nb_island = 0;
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

/* Checks the island and returns the number of neighbors */
int get_nb_neighbor(Island island) {
  int cpt = 0;
  if (island.up_neighbor != NULL)
    cpt++;
  if (island.down_neighbor != NULL)
    cpt++;
  if (island.left_neighbor != NULL)
    cpt++;
  if (island.right_neighbor != NULL)
    cpt++;
  return cpt;
}

/* Checks the island and returns the number of neighbors finished */
int get_nb_neighbor_finished(Island island) {
  int cpt = 0;
  if ((island.up_neighbor != NULL) && (island.up_neighbor->finished == 1))
    cpt++;
  if ((island.down_neighbor != NULL) && (island.down_neighbor->finished == 1))
    cpt++;
  if ((island.left_neighbor != NULL) && (island.left_neighbor->finished == 1))
    cpt++;
  if ((island.right_neighbor != NULL) && (island.right_neighbor->finished == 1))
    cpt++;
  return cpt;
}

/* Checks the island and returns the number of bridges */
int get_nb_bridge(Island island) {
  int cpt = 0;
  if (island.nb_bridge_up > 0)
    cpt += island.nb_bridge_up;
  if (island.nb_bridge_down > 0)
    cpt += island.nb_bridge_down;
  if (island.nb_bridge_left > 0)
    cpt += island.nb_bridge_left;
  if (island.nb_bridge_right > 0)
    cpt += island.nb_bridge_right;
  return cpt;
}

/* Checks the file and fills the Island_list with the different islands
 *    and their informations */
void fill_Island_list(FILE* _file, Island_list* island_list) {
  char char_read;
  int i = 0;
  int j = 0;
  int a = 0;
  char_read = fgetc(_file);
  while (char_read != EOF) {
    if (char_read == '_') { /* Replaces _ by 0 in Island_list. */
      j++;
    } else if (char_read == '\n') {
      i++;
      j = 0;
    } else if ((char_read - INT_TO_CHAR < 9) && (char_read - INT_TO_CHAR > 0)) {
      island_list->islands[a].x = j;
      island_list->islands[a].y = i;
      island_list->islands[a].value = char_read - INT_TO_CHAR;
      j++;
      a++;
    } else
      j++;
    char_read = fgetc(_file);
  }
}

/* Checks the Island_list and find the neighbors of each island
 * and store the information in the islands */
void fill_Island_list_neighbor(Island_list* island_list, int size_island_list) {
  int position_neighbor = -1;
  for (int i = 0; i < nb_island; i++) {
    if ((island_list->islands[i].x != 0) && (island_list->islands[i].left_neighbor == NULL)) {
      for (int j = 0; j < nb_island && j != i; j++) {
        if ((island_list->islands[j].y == island_list->islands[i].y) &&
            (island_list->islands[j].x < island_list->islands[i].x)) {
          if (position_neighbor == -1)
            position_neighbor = j;
          else {
            if ((distance(island_list->islands[position_neighbor].x,
                          island_list->islands[i].x)) >
                (distance(island_list->islands[j].x, island_list->islands[i].x)))
              position_neighbor = j;
          }
        }
      }
      if (position_neighbor > -1) {
        island_list->islands[i].left_neighbor = &(island_list->islands[position_neighbor]);
        island_list->islands[position_neighbor].right_neighbor = &(island_list->islands[i]);
      }
      position_neighbor = -1;
    }
    if ((island_list->islands[i].x != size_island_list) &&
        (island_list->islands[i].right_neighbor == NULL)) {
      for (int j = 0; j < nb_island && j != i; j++) {
        if ((island_list->islands[j].y == island_list->islands[i].y) &&
            (island_list->islands[j].x > island_list->islands[i].x)) {
          if (position_neighbor == -1)
            position_neighbor = j;
          else {
            if ((distance(island_list->islands[position_neighbor].x,
                          island_list->islands[i].x)) >
                (distance(island_list->islands[j].x, island_list->islands[i].x)))
              position_neighbor = j;
          }
        }
      }
      if (position_neighbor > -1) {
        island_list->islands[i].right_neighbor = &(island_list->islands[position_neighbor]);
        island_list->islands[position_neighbor].left_neighbor = &(island_list->islands[i]);
      }
      position_neighbor = -1;
    }
    if ((island_list->islands[i].y != 0) && (island_list->islands[i].up_neighbor == NULL)) {
      for (int j = 0; j < nb_island && j != i; j++) {
        if ((island_list->islands[j].x == island_list->islands[i].x) &&
            (island_list->islands[j].y < island_list->islands[i].y)) {
          if (position_neighbor == -1)
            position_neighbor = j;
          else {
            if ((distance(island_list->islands[position_neighbor].y,
                          island_list->islands[i].y)) >
                (distance(island_list->islands[j].y, island_list->islands[i].y)))
              position_neighbor = j;
          }
        }
      }
      if (position_neighbor > -1) {
        island_list->islands[i].up_neighbor = &(island_list->islands[position_neighbor]);
        island_list->islands[position_neighbor].down_neighbor = &(island_list->islands[i]);
      }
      position_neighbor = -1;
    }
    if ((island_list->islands[i].y != size_island_list) &&
        (island_list->islands[i].down_neighbor == NULL)) {
      for (int j = 0; j < nb_island && j != i; j++) {
        if ((island_list->islands[j].x == island_list->islands[i].x) &&
            (island_list->islands[j].y > island_list->islands[i].y)) {
          if (position_neighbor == -1)
            position_neighbor = j;
          else {
            if ((distance(island_list->islands[position_neighbor].y,
                          island_list->islands[i].y)) >
                (distance(island_list->islands[j].y, island_list->islands[i].y)))
              position_neighbor = j;
          }
        }
      }
      if (position_neighbor > -1) {
        island_list->islands[i].down_neighbor = &(island_list->islands[position_neighbor]);
        island_list->islands[position_neighbor].up_neighbor = &(island_list->islands[i]);
      }
      position_neighbor = -1;
    }
  }
}



/* Solving algorithms */

/* Checks the Island_list and returns the number of islands finished */
int get_nb_island_finished(Island_list* island_list) {
  int cpt = 0;
  for (int i = 0; i < nb_island; i++) {
    if (island_list->islands[i].finished == 1)
      cpt++;
  }
  return cpt;
}

/* Checks the island and put it to the finished state if the island has
 * the right amount of bridges. */
void validate_island(Island* island) {
  if (get_nb_bridge(*island) == island->value)
    island->finished = 1;
}

/* Checks the island and if it only has one neighbor then it puts one or two
 * bridges (according to the value of the island) between the island
 and the neighbor. */
void heuristic_n1(Island* island, int bridges[]) {
  if (get_nb_neighbor(*island) == 1 && island->finished == 0) {
    if (island->up_neighbor != NULL &&
        is_locked(island, island->up_neighbor, UP, bridges) == 0) {
      island->linked_up_island = island->up_neighbor;
      island->nb_bridge_up = island->value;
      island->linked_up_island->linked_down_island = island;
      island->linked_up_island->nb_bridge_down = island->value;
      lock(island, island->up_neighbor, UP, bridges);
      validate_island(island->linked_up_island);
    }
    if (island->left_neighbor != NULL &&
        is_locked(island, island->left_neighbor, LEFT, bridges) == 0) {
      island->linked_left_island = island->left_neighbor;
      island->nb_bridge_left = island->value;
      island->linked_left_island->linked_right_island = island;
      island->linked_left_island->nb_bridge_right = island->value;
      lock(island, island->left_neighbor, LEFT, bridges);
      validate_island(island->linked_left_island);
    }
    if (island->down_neighbor != NULL &&
        is_locked(island, island->down_neighbor, DOWN, bridges) == 0) {
      island->linked_down_island = island->down_neighbor;
      island->nb_bridge_down = island->value;
      island->linked_down_island->linked_up_island = island;
      island->linked_down_island->nb_bridge_up = island->value;
      lock(island, island->down_neighbor, DOWN, bridges);
      validate_island(island->linked_down_island);
    }
    if (island->right_neighbor != NULL &&
        is_locked(island, island->right_neighbor, RIGHT, bridges) == 0) {
      island->linked_right_island = island->right_neighbor;
      island->nb_bridge_right = island->value;
      island->linked_right_island->linked_left_island = island;
      island->linked_right_island->nb_bridge_left = island->value;
      lock(island, island->right_neighbor, RIGHT, bridges);
      validate_island(island->linked_right_island);
    }
    island->finished = 1;
  }
}

/* Checks the island and if it is even and has the value divided by 2 number
 of neighbor then we put two bridges between the island and each of
 its neighbor */
void heuristic_n2(Island* island, int bridges[]) {
  if (get_nb_neighbor(*island) == island->value / 2 && island->finished == 0) {
    if (island->up_neighbor != NULL &&
        is_locked(island, island->up_neighbor, UP, bridges) == 0) {
      island->linked_up_island = island->up_neighbor;
      island->nb_bridge_up = 2;
      island->linked_up_island->linked_down_island = island;
      island->linked_up_island->nb_bridge_down = 2;
      lock(island, island->up_neighbor, UP, bridges);
      validate_island(island->linked_up_island);
    }
    if (island->left_neighbor != NULL &&
        is_locked(island, island->left_neighbor, LEFT, bridges) == 0) {
      island->linked_left_island = island->left_neighbor;
      island->nb_bridge_left = 2;
      island->linked_left_island->linked_right_island = island;
      island->linked_left_island->nb_bridge_right = 2;
      lock(island, island->left_neighbor, LEFT, bridges);
      validate_island(island->linked_left_island);
    }
    if (island->down_neighbor != NULL &&
        is_locked(island, island->down_neighbor, DOWN, bridges) == 0) {
      island->linked_down_island = island->down_neighbor;
      island->nb_bridge_down = 2;
      island->linked_down_island->linked_up_island = island;
      island->linked_down_island->nb_bridge_up = 2;
      lock(island, island->down_neighbor, DOWN, bridges);
      validate_island(island->linked_down_island);
    }
    if (island->right_neighbor != NULL &&
        is_locked(island, island->right_neighbor, RIGHT, bridges) == 0) {
      island->linked_right_island = island->right_neighbor;
      island->nb_bridge_right = 2;
      island->linked_right_island->linked_left_island = island;
      island->linked_right_island->nb_bridge_left = 2;
      lock(island, island->right_neighbor, RIGHT, bridges);
      validate_island(island->linked_right_island);
    }
    island->finished = 1;
  }
}

/* Checks the island and if it is odd and has the value + 1 divided by 2 number
 of neighbor then we put one bridge between the island and each of
 its neighbor */
void heuristic_n3(Island* island, int bridges[]) {
  if (island->up_neighbor != NULL)
    is_locked(island, island->up_neighbor, UP, bridges);
  if (island->down_neighbor != NULL)
    is_locked(island, island->down_neighbor, DOWN, bridges);
  if (island->left_neighbor != NULL)
    is_locked(island, island->left_neighbor, LEFT, bridges);
  if (island->right_neighbor != NULL)
    is_locked(island, island->right_neighbor, RIGHT, bridges);
  if (((island->value + 1) % 2 == 0) &&
      (get_nb_neighbor(*island) == (island->value + 1) / 2) &&
      (island->finished == 0)) {
    if ((island->up_neighbor != NULL) &&
        (is_locked(island, island->up_neighbor, UP, bridges) == 0) &&
        (island->nb_bridge_up < 1)) {
      island->linked_up_island = island->up_neighbor;
      island->nb_bridge_up = 1;
      island->linked_up_island->linked_down_island = island;
      island->linked_up_island->nb_bridge_down = 1;
      lock(island, island->up_neighbor, UP, bridges);
      validate_island(island->linked_up_island);
    }
    if ((island->left_neighbor != NULL) &&
        (is_locked(island, island->left_neighbor, LEFT, bridges) == 0) &&
        (island->nb_bridge_left < 1)) {
      island->linked_left_island = island->left_neighbor;
      island->nb_bridge_left = 1;
      island->linked_left_island->linked_right_island = island;
      island->linked_left_island->nb_bridge_right = 1;
      lock(island, island->left_neighbor, LEFT, bridges);
      validate_island(island->linked_left_island);
    }
    if ((island->down_neighbor != NULL) &&
        (is_locked(island, island->down_neighbor, DOWN, bridges) == 0) &&
        (island->nb_bridge_down < 1)) {
      island->linked_down_island = island->down_neighbor;
      island->nb_bridge_down = 1;
      island->linked_down_island->linked_up_island = island;
      island->linked_down_island->nb_bridge_up = 1;
      lock(island, island->down_neighbor, DOWN, bridges);
      validate_island(island->linked_down_island);
    }
    if ((island->right_neighbor != NULL) &&
        (is_locked(island, island->right_neighbor, RIGHT, bridges) == 0) &&
        (island->nb_bridge_right < 1)) {
      island->linked_right_island = island->right_neighbor;
      island->nb_bridge_right = 1;
      island->linked_right_island->linked_left_island = island;
      island->linked_right_island->nb_bridge_left = 1;
      lock(island, island->right_neighbor, RIGHT, bridges);
      validate_island(island->linked_right_island);
    }
    validate_island(island);
  }
}

/* Checks the island and if it only has one neighbor who is not finished then
we add one or two bridges (depending on the number of bridges already done)
between the island and its neighbor */
void heuristic_neighbor_finished(Island* island, int bridges[]) {
  if (island->up_neighbor != NULL)
    is_locked(island, island->up_neighbor, UP, bridges);
  if (island->down_neighbor != NULL)
    is_locked(island, island->down_neighbor, DOWN, bridges);
  if (island->left_neighbor != NULL)
    is_locked(island, island->left_neighbor, LEFT, bridges);
  if (island->right_neighbor != NULL)
    is_locked(island, island->right_neighbor, RIGHT, bridges);

  if ((get_nb_neighbor(*island) - get_nb_neighbor_finished(*island)) == 1 &&
      island->finished == 0) {
    if ((island->up_neighbor != NULL) &&
        (is_locked(island, island->up_neighbor, UP, bridges) == 0) &&
        (island->up_neighbor->finished == 0)) {
      island->linked_up_island = island->up_neighbor;
      island->nb_bridge_up += island->value - get_nb_bridge(*island);
      island->linked_up_island->linked_down_island = island;
      island->linked_up_island->nb_bridge_down = island->nb_bridge_up;
      lock(island, island->up_neighbor, UP, bridges);
      validate_island(island->linked_up_island);
    }
    if ((island->left_neighbor != NULL) &&
        (is_locked(island, island->left_neighbor, LEFT, bridges) == 0) &&
        (island->left_neighbor->finished == 0)) {
      island->linked_left_island = island->left_neighbor;
      island->nb_bridge_left += island->value - get_nb_bridge(*island);
      island->linked_left_island->linked_right_island = island;
      island->linked_left_island->nb_bridge_right = island->nb_bridge_left;
      lock(island, island->left_neighbor, LEFT, bridges);
      validate_island(island->linked_left_island);
    }
    if ((island->down_neighbor != NULL) &&
        (is_locked(island, island->down_neighbor, DOWN, bridges) == 0) &&
        (island->down_neighbor->finished == 0)) {
      island->linked_down_island = island->down_neighbor;
      island->nb_bridge_down += island->value - get_nb_bridge(*island);
      island->linked_down_island->linked_up_island = island;
      island->linked_down_island->nb_bridge_up = island->nb_bridge_down;
      lock(island, island->down_neighbor, DOWN, bridges);
      validate_island(island->linked_down_island);
    }
    if ((island->right_neighbor != NULL) &&
        (is_locked(island, island->right_neighbor, RIGHT, bridges) == 0) &&
        (island->right_neighbor->finished == 0)) {
      island->linked_right_island = island->right_neighbor;
      island->nb_bridge_right += island->value - get_nb_bridge(*island);
      island->linked_right_island->linked_left_island = island;
      island->linked_right_island->nb_bridge_left = island->nb_bridge_right;
      lock(island, island->right_neighbor, RIGHT, bridges);
      validate_island(island->linked_right_island);
    }
    island->finished = 1;
  }
}

/* Not used and not fonctionnal */
void heuristic_k(Island* island) {
  int tmp_max;
  int max_bridge = 0;
  int max_bridge_up = 0;
  int max_bridge_left = 0;
  int max_bridge_down = 0;
  int max_bridge_right = 0;

  if (island->finished == 0) {
    if (island->up_neighbor != NULL && island->up_neighbor->finished == 0) {
      tmp_max =
          island->up_neighbor->value - get_nb_bridge(*(island->up_neighbor));
      if (tmp_max > 1)
        max_bridge_up = 2;
      else if (tmp_max > 0)
        max_bridge_up = 1;
      max_bridge += max_bridge_up;
    }
    if (island->left_neighbor != NULL && island->left_neighbor->finished == 0) {
      tmp_max = island->left_neighbor->value -
                get_nb_bridge(*(island->left_neighbor));
      if (tmp_max > 1)
        max_bridge_left = 2;
      else if (tmp_max > 0)
        max_bridge_left = 1;
      max_bridge += max_bridge_left;
    }
    if (island->down_neighbor != NULL && island->down_neighbor->finished == 0) {
      tmp_max = island->down_neighbor->value -
                get_nb_bridge(*(island->down_neighbor));
      if (tmp_max > 1)
        max_bridge_down = 2;
      else if (tmp_max > 0)
        max_bridge_down = 1;
      max_bridge += max_bridge_down;
    }
    if (island->right_neighbor != NULL &&
        island->right_neighbor->finished == 0) {
      tmp_max = island->right_neighbor->value -
                get_nb_bridge(*(island->right_neighbor));
      if (tmp_max > 1)
        max_bridge_right = 2;
      else if (tmp_max > 0)
        max_bridge_right = 1;
      max_bridge += max_bridge_right;
    }
    printf("max bridge %d\n", max_bridge);
    if (island->value == max_bridge) {
      if (max_bridge_up > 0) {
        island->linked_up_island = island->up_neighbor;
        island->nb_bridge_up = max_bridge_up;
        island->linked_up_island->linked_down_island = island;
        island->linked_up_island->nb_bridge_down = max_bridge_up;
        validate_island(island->linked_up_island);
      }
      if (max_bridge_left > 0) {
        island->linked_left_island = island->left_neighbor;
        island->nb_bridge_left = max_bridge_left;
        island->linked_left_island->linked_right_island = island;
        island->linked_left_island->nb_bridge_right = max_bridge_left;
        validate_island(island->linked_left_island);
      }
      if (max_bridge_down > 0) {
        island->linked_down_island = island->down_neighbor;
        island->nb_bridge_down = max_bridge_down;
        island->linked_down_island->linked_up_island = island;
        island->linked_down_island->nb_bridge_up = max_bridge_down;
        validate_island(island->linked_down_island);
      }
      if (max_bridge_right > 0) {
        island->linked_right_island = island->right_neighbor;
        island->nb_bridge_right = max_bridge_right;
        island->linked_right_island->linked_left_island = island;
        island->linked_right_island->nb_bridge_left = max_bridge_right;
        validate_island(island->linked_right_island);
      }
      island->finished = 1;
    }
  }
}

void simple_solver(Island_list* island_list, int bridges[]) {
  // while (is_game_over(island_list)!=1){
  for (int i = 0; i < nb_island; i++) {
    heuristic_n1(&(island_list->islands[i]), bridges);
    heuristic_n2(&(island_list->islands[i]), bridges);
    heuristic_n3(&(island_list->islands[i]), bridges);
  }
  for (int j = 0; j < 10; j++) {
    for (int i = 0; i < nb_island; i++) {
      heuristic_neighbor_finished(&(island_list->islands[i]), bridges);
    }
  }

  //}
}

/* Print the instructions to solve the game. */
void print_Island_list(Island_list* island_list) {
  for (int i = 0; i < nb_island; i++) {
    printf(
        "Island[%d], position %d %d: left bridges: %d, right bridges: %d, up "
        "bridges %d, down bridges: %d\n",
        i, island_list->islands[i].x, island_list->islands[i].y,
        island_list->islands[i].nb_bridge_left, island_list->islands[i].nb_bridge_right,
        island_list->islands[i].nb_bridge_up, island_list->islands[i].nb_bridge_down);
  }

  printf("Total number of islands : %d\nNumber of finished islands : %d\n",
         nb_island, get_nb_island_finished(island_list));
  if (is_game_over(island_list) == 1) {
    printf("Solved.\n");
  } else {
    printf("Unsolved.\n");
  }
}

/* Not useful anymore */
/* Used to print the Island_list in a file (when the Island_list was not a structure) */
void print_Island_list_in_file(int** island_list) {
  FILE* outputFile = NULL;

  outputFile =
      fopen("../hashiOutput.txt", "w"); /* Creates a file to write in. */
  for (int i = 0; i < 6; i++) {
    if (i > 0)
      fputc('\n', outputFile);
    for (int j = 0; j < 6; j++) {
      if (island_list[i][j] + INT_TO_CHAR == '0')
        fputc('_', outputFile);
      else
        fputc(island_list[i][j] + INT_TO_CHAR, outputFile);
    }
  }
  fclose(outputFile);
}

/* Main */

int main(int argc, char** argv) {
  int bridges[1024];
  int size_island_list = 6;

  /* Opens the file and check if it succeeded. */
  FILE* inputFile;
  inputFile = fopen(argv[1], "r");
  if (inputFile == NULL) { /* Check if the file exists. */
    fprintf(stderr, "Error reading file.\n");
    exit(EXIT_FAILURE);
  }
  nb_island = get_nb_island(inputFile);
  rewind(inputFile);
  /* Allocation */
  Island_list* island_list = malloc(sizeof(Island_list));
  if (island_list == NULL) {
    fprintf(stderr, "Allocation error.");
    exit(EXIT_FAILURE);
  }
  island_list->islands = malloc(sizeof(Island*) * sizeof(Island) * nb_island);
  if (island_list->islands == NULL) {
    fprintf(stderr, "Allocation error.");
    exit(EXIT_FAILURE);
  }
  /* Initialize the Island_list and fills it with informations of the islands */
  initialize(island_list);
  fill_Island_list(inputFile, island_list);
  fill_Island_list_neighbor(island_list, size_island_list);
  fclose(inputFile);

  /* Uses a simple solver to try to solve the Island_list */
  simple_solver(island_list, bridges);

  /* Prints the result */
  print_Island_list(island_list);

  free(island_list);
  free(island_list->islands);
  return (0);
}

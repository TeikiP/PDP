#include "processing.h"

void validate_island(Island* island) {
  if (get_nb_bridge(*island) == get_value(island->information_island))
    set_finished(&(island->information_island), 1);
}

void heuristic_n1(Island* island, Grid* grid) {
  if (get_nb_neighbor(*island) == 1 &&
      get_finished(island->information_island) == 0) {
    if (island->up_neighbor != NULL &&
        is_locked(island, island->up_neighbor, UP, grid) == 0) {
      island->linked_up_island = island->up_neighbor;
      set_nb_bridge_up(&(island->information_island),
                       get_value(island->information_island));
      island->linked_up_island->linked_down_island = island;
      set_nb_bridge_down(&(island->linked_up_island->information_island),
                         get_value(island->information_island));
      lock(island, island->up_neighbor, UP, grid);
      validate_island(island->linked_up_island);
    }
    if (island->left_neighbor != NULL &&
        is_locked(island, island->left_neighbor, LEFT, grid) == 0) {
      island->linked_left_island = island->left_neighbor;
      set_nb_bridge_left(&(island->information_island),
                         get_value(island->information_island));
      island->linked_left_island->linked_right_island = island;
      set_nb_bridge_right(&(island->linked_left_island->information_island),
                          get_value(island->information_island));
      lock(island, island->left_neighbor, LEFT, grid);
      validate_island(island->linked_left_island);
    }
    if (island->down_neighbor != NULL &&
        is_locked(island, island->down_neighbor, DOWN, grid) == 0) {
      island->linked_down_island = island->down_neighbor;
      set_nb_bridge_down(&(island->information_island),
                         get_value(island->information_island));
      island->linked_down_island->linked_up_island = island;
      set_nb_bridge_up(&(island->linked_down_island->information_island),
                       get_value(island->information_island));
      lock(island, island->down_neighbor, DOWN, grid);
      validate_island(island->linked_down_island);
    }
    if (island->right_neighbor != NULL &&
        is_locked(island, island->right_neighbor, RIGHT, grid) == 0) {
      island->linked_right_island = island->right_neighbor;
      set_nb_bridge_right(&(island->information_island),
                          get_value(island->information_island));
      island->linked_right_island->linked_left_island = island;
      set_nb_bridge_left(&(island->linked_right_island->information_island),
                         get_value(island->information_island));
      lock(island, island->right_neighbor, RIGHT, grid);
      validate_island(island->linked_right_island);
    }
    set_finished(&(island->information_island), 1);
  }
}

void heuristic_n2(Island* island, Grid* grid) {
  if (get_nb_neighbor(*island) == get_value(island->information_island) / 2 &&
      get_finished(island->information_island) == 0) {
    if (island->up_neighbor != NULL &&
        is_locked(island, island->up_neighbor, UP, grid) == 0) {
      island->linked_up_island = island->up_neighbor;
      set_nb_bridge_up(&(island->information_island), 2);
      island->linked_up_island->linked_down_island = island;
      set_nb_bridge_down(&(island->linked_up_island->information_island), 2);
      lock(island, island->up_neighbor, UP, grid);
      validate_island(island->linked_up_island);
    }
    if (island->left_neighbor != NULL &&
        is_locked(island, island->left_neighbor, LEFT, grid) == 0) {
      island->linked_left_island = island->left_neighbor;
      set_nb_bridge_left(&(island->information_island), 2);
      island->linked_left_island->linked_right_island = island;
      set_nb_bridge_right(&(island->linked_left_island->information_island), 2);
      lock(island, island->left_neighbor, LEFT, grid);
      validate_island(island->linked_left_island);
    }
    if (island->down_neighbor != NULL &&
        is_locked(island, island->down_neighbor, DOWN, grid) == 0) {
      island->linked_down_island = island->down_neighbor;
      set_nb_bridge_down(&(island->information_island), 2);
      island->linked_down_island->linked_up_island = island;
      set_nb_bridge_up(&(island->linked_down_island->information_island), 2);
      lock(island, island->down_neighbor, DOWN, grid);
      validate_island(island->linked_down_island);
    }
    if (island->right_neighbor != NULL &&
        is_locked(island, island->right_neighbor, RIGHT, grid) == 0) {
      island->linked_right_island = island->right_neighbor;
      set_nb_bridge_right(&(island->information_island), 2);
      island->linked_right_island->linked_left_island = island;
      set_nb_bridge_left(&(island->linked_right_island->information_island), 2);
      lock(island, island->right_neighbor, RIGHT, grid);
      validate_island(island->linked_right_island);
    }
    set_finished(&(island->information_island), 1);
  }
}

void heuristic_n3(Island* island, Grid* grid) {
  if (((get_value(island->information_island) + 1) % 2 == 0) &&
      (get_nb_neighbor(*island) ==
       (get_value(island->information_island) + 1) / 2) &&
      (get_finished(island->information_island) == 0)) {
    if ((island->up_neighbor != NULL) &&
        (is_locked(island, island->up_neighbor, UP, grid) == 0) &&
        (get_nb_bridge_up(island->information_island) < 1)) {
      island->linked_up_island = island->up_neighbor;
      set_nb_bridge_up(&(island->information_island), 1);
      island->linked_up_island->linked_down_island = island;
      set_nb_bridge_down(&(island->linked_up_island->information_island), 1);
      lock(island, island->up_neighbor, UP, grid);
      validate_island(island->linked_up_island);
    }
    if ((island->left_neighbor != NULL) &&
        (is_locked(island, island->left_neighbor, LEFT, grid) == 0) &&
        (get_nb_bridge_left(island->information_island) < 1)) {
      island->linked_left_island = island->left_neighbor;
      set_nb_bridge_left(&(island->information_island), 1);
      island->linked_left_island->linked_right_island = island;
      set_nb_bridge_right(&(island->linked_left_island->information_island), 1);
      lock(island, island->left_neighbor, LEFT, grid);
      validate_island(island->linked_left_island);
    }
    if ((island->down_neighbor != NULL) &&
        (is_locked(island, island->down_neighbor, DOWN, grid) == 0) &&
        (get_nb_bridge_down(island->information_island) < 1)) {
      island->linked_down_island = island->down_neighbor;
      set_nb_bridge_down(&(island->information_island), 1);
      island->linked_down_island->linked_up_island = island;
      set_nb_bridge_up(&(island->linked_down_island->information_island), 1);
      lock(island, island->down_neighbor, DOWN, grid);
      validate_island(island->linked_down_island);
    }
    if ((island->right_neighbor != NULL) &&
        (is_locked(island, island->right_neighbor, RIGHT, grid) == 0) &&
        (get_nb_bridge_right(island->information_island) < 1)) {
      island->linked_right_island = island->right_neighbor;
      set_nb_bridge_right(&(island->information_island), 1);
      island->linked_right_island->linked_left_island = island;
      set_nb_bridge_left(&(island->linked_right_island->information_island), 1);
      lock(island, island->right_neighbor, RIGHT, grid);
      validate_island(island->linked_right_island);
    }
    validate_island(island);
  }
}

void heuristic_neighbor_finished(Island* island, Grid* grid) {
  if (island->up_neighbor != NULL)
    is_locked(island, island->up_neighbor, UP, grid);
  if (island->down_neighbor != NULL)
    is_locked(island, island->down_neighbor, DOWN, grid);
  if (island->left_neighbor != NULL)
    is_locked(island, island->left_neighbor, LEFT, grid);
  if (island->right_neighbor != NULL)
    is_locked(island, island->right_neighbor, RIGHT, grid);

  if ((get_nb_neighbor(*island) - get_nb_neighbor_finished(*island)) == 1 &&
      get_finished(island->information_island) == 0) {
    if ((island->up_neighbor != NULL) &&
        (is_locked(island, island->up_neighbor, UP, grid) == 0) &&
        (get_finished(island->up_neighbor->information_island) == 0) &&
        (get_value(island->information_island) - get_nb_bridge(*island) < 3)) {
      island->linked_up_island = island->up_neighbor;
      set_nb_bridge_up(
          &(island->information_island),
          get_nb_bridge_up(island->information_island) +
              (get_value(island->information_island) - get_nb_bridge(*island)));
      island->linked_up_island->linked_down_island = island;
      set_nb_bridge_down(&(island->linked_up_island->information_island),
                         get_nb_bridge_up(island->information_island));
      lock(island, island->up_neighbor, UP, grid);
      validate_island(island->linked_up_island);
    }
    if ((island->left_neighbor != NULL) &&
        (is_locked(island, island->left_neighbor, LEFT, grid) == 0) &&
        (get_finished(island->left_neighbor->information_island) == 0) &&
        (get_value(island->information_island) - get_nb_bridge(*island) < 3)) {
      island->linked_left_island = island->left_neighbor;
      set_nb_bridge_left(
          &(island->information_island),
          get_nb_bridge_left(island->information_island) +
              (get_value(island->information_island) - get_nb_bridge(*island)));
      island->linked_left_island->linked_right_island = island;
      set_nb_bridge_right(&(island->linked_left_island->information_island),
                          get_nb_bridge_left(island->information_island));
      lock(island, island->left_neighbor, LEFT, grid);
      validate_island(island->linked_left_island);
    }
    if ((island->down_neighbor != NULL) &&
        (is_locked(island, island->down_neighbor, DOWN, grid) == 0) &&
        (get_finished(island->down_neighbor->information_island) == 0) &&
        (get_value(island->information_island) - get_nb_bridge(*island) < 3)) {
      island->linked_down_island = island->down_neighbor;
      set_nb_bridge_down(
          &(island->information_island),
          get_nb_bridge_down(island->information_island) +
              (get_value(island->information_island) - get_nb_bridge(*island)));
      island->linked_down_island->linked_up_island = island;
      set_nb_bridge_up(&(island->linked_down_island->information_island),
                       get_nb_bridge_down(island->information_island));
      lock(island, island->down_neighbor, DOWN, grid);
      validate_island(island->linked_down_island);
    }
    if ((island->right_neighbor != NULL) &&
        (is_locked(island, island->right_neighbor, RIGHT, grid) == 0) &&
        (get_finished(island->right_neighbor->information_island) == 0) &&
        (get_value(island->information_island) - get_nb_bridge(*island) < 3)) {
      island->linked_right_island = island->right_neighbor;
      set_nb_bridge_right(
          &(island->information_island),
          get_nb_bridge_right(island->information_island) +
              (get_value(island->information_island) - get_nb_bridge(*island)));
      island->linked_right_island->linked_left_island = island;
      set_nb_bridge_left(&(island->linked_right_island->information_island),
                         get_nb_bridge_right(island->information_island));
      lock(island, island->right_neighbor, RIGHT, grid);
      validate_island(island->linked_right_island);
    }
    set_finished(&(island->information_island), 1);
    grid->heuristic_used++;
  }
}

Island* choose_and_draw_bridge(Grid* grid, unsigned nb_island) {
  Island* chosen_island = NULL;
  unsigned nb_bridges_to_do = 8;
  unsigned nb_bridges_tmp;
  unsigned nb_neighbor_finished = 0;
  /* We choose the island where we will draw the bridge */
  for (unsigned i = 0; i < nb_island; i++) {
    if ((get_finished(grid->islands[i].information_island) != 1) &&
        (get_up_chosen(grid->islands[i].information_backtracking) +
             get_down_chosen(grid->islands[i].information_backtracking) +
             get_left_chosen(grid->islands[i].information_backtracking) +
             get_right_chosen(grid->islands[i].information_backtracking) <
         get_nb_neighbor(grid->islands[i]) -
             get_nb_neighbor_finished(grid->islands[i])) &&
        (get_stuck_island(grid->islands[i].information_backtracking) != 1)) {
      nb_bridges_tmp = get_value(grid->islands[i].information_island) -
                       get_nb_bridge(grid->islands[i]);
      if (nb_bridges_tmp < nb_bridges_to_do) {
        nb_bridges_to_do = nb_bridges_tmp;
        nb_neighbor_finished = get_nb_neighbor_finished(grid->islands[i]);
        chosen_island = &(grid->islands[i]);
      } else if (nb_bridges_tmp == nb_bridges_to_do) {
        if (get_nb_neighbor_finished(grid->islands[i]) > nb_neighbor_finished) {
          nb_neighbor_finished = get_nb_neighbor_finished(grid->islands[i]);
          chosen_island = &(grid->islands[i]);
        }
      }
    }
  }

  if (chosen_island == NULL)
    return chosen_island;

  if ((chosen_island->up_neighbor != NULL) &&
      (is_locked(chosen_island, chosen_island->up_neighbor, UP, grid) == 0) &&
      (get_finished(chosen_island->up_neighbor->information_island) == 0) &&
      (get_nb_bridge_up(chosen_island->information_island) < 2) &&
      (get_up_chosen(chosen_island->information_backtracking) != 1) &&
      (get_down_chosen(chosen_island->up_neighbor->information_backtracking) !=
       1)) {
    chosen_island->linked_up_island = chosen_island->up_neighbor;
    set_nb_bridge_up(&(chosen_island->information_island),
                     get_nb_bridge_up(chosen_island->information_island) + 1);
    chosen_island->linked_up_island->linked_down_island = chosen_island;
    set_nb_bridge_down(&(chosen_island->linked_up_island->information_island),
                       get_nb_bridge_up(chosen_island->information_island));
    lock(chosen_island, chosen_island->up_neighbor, UP, grid);
    validate_island(chosen_island->linked_up_island);
    validate_island(chosen_island);
    set_up_chosen(&(chosen_island->information_backtracking), 1);
    set_down_chosen(&(chosen_island->up_neighbor->information_backtracking), 1);
  } else if ((chosen_island->down_neighbor != NULL) &&
             (is_locked(chosen_island, chosen_island->down_neighbor, DOWN,
                        grid) == 0) &&
             (get_finished(chosen_island->down_neighbor->information_island) ==
              0) &&
             (get_nb_bridge_down(chosen_island->information_island) < 2) &&
             (get_down_chosen(chosen_island->information_backtracking) != 1) &&
             (get_up_chosen(
                  chosen_island->down_neighbor->information_backtracking) !=
              1)) {
    chosen_island->linked_down_island = chosen_island->down_neighbor;
    set_nb_bridge_down(
        &(chosen_island->information_island),
        get_nb_bridge_down(chosen_island->information_island) + 1);
    chosen_island->linked_down_island->linked_up_island = chosen_island;
    set_nb_bridge_up(&(chosen_island->linked_down_island->information_island),
                     get_nb_bridge_down(chosen_island->information_island));
    lock(chosen_island, chosen_island->down_neighbor, DOWN, grid);
    validate_island(chosen_island->linked_down_island);
    validate_island(chosen_island);
    set_down_chosen(&(chosen_island->information_backtracking), 1);
    set_up_chosen(&(chosen_island->down_neighbor->information_backtracking), 1);
  } else if ((chosen_island->left_neighbor != NULL) &&
             (is_locked(chosen_island, chosen_island->left_neighbor, LEFT,
                        grid) == 0) &&
             (get_finished(chosen_island->left_neighbor->information_island) ==
              0) &&
             (get_nb_bridge_left(chosen_island->information_island) < 2) &&
             (get_left_chosen(chosen_island->information_backtracking) != 1) &&
             (get_right_chosen(
                  chosen_island->left_neighbor->information_backtracking) !=
              1)) {
    chosen_island->linked_left_island = chosen_island->left_neighbor;
    set_nb_bridge_left(
        &(chosen_island->information_island),
        get_nb_bridge_left(chosen_island->information_island) + 1);
    chosen_island->linked_left_island->linked_right_island = chosen_island;
    set_nb_bridge_right(
        &(chosen_island->linked_left_island->information_island),
        get_nb_bridge_left(chosen_island->information_island));
    lock(chosen_island, chosen_island->left_neighbor, LEFT, grid);
    validate_island(chosen_island->linked_left_island);
    validate_island(chosen_island);
    set_left_chosen(&(chosen_island->information_backtracking), 1);
    set_right_chosen(&(chosen_island->left_neighbor->information_backtracking),
                     1);
  } else if ((chosen_island->right_neighbor != NULL) &&
             (is_locked(chosen_island, chosen_island->right_neighbor, RIGHT,
                        grid) == 0) &&
             (get_finished(chosen_island->right_neighbor->information_island) ==
              0) &&
             (get_nb_bridge_right(chosen_island->information_island) < 2) &&
             (get_right_chosen(chosen_island->information_backtracking) != 1) &&
             (get_left_chosen(
                  chosen_island->right_neighbor->information_backtracking) !=
              1)) {
    chosen_island->linked_right_island = chosen_island->right_neighbor;
    set_nb_bridge_right(
        &(chosen_island->information_island),
        get_nb_bridge_right(chosen_island->information_island) + 1);
    chosen_island->linked_right_island->linked_left_island = chosen_island;
    set_nb_bridge_left(
        &(chosen_island->linked_right_island->information_island),
        get_nb_bridge_right(chosen_island->information_island));
    lock(chosen_island, chosen_island->right_neighbor, RIGHT, grid);
    validate_island(chosen_island->linked_right_island);
    validate_island(chosen_island);
    set_right_chosen(&(chosen_island->information_backtracking), 1);
    set_left_chosen(&(chosen_island->right_neighbor->information_backtracking),
                    1);
  } else {
    set_stuck_island(&(chosen_island->information_backtracking), 1);
    return choose_and_draw_bridge(grid, nb_island);
  }

  return chosen_island;
}

unsigned island_exist(unsigned x, unsigned y, Grid* grid, unsigned nb_island) {
  for (unsigned i = 0; i < nb_island + 1; i++) {
    if (get_x(grid->islands[i].position) == x &&
        get_y(grid->islands[i].position) == y)
      return i;
  }
  return nb_island + 1;
}

unsigned is_place_unavailable(Island island,
                              Grid* grid,
                              unsigned size_grid,
                              unsigned nb_island) {
  unsigned x = get_x(island.position);
  unsigned y = get_y(island.position);

  for (unsigned i = 0; i < grid->pos; i++) {
    if (grid->bridges_x[i] == x && grid->bridges_y[i] == y)
      return 1;
  }
  for (unsigned j = 0; j < nb_island + 1; j++) {
    if (x > 0 && get_x(grid->islands[j].position) == x - 1 &&
        get_y(grid->islands[j].position) == y)
      return 1;
    if (x < size_grid - 1 && get_x(grid->islands[j].position) == x + 1 &&
        get_y(grid->islands[j].position) == y)
      return 1;
    if (y > 0 && get_x(grid->islands[j].position) == x &&
        get_y(grid->islands[j].position) == y - 1)
      return 1;
    if (y < size_grid - 1 && get_x(grid->islands[j].position) == x &&
        get_y(grid->islands[j].position) == y + 1)
      return 1;
  }

  return 0;
}

void reset_grid(Grid* grid, unsigned size_grid, unsigned nb_island) {
  for (unsigned i = 0; i < (size_grid * size_grid); i++) {
    grid->bridges_x[i] = 0;
  }
  for (unsigned i = 0; i < (size_grid * size_grid); i++) {
    grid->bridges_y[i] = 0;
  }
  for (unsigned i = 0; i < (size_grid * size_grid); i++) {
    grid->bridges_d[i] = 0;
  }
  grid->pos = 0;
  grid->heuristic_used = 1;
  grid->chosen_island = NULL;

  for (unsigned i = 0; i < nb_island; i++) {
    grid->islands[i] = (Island){0};
  }
}

/* Checks if a way is locked, and delete the neighbor if it's the case. */
unsigned is_island_on_the_way(Island* islands,
                              Island* islandt,
                              unsigned dir,
                              Grid* grid,
                              unsigned nb_island) {
  unsigned xs = get_x(islands->position);
  unsigned ys = get_y(islands->position);
  unsigned xt = get_x(islandt->position);
  unsigned yt = get_y(islandt->position);
  if (dir == 0) {
    for (ys -= 1; ys > yt; ys--) {
      for (unsigned i = 0; i < nb_island + 1; i++) {
        if (get_x(grid->islands[i].position) == xs &&
            get_y(grid->islands[i].position) == ys)
          return 1;
      }
    }
  }
  if (dir == 1) {
    for (ys += 1; ys < yt; ys++) {
      for (unsigned i = 0; i < nb_island + 1; i++) {
        if (get_x(grid->islands[i].position) == xs &&
            get_y(grid->islands[i].position) == ys)
          return 1;
      }
    }
  }
  if (dir == 2) {
    for (xs -= 1; xs > xt; xs--) {
      for (unsigned i = 0; i < nb_island + 1; i++) {
        if (get_x(grid->islands[i].position) == xs &&
            get_y(grid->islands[i].position) == ys)
          return 1;
      }
    }
  }
  if (dir == 3) {
    for (xs += 1; xs < xt; xs++) {
      for (unsigned i = 0; i < nb_island + 1; i++) {
        if (get_x(grid->islands[i].position) == xs &&
            get_y(grid->islands[i].position) == ys)
          return 1;
      }
    }
  }
  return 0;
}

void lock(Island* islands, Island* islandt, unsigned dir, Grid* grid) {
  unsigned xs = get_x(islands->position);
  unsigned ys = get_y(islands->position);
  unsigned xt = get_x(islandt->position);
  unsigned yt = get_y(islandt->position);
  if (dir == 0) {
    for (ys -= 1; ys > yt; ys--) {
      grid->bridges_x[grid->pos] = xs;
      grid->bridges_y[grid->pos] = ys;
      grid->pos++;
    }
  }
  if (dir == 1) {
    for (ys += 1; ys < yt; ys++) {
      grid->bridges_x[grid->pos] = xs;
      grid->bridges_y[grid->pos] = ys;
      grid->pos++;
    }
  }
  if (dir == 2) {
    for (xs -= 1; xs > xt; xs--) {
      grid->bridges_x[grid->pos] = xs;
      grid->bridges_y[grid->pos] = ys;
      grid->pos++;
    }
  }
  if (dir == 3) {
    for (xs += 1; xs < xt; xs++) {
      grid->bridges_x[grid->pos] = xs;
      grid->bridges_y[grid->pos] = ys;
      grid->pos++;
    }
  }
}

void bridge_doubler(Grid* grid, unsigned nb_island) {
  for (unsigned i = 0; i < nb_island; ++i) {
    if (get_nb_bridge_up(grid->islands[i].information_island) == 2) {
      unsigned xs = get_x(grid->islands[i].position);
      unsigned ys = get_y(grid->islands[i].position);
      unsigned yt = get_y(grid->islands[i].linked_up_island->position);
      for (ys -= 1; ys > yt; ys--) {
        for (unsigned j = 0; j < grid->pos; ++j) {
          if (grid->bridges_x[j] == xs && grid->bridges_y[j] == ys)
            grid->bridges_d[j] = 1;
        }
      }
    }
    if (get_nb_bridge_down(grid->islands[i].information_island) == 2) {
      unsigned xs = get_x(grid->islands[i].position);
      unsigned ys = get_y(grid->islands[i].position);
      unsigned yt = get_y(grid->islands[i].linked_down_island->position);
      for (ys += 1; ys < yt; ys++) {
        for (unsigned j = 0; j < grid->pos; ++j) {
          if (grid->bridges_x[j] == xs && grid->bridges_y[j] == ys)
            grid->bridges_d[j] = 1;
        }
      }
    }
    if (get_nb_bridge_left(grid->islands[i].information_island) == 2) {
      unsigned xs = get_x(grid->islands[i].position);
      unsigned ys = get_y(grid->islands[i].position);
      unsigned xt = get_x(grid->islands[i].linked_left_island->position);
      for (xs -= 1; xs > xt; xs--) {
        for (unsigned j = 0; j < grid->pos; ++j) {
          if (grid->bridges_x[j] == xs && grid->bridges_y[j] == ys)
            grid->bridges_d[j] = 1;
        }
      }
    }
    if (get_nb_bridge_right(grid->islands[i].information_island) == 2) {
      unsigned xs = get_x(grid->islands[i].position);
      unsigned ys = get_y(grid->islands[i].position);
      unsigned xt = get_x(grid->islands[i].linked_right_island->position);
      for (xs += 1; xs < xt; xs++) {
        for (unsigned j = 0; j < grid->pos; ++j) {
          if (grid->bridges_x[j] == xs && grid->bridges_y[j] == ys)
            grid->bridges_d[j] = 1;
        }
      }
    }
  }
}

unsigned is_locked(Island* islands, Island* islandt, unsigned dir, Grid* grid) {
  unsigned xs = get_x(islands->position);
  unsigned ys = get_y(islands->position);
  unsigned xt = get_x(islandt->position);
  unsigned yt = get_y(islandt->position);
  if (dir == 0) {
    for (ys -= 1; ys > yt; ys--) {
      for (unsigned i = 0; i <= grid->pos; i++) {
        if (grid->bridges_x[i] == xs && grid->bridges_y[i] == ys) {
          if (islands->linked_up_island != NULL &&
              get_nb_bridge_up(islands->information_island) < 2) {
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
      for (unsigned i = 0; i <= grid->pos; i++) {
        if (grid->bridges_x[i] == xs && grid->bridges_y[i] == ys) {
          if (islands->linked_down_island != NULL &&
              get_nb_bridge_down(islands->information_island) < 2) {
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
      for (unsigned i = 0; i <= grid->pos; i++) {
        if (grid->bridges_x[i] == xs && grid->bridges_y[i] == ys) {
          if (islands->linked_left_island != NULL &&
              get_nb_bridge_left(islands->information_island) < 2) {
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
      for (unsigned i = 0; i <= grid->pos; i++) {
        if (grid->bridges_x[i] == xs && grid->bridges_y[i] == ys) {
          if (islands->linked_right_island != NULL &&
              get_nb_bridge_right(islands->information_island) < 2) {
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

unsigned get_nb_neighbor(Island island) {
  unsigned cpt = 0;
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

unsigned get_nb_neighbor_finished(Island island) {
  unsigned cpt = 0;
  if ((island.up_neighbor != NULL) &&
      (get_finished(island.up_neighbor->information_island) == 1))
    cpt++;
  if ((island.down_neighbor != NULL) &&
      (get_finished(island.down_neighbor->information_island) == 1))
    cpt++;
  if ((island.left_neighbor != NULL) &&
      (get_finished(island.left_neighbor->information_island) == 1))
    cpt++;
  if ((island.right_neighbor != NULL) &&
      (get_finished(island.right_neighbor->information_island) == 1))
    cpt++;
  return cpt;
}

unsigned get_nb_bridge(Island island) {
  return get_nb_bridge_up(island.information_island) +
         get_nb_bridge_down(island.information_island) +
         get_nb_bridge_left(island.information_island) +
         get_nb_bridge_right(island.information_island);
}

unsigned get_nb_bridge_possible_to_draw(Island island) {
  unsigned cpt_bridge = 0;
  if ((island.up_neighbor != NULL) &&
      (get_finished(island.up_neighbor->information_island) != 1) &&
      (get_nb_bridge_up(island.information_island) < 2)) {
    if (get_value(island.up_neighbor->information_island) -
            get_nb_bridge(*(island.up_neighbor)) ==
        1)
      cpt_bridge++;
    else
      cpt_bridge += (2 - get_nb_bridge_up(island.information_island));
  }
  if ((island.down_neighbor != NULL) &&
      (get_finished(island.down_neighbor->information_island) != 1) &&
      (get_nb_bridge_down(island.information_island) < 2)) {
    if (get_value(island.down_neighbor->information_island) -
            get_nb_bridge(*(island.down_neighbor)) ==
        1)
      cpt_bridge++;
    else
      cpt_bridge += (2 - get_nb_bridge_down(island.information_island));
  }
  if ((island.left_neighbor != NULL) &&
      (get_finished(island.left_neighbor->information_island) != 1) &&
      (get_nb_bridge_left(island.information_island) < 2)) {
    if (get_value(island.left_neighbor->information_island) -
            get_nb_bridge(*(island.left_neighbor)) ==
        1)
      cpt_bridge++;
    else
      cpt_bridge += (2 - get_nb_bridge_left(island.information_island));
  }
  if ((island.right_neighbor != NULL) &&
      (get_finished(island.right_neighbor->information_island) != 1) &&
      (get_nb_bridge_right(island.information_island) < 2)) {
    if (get_value(island.right_neighbor->information_island) -
            get_nb_bridge(*(island.right_neighbor)) ==
        1)
      cpt_bridge++;
    else
      cpt_bridge += (2 - get_nb_bridge_right(island.information_island));
  }
  return cpt_bridge;
}

unsigned is_correct(Grid* grid, unsigned nb_island) {
  for (unsigned i = 0; i < nb_island; i++) {
    if ((get_nb_bridge_up(grid->islands[i].information_island) +
             get_nb_bridge_left(grid->islands[i].information_island) +
             get_nb_bridge_down(grid->islands[i].information_island) +
             get_nb_bridge_right(grid->islands[i].information_island) >
         get_value(grid->islands[i].information_island)) ||
        get_nb_bridge_up(grid->islands[i].information_island) > 2 ||
        get_nb_bridge_down(grid->islands[i].information_island) > 2 ||
        get_nb_bridge_left(grid->islands[i].information_island) > 2 ||
        get_nb_bridge_down(grid->islands[i].information_island) > 2 ||
        get_nb_bridge_right(grid->islands[i].information_island) > 2) {
      return 0;
    }
    if ((get_finished(grid->islands[i].information_island) != 1) &&
        (get_value(grid->islands[i].information_island) -
             get_nb_bridge(grid->islands[i]) >
         (get_nb_bridge_possible_to_draw(grid->islands[i])))) {
      return 0;
    }
  }
  return 1;
}

unsigned is_game_over(Grid* grid, unsigned nb_island) {
  unsigned cpt_bridges = 0;
  unsigned cpt_values = 0;
  unsigned cpt_finished = 0;
  for (unsigned i = 0; i < nb_island; i++) {
    cpt_values += get_value(grid->islands[i].information_island);
    cpt_bridges += get_nb_bridge_down(grid->islands[i].information_island) +
                   get_nb_bridge_up(grid->islands[i].information_island) +
                   get_nb_bridge_left(grid->islands[i].information_island) +
                   get_nb_bridge_right(grid->islands[i].information_island);
    cpt_finished += get_finished(grid->islands[i].information_island);
  }

  if (cpt_values == cpt_bridges && cpt_finished == nb_island &&
      is_correct(grid, nb_island) == 1)
    return 1;
  return 0;
}

unsigned get_nb_island_finished(Grid* grid, unsigned nb_island) {
  unsigned cpt = 0;
  for (unsigned i = 0; i < nb_island; i++) {
    if (get_finished(grid->islands[i].information_island) == 1)
      cpt++;
  }
  return cpt;
}

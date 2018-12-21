#ifndef ISLAND_H_INCLUDED
#define ISLAND_H_INCLUDED

/* position of the lowest bit of the following */
#define POS_BIT_VALUE 0
#define POS_BIT_FINISHED 4
#define POS_BIT_NB_BRIDGE_UP 11
#define POS_BIT_NB_BRIDGE_DOWN 9
#define POS_BIT_NB_BRIDGE_LEFT 7
#define POS_BIT_NB_BRIDGE_RIGHT 5
#define POS_BIT_UP_CHOSEN 3
#define POS_BIT_DOWN_CHOSEN 2
#define POS_BIT_LEFT_CHOSEN 1
#define POS_BIT_RIGHT_CHOSEN 0
#define POS_BIT_STUCK_ISLAND 4
#define POS_BIT_X 0
#define POS_BIT_Y 8

/* Value of the bit(s) of the following */
#define BIT_VALUE 0x000F
#define BIT_FINISHED 0x0010
#define BIT_NB_BRIDGE_UP 0x1800
#define BIT_NB_BRIDGE_DOWN 0x0600
#define BIT_NB_BRIDGE_LEFT 0x0180
#define BIT_NB_BRIDGE_RIGHT 0x0060
#define BIT_UP_CHOSEN 0x0008
#define BIT_DOWN_CHOSEN 0x0004
#define BIT_LEFT_CHOSEN 0x0002
#define BIT_RIGHT_CHOSEN 0x0001
#define BIT_STUCK_ISLAND 0x0010
#define BIT_X 0x00FF
#define BIT_Y 0xFF00

/* structure to store the informations of the islands */
typedef struct Island Island;
/* structure to store all the islands */
typedef struct Grid Grid;
/* structure to store all the grids */
typedef struct stack_t* Stack;

struct Island {
  /* register to store the x and y position */
  unsigned position;
  /* register to store the value, the finished status, and the number of bridges
   * on every side */
  unsigned information_island;
  /* register to store the bits chosen on every side and the stuck_island status
   */
  unsigned information_backtracking;

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
};

struct Grid {
  /* Bridges */
  unsigned* bridges_x;
  unsigned* bridges_y;
  unsigned* bridges_d;
  unsigned pos;
  /* List of islands */
  Island* islands;

  /* variable used to know when to stop using heuristics */
  unsigned heuristic_used;
  /* the island chosen by the backtracking */
  Island* chosen_island;
};

struct stack_t {
  /* List of grids */
  Grid* tab;
  /* Number of grids stored + 1. Used to store the next grid */
  unsigned size;
  /* Number of grids that we can store. Can be changed */
  unsigned capacity;
};

/* Returns the value of the island */
unsigned get_value(unsigned info_island);
/* Returns the status finished of the island */
unsigned get_finished(unsigned info_island);
/* Returns the number of bridges above the island */
unsigned get_nb_bridge_up(unsigned info_island);
/* Returns the number of bridges under the island */
unsigned get_nb_bridge_down(unsigned info_island);
/* Returns the number of bridges on the left of the island */
unsigned get_nb_bridge_left(unsigned info_island);
/* Returns the number of bridges on the right of the island */
unsigned get_nb_bridge_right(unsigned info_island);
/* Returns if we already choosed to draw a bridge up of the island with the
* choose_and_draw_bridge(...) function */
unsigned get_up_chosen(unsigned info_backtracking);
/* Returns if we already choosed to draw a bridge down of the island with the
* choose_and_draw_bridge(...) function */
unsigned get_down_chosen(unsigned info_backtracking);
/* Returns if we already choosed to draw a bridge on the left of the island
* with the choose_and_draw_bridge(...) function */
unsigned get_left_chosen(unsigned info_backtracking);
/* Returns if we already choosed to draw a bridge on the right of the island
* with the choose_and_draw_bridge(...) function */
unsigned get_right_chosen(unsigned info_backtracking);
/* Returns if the island stucks all the other ones if we continue the
* backtracking */
unsigned get_stuck_island(unsigned info_backtracking);
/* Returns the x position of the island */
unsigned get_x(unsigned position);
/* Returns the y position of the island */
unsigned get_y(unsigned position);

/* Sets the new value of the island */
void set_value(unsigned* info_island, unsigned value);
/* Sets the new value of the status finished of the island */
void set_finished(unsigned* info_island, unsigned finished);
/* Sets the new value of the number of bridges above the island */
void set_nb_bridge_up(unsigned* info_island, unsigned nb_bridge_up);
/* Sets the new value of the number of bridges under the island */
void set_nb_bridge_down(unsigned* info_island, unsigned nb_bridge_down);
/* Sets the new value of the number of bridges on the left of the island */
void set_nb_bridge_left(unsigned* info_island, unsigned nb_bridge_left);
/* Sets the new value of the number of bridges on the right of the island */
void set_nb_bridge_right(unsigned* info_island, unsigned nb_bridge_right);
/* Sets the new value of the status up_chosen of the island */
void set_up_chosen(unsigned* info_backtracking, unsigned up_chosen);
/* Sets the new value of the status down_chosen of the island */
void set_down_chosen(unsigned* info_backtracking, unsigned down_chosen);
/* Sets the new value of the status left_chosen of the island */
void set_left_chosen(unsigned* info_backtracking, unsigned left_chosen);
/* Sets the new value of the status right_chosen of the island */
void set_right_chosen(unsigned* info_backtracking, unsigned right_chosen);
/* Sets the new value of the status stuck_island of the island */
void set_stuck_island(unsigned* info_backtracking, unsigned stuck_island);
/* Sets the new value of the x position of the island */
void set_x(unsigned* position, unsigned x);
/* Sets the new value of the y position of the island */
void set_y(unsigned* position, unsigned y);

/* Initialize every field of the Grid structure to NULL or 0 so it's ready
 * to be used. */
void initialize(Grid* grid, unsigned size_grid, unsigned nb_island);
/* Create a Stack to be used for backtracking */
Stack create_stack();
/* Copy a game */
void copy_game(Grid src, Grid* dst, unsigned size_grid, unsigned nb_island);
/* Copy a game but not the backtracking register */
void copy_game_but_not_backtracking(Grid src,
                                    Grid* dst,
                                    unsigned size_grid,
                                    unsigned nb_island);
/* Insert the grid in parameter into the stack */
void insert_value(Stack s, Grid g, unsigned size_grid, unsigned nb_island);
/* Deletes the grid from the stack and free the memory used */
void delete_game(Stack, Grid* grid);
/* Deletes all the grids from the stack and free all the memory used */
void delete_stack(Stack s);

#endif  // ISLAND_H_INCLUDED

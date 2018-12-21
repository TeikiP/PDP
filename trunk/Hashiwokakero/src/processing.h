#include "island.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define INT_TO_CHAR 48 /* constant to translate an unsigned into a char*/

/* Checks the island and put it to the finished state if the island has
 * the right amount of bridges. */
void validate_island(Island* island);
/* Checks the island and if it only has one neighbor then it puts one or two
 * bridges (according to the value of the island) between the island
 and the neighbor. */
void heuristic_n1(Island* island, Grid* grid);
/* Checks the island and if it is even and has the value divided by 2 number
 of neighbor then we put two bridges between the island and each of
 its neighbor */
void heuristic_n2(Island* island, Grid* grid);
/* Checks the island and if it is odd and has the value + 1 divided by 2 number
 of neighbor then we put one bridge between the island and each of
 its neighbor */
void heuristic_n3(Island* island, Grid* grid);
/* Checks the island and if it only has one neighbor who is not finished then
we add one or two bridges (depending on the number of bridges already done)
between the island and its neighbor */
void heuristic_neighbor_finished(Island* island, Grid* grid);
/* Chooses the island with the least bridges to trace and the most neighbors
* finished and draw a bridge in the first direction available. Returns the
* island chosen */
Island* choose_and_draw_bridge(Grid* grid, unsigned nb_island);
/* Checks if the island already exist in the grid and returns its position in
* the list of islands if it does exist or a special number if it doesn't exist
*/
unsigned island_exist(unsigned x, unsigned y, Grid* grid, unsigned nb_island);
/* Checks if there is no bridges and no islands on the next place in every
* direction where we try to put the island. Returns 0 if the place is
* available and 1 if it is unavailable */
unsigned is_place_unavailable(Island island,
                              Grid* grid,
                              unsigned size_grid,
                              unsigned nb_island);
/* Resets the grid by putting every value back to their initial values */
void reset_grid(Grid* grid, unsigned size_grid, unsigned nb_island);
/* Checks if there is an island on the way of where we try to trace the new
* island. Returns 0 if there is none and 1 otherwise */
unsigned is_island_on_the_way(Island* islands,
                              Island* islandt,
                              unsigned dir,
                              Grid* grid,
                              unsigned nb_island);
/* Locks the way where a bridge is drawn by putting the position in the bridges
 */
void lock(Island* islands, Island* islandt, unsigned dir, Grid* grid);
/* Puts in bridges_d in grid the real type of bridge : simple or double */
void bridge_doubler(Grid* grid, unsigned nb_island);
/* Checks if a way is locked, and delete the neighbor if it's the case. */
unsigned is_locked(Island* islands, Island* islandt, unsigned dir, Grid* grid);
/* Checks the island and returns the number of neighbors */
unsigned get_nb_neighbor(Island island);
/* Checks the island and returns the number of neighbors finished */
unsigned get_nb_neighbor_finished(Island island);
/* Checks the island and returns the number of bridges traced */
unsigned get_nb_bridge(Island island);
/* Checks the island and returns the number of bridges */
unsigned get_nb_bridge_possible_to_draw(Island island);
/* Checks if the rules of the game are respected, i.e. checks if there isn't
 * more than 2 bridges by side, if the number of bridges isn't higher than
 * the island value and if you have enough possibilities to draw your
 * bridges with your neighbors */
unsigned is_correct(Grid* grid, unsigned nb_island);
/* Checks if the game is solved. Returns 1 if it's the case, 0 if not. */
unsigned is_game_over(Grid* grid, unsigned nb_island);
/* Checks the Grid and returns the number of islands finished */
unsigned get_nb_island_finished(Grid* grid, unsigned nb_island);

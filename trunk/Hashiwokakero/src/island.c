#include "island.h"

#include <stdio.h>
#include <stdlib.h>

unsigned get_value(unsigned info_island) {
    return (info_island & BIT_VALUE) >> POS_BIT_VALUE;
}

unsigned get_finished(unsigned info_island) {
    return (info_island & BIT_FINISHED) >> POS_BIT_FINISHED;
}

unsigned get_nb_bridge_up(unsigned info_island) {
    return (info_island & BIT_NB_BRIDGE_UP) >> POS_BIT_NB_BRIDGE_UP;
}

unsigned get_nb_bridge_down(unsigned info_island) {
    return (info_island & BIT_NB_BRIDGE_DOWN) >> POS_BIT_NB_BRIDGE_DOWN;
}

unsigned get_nb_bridge_left(unsigned info_island) {
    return (info_island & BIT_NB_BRIDGE_LEFT) >> POS_BIT_NB_BRIDGE_LEFT;
}

unsigned get_nb_bridge_right(unsigned info_island) {
    return (info_island & BIT_NB_BRIDGE_RIGHT) >> POS_BIT_NB_BRIDGE_RIGHT;
}

unsigned get_up_chosen(unsigned info_backtracking) {
    return (info_backtracking & BIT_UP_CHOSEN) >> POS_BIT_UP_CHOSEN;
}

unsigned get_down_chosen(unsigned info_backtracking) {
    return (info_backtracking & BIT_DOWN_CHOSEN) >> POS_BIT_DOWN_CHOSEN;
}

unsigned get_left_chosen(unsigned info_backtracking) {
    return (info_backtracking & BIT_LEFT_CHOSEN) >> POS_BIT_LEFT_CHOSEN;
}

unsigned get_right_chosen(unsigned info_backtracking) {
    return (info_backtracking & BIT_RIGHT_CHOSEN) >> POS_BIT_RIGHT_CHOSEN;
}

unsigned get_stuck_island(unsigned info_backtracking) {
    return (info_backtracking & BIT_STUCK_ISLAND) >> POS_BIT_STUCK_ISLAND;
}

unsigned get_x(unsigned position) {
    return (position & BIT_X) >> POS_BIT_X;
}

unsigned get_y(unsigned position) {
    return (position & BIT_Y) >> POS_BIT_Y;
}

void set_value(unsigned *info_island, unsigned value) {
    *info_island = (*info_island & (0xFFFF - BIT_VALUE)) | (value << POS_BIT_VALUE);
}

void set_finished(unsigned *info_island, unsigned finished) {
    *info_island = (*info_island & (0xFFFF - BIT_FINISHED)) | (finished << POS_BIT_FINISHED);
}

void set_nb_bridge_up(unsigned *info_island, unsigned nb_bridge_up) {
    *info_island = (*info_island & (0xFFFF - BIT_NB_BRIDGE_UP)) | (nb_bridge_up << POS_BIT_NB_BRIDGE_UP);
}

void set_nb_bridge_down(unsigned *info_island, unsigned nb_bridge_down) {
    *info_island = (*info_island & (0xFFFF - BIT_NB_BRIDGE_DOWN)) | (nb_bridge_down << POS_BIT_NB_BRIDGE_DOWN);
}

void set_nb_bridge_left(unsigned *info_island, unsigned nb_bridge_left) {
    *info_island = (*info_island & (0xFFFF - BIT_NB_BRIDGE_LEFT)) | (nb_bridge_left << POS_BIT_NB_BRIDGE_LEFT);
}

void set_nb_bridge_right(unsigned *info_island, unsigned nb_bridge_right) {
    *info_island = (*info_island & (0xFFFF - BIT_NB_BRIDGE_RIGHT)) | (nb_bridge_right << POS_BIT_NB_BRIDGE_RIGHT);
}

void set_up_chosen(unsigned *info_backtracking, unsigned up_chosen) {
    *info_backtracking = (*info_backtracking & (0xFFFF - BIT_UP_CHOSEN)) | (up_chosen << POS_BIT_UP_CHOSEN);
}

void set_down_chosen(unsigned *info_backtracking, unsigned down_chosen) {
    *info_backtracking = (*info_backtracking & (0xFFFF - BIT_DOWN_CHOSEN)) | (down_chosen << POS_BIT_DOWN_CHOSEN);
}

void set_left_chosen(unsigned *info_backtracking, unsigned left_chosen) {
    *info_backtracking = (*info_backtracking & (0xFFFF - BIT_LEFT_CHOSEN)) | (left_chosen << POS_BIT_LEFT_CHOSEN);
}

void set_right_chosen(unsigned *info_backtracking, unsigned right_chosen) {
    *info_backtracking = (*info_backtracking & (0xFFFF - BIT_RIGHT_CHOSEN)) | (right_chosen << POS_BIT_RIGHT_CHOSEN);
}

void set_stuck_island(unsigned *info_backtracking, unsigned stuck_island) {
    *info_backtracking = (*info_backtracking & (0xFFFF - BIT_STUCK_ISLAND)) | (stuck_island << POS_BIT_STUCK_ISLAND);
}

void set_x(unsigned *position, unsigned x) {
    *position = (*position & (0xFFFF - BIT_X)) | (x << POS_BIT_X);
}

void set_y(unsigned *position, unsigned y) {
    *position = (*position & (0xFFFF - BIT_Y)) | (y << POS_BIT_Y);
}

void initialize(Grid* grid, unsigned size_grid, unsigned nb_island) {
  grid->bridges_x = malloc(sizeof(unsigned)*(size_grid*size_grid));
  for(unsigned i = 0; i < (size_grid*size_grid); i++){
    grid->bridges_x[i]=0;
  }
  grid->bridges_y = malloc(sizeof(unsigned)*(size_grid*size_grid));
  for(unsigned i = 0; i < (size_grid*size_grid); i++){
    grid->bridges_y[i]=0;
  }
  grid->bridges_d = malloc(sizeof(unsigned)*(size_grid*size_grid));
  for(unsigned i = 0; i < (size_grid*size_grid); i++){
    grid->bridges_d[i]=0;
  }
  grid->pos = 0;
  grid->heuristic_used = 1;
  grid->chosen_island = NULL;

  /* Allocation de la m�moire pour islands */
  grid->islands = malloc(sizeof(Island) * nb_island);
  if (grid->islands == NULL) {
    fprintf(stderr, "Allocation error.");
    exit(EXIT_FAILURE);
  }

  for (unsigned i = 0; i < nb_island; i++) {
    grid->islands[i] = (Island) {0};
  }
}

Stack create_stack(){
	Stack s = malloc(sizeof(struct stack_t));
	if (s == NULL){
		fprintf(stderr, "problème d'allocation");
		exit(EXIT_FAILURE);
	}
	s->tab = malloc(10*sizeof(Grid));
	if (s->tab == NULL){
		fprintf(stderr, "problème d'allocation");
		exit(EXIT_FAILURE);
	}
	s->capacity = 10;
	s->size = 0;
	return s;
}

void copy_game(Grid src, Grid *dst, unsigned size_grid, unsigned nb_island){
    for(unsigned j = 0; j < nb_island; j++){
    	dst->islands[j].position = src.islands[j].position;
    	dst->islands[j].information_island = src.islands[j].information_island;
    	dst->islands[j].information_backtracking = src.islands[j].information_backtracking;
    	dst->islands[j].up_neighbor = src.islands[j].up_neighbor;
    	dst->islands[j].down_neighbor = src.islands[j].down_neighbor;
    	dst->islands[j].left_neighbor = src.islands[j].left_neighbor;
    	dst->islands[j].right_neighbor = src.islands[j].right_neighbor;
    	dst->islands[j].linked_up_island = src.islands[j].linked_up_island;
    	dst->islands[j].linked_down_island = src.islands[j].linked_down_island;
    	dst->islands[j].linked_left_island = src.islands[j].linked_left_island;
    	dst->islands[j].linked_right_island = src.islands[j].linked_right_island;
    }
    for(unsigned i = 0; i < src.pos; i++){
    	dst->bridges_x[i] = src.bridges_x[i];
       	dst->bridges_y[i] = src.bridges_y[i];
        dst->bridges_d[i] = src.bridges_d[i];

    }
    for(unsigned i = src.pos; i < (size_grid*size_grid); i++) {
        dst->bridges_x[i] = 0;
        dst->bridges_y[i] = 0;
        dst->bridges_d[i] = 0;
    }
    dst->pos = src.pos;
    dst->heuristic_used = 1;
    dst->chosen_island = src.chosen_island;
}

void copy_game_but_not_backtracking(Grid src, Grid *dst, unsigned size_grid, unsigned nb_island){
    for(unsigned j = 0; j < nb_island; j++){
    	dst->islands[j].position = src.islands[j].position;
    	dst->islands[j].information_island = src.islands[j].information_island;
    	dst->islands[j].up_neighbor = src.islands[j].up_neighbor;
    	dst->islands[j].down_neighbor = src.islands[j].down_neighbor;
    	dst->islands[j].left_neighbor = src.islands[j].left_neighbor;
    	dst->islands[j].right_neighbor = src.islands[j].right_neighbor;
    	dst->islands[j].linked_up_island = src.islands[j].linked_up_island;
    	dst->islands[j].linked_down_island = src.islands[j].linked_down_island;
    	dst->islands[j].linked_left_island = src.islands[j].linked_left_island;
    	dst->islands[j].linked_right_island = src.islands[j].linked_right_island;
    }
    for(unsigned i = 0; i < src.pos; i++){
    	dst->bridges_x[i] = src.bridges_x[i];
       	dst->bridges_y[i] = src.bridges_y[i];
        dst->bridges_d[i] = src.bridges_d[i];

    }
    for(unsigned i = src.pos; i < (size_grid*size_grid); i++) {
        dst->bridges_x[i] = 0;
        dst->bridges_y[i] = 0;
        dst->bridges_d[i] = 0;
    }
    dst->pos = src.pos;
    dst->heuristic_used = 1;
    dst->chosen_island = src.chosen_island;
}

void delete_game(Stack s, Grid* grid){
  free(grid->islands);
  free(grid->bridges_x);
  free(grid->bridges_y);
  free(grid->bridges_d);
  grid = NULL;

  s->size--;
}

void delete_stack(Stack s){
    while(s->size > 0) {
	    delete_game(s, &(s->tab[s->size-1]));
    }
    free(s->tab);

	free(s);
}

void insert_value(Stack s, Grid g, unsigned size_grid, unsigned nb_island){
	if(s->size >= s->capacity){ 	//réallocation de 2* la capacité du tas
		unsigned new_size = 2*s->capacity;
    	s->tab = realloc(s->tab, new_size*sizeof(Grid));
    	s->capacity = new_size;
	}
    initialize(&(s->tab[s->size]), size_grid, nb_island);
	copy_game (g, &(s->tab[s->size]), size_grid, nb_island);
	s->size++;
}

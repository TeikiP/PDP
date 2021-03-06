#ifndef COMPOSITES_H
#define COMPOSITES_H

#include <stdint.h>

typedef struct composites_set_t composites_set_t;

typedef struct composites_set_t {
  /* Bit by bit representation of factors that make up the target number. */
  uint64_t factors;
  /* Next set of factors that make up this same number. */
  composites_set_t* next;
} composites_set_t;

/* Returns the number of factors within the given set. */
unsigned short get_set_length(composites_set_t* set);

/* Deallocates a composites_set_t and all linked composites_set_t. */
void free_composites_set(composites_set_t* set);

/* Prints all factors within the given and linked composites_set_t. */
void print_composites_set(composites_set_t* set);

/* Finds and returns composites_set_t of 'length' elements that make up the
 * 'product' given as an argument, with 'max size' being the upper limit that a
 * factor can be. */
composites_set_t* find_composites(unsigned long long product,
                                  unsigned int max_size,
                                  unsigned short length);

#endif /* COMPOSITES_H */

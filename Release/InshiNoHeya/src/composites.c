#include "composites.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

struct composite_t {
  /* Factor that makes up the factorized number. */
  uint64_t factor;
  /* Next factor that makes up the factorized number. */
  Composite* next;
};

struct composites_set_t {
  /* First factor that makes up this number. */
  Composite* first_factor;
  /* Next set of factors that make up this same number. */
  CompositesSet* next;
};

/* Allocates, initializes and returns a new Composite. */
Composite* generate_empty_composite() {
  Composite* new_composite = malloc(sizeof(Composite));
  new_composite->factor = 0;
  new_composite->next = NULL;

  return new_composite;
}

/* Allocates, initializes and returns a new CompositesSet. */
CompositesSet* generate_empty_set() {
  CompositesSet* new_set = malloc(sizeof(CompositesSet));
  new_set->first_factor = generate_empty_composite();
  new_set->next = NULL;

  return new_set;
}

/* This function does not currently work as intended due to a pointer issue. */
/* Deallocates a Composite and all linked Composites. */
void free_composite(Composite* composite) {
  if (composite != NULL) {
    while (composite->next != NULL)
      free_composite(composite->next);

    free(composite);
  }
}

/* Deallocates a CompositesSet and all linked CompositesSets. */
void free_composites_set(CompositesSet* set) {
  if (set != NULL) {
    while (set->next != NULL)
      free_composites_set(set->next);

    free_composite(set->first_factor);
    free(set);
  }
}

/* Prints all values of Composites within linked CompositesSets. */
void print_composites_set(CompositesSet* set) {
  while (set != NULL) {
    Composite* factor = set->first_factor;

    while (factor != NULL) {
      printf("%lu ", factor->factor);

      factor = factor->next;
    }

    printf("\n");

    set = set->next;
  }
}

/* Find and returns CompositesSets that make up the product given as an
 * argument. */
CompositesSet* find_composites(int product) {
  CompositesSet* starting_set = generate_empty_set();
  CompositesSet* iterator = starting_set;

  /* Add (product) */
  add_composite_to_set(iterator->first_factor, product);
  iterator->next = generate_empty_set();
  iterator = iterator->next;

  /* Add (product * 1) */
  add_composites_to_set(iterator->first_factor, product, 1);
  iterator->next = generate_empty_set();
  iterator = iterator->next;

  /* Trial division */
  unsigned int limit = floor(sqrt(product));

  for (unsigned int factor = 2; factor < limit; factor++) {
    if (product % factor == 0 && product / factor != factor) {
      /* Add both factors found */
      add_composites_to_set(iterator->first_factor, factor, product / factor);

      iterator->next = generate_empty_set();
      iterator = iterator->next;

      /* Add both factors and 1 */
      add_composites_to_set(iterator->first_factor, factor, product / factor);
      add_composite_to_set(iterator->first_factor, 1);

      iterator->next = generate_empty_set();
      iterator = iterator->next;
    }
  }

  free(iterator);

  return starting_set;
}

/* This function is currently unfinished. */
/* Merges two composites sets. */
void merge_sets(CompositesSet* main_set, CompositesSet* sub_set) {
  (void)sub_set;

  /* Find last set in main set */
  while (main_set->next != NULL)
    main_set = main_set->next;

  /* Make a copy of last composite of the current main set */
  /*Composite *original = copy_composite(main_set->first_factor);*/

  /* Find last composite in current main set */
  Composite* iterator = main_set->first_factor;
  while (iterator->next != NULL)
    iterator = iterator->next;

  /* Add first sub set to current composite in main set */
  iterator->next = copy_composite(sub_set->first_factor);

  /* Repeat for next set in sub_set */
  /* TODO */

  /* Sort sets and filter duplicates and sets with duplicate numbers */
  /* TODO */

  /* Free unused memory */
  /*free_composites_set(sub_set);*/
}

/* Adds the factor given as the last element to the Composite linked list given.
 */
void add_composite_to_set(Composite* first_factor, uint64_t factor) {
  Composite* iterator = first_factor;

  /* Find the end of the set */
  while (iterator->next != NULL)
    iterator = iterator->next;

  /* Add factor at the end */
  if (iterator->factor != 0) {
    iterator->next = generate_empty_composite();
    iterator = iterator->next;
  }

  iterator->factor = factor;
}

/* Adds the factors given as the lasts elements to the Composite linked list
 * given. */
void add_composites_to_set(Composite* first_factor,
                           uint64_t factor1,
                           uint64_t factor2) {
  Composite* iterator = first_factor;

  /* Find the end of the set */
  while (iterator->next != NULL)
    iterator = iterator->next;

  /* Add factors at the end */
  if (iterator->factor != 0) {
    iterator->next = generate_empty_composite();
    iterator = iterator->next;
  }

  iterator->factor = factor1;

  iterator->next = generate_empty_composite();
  iterator = iterator->next;
  iterator->factor = factor2;
}

/* Takes a composite and returns a new one with the exact same values for it and
 * its linked Composites. */
Composite* copy_composite(Composite* composite_to_copy) {
  Composite* new_composite = malloc(sizeof(Composite));
  new_composite->factor = composite_to_copy->factor;

  Composite* original_iterator = composite_to_copy;
  Composite* new_iterator = new_composite;

  /* Copy all Composites */
  while (original_iterator->next != NULL) {
    original_iterator = original_iterator->next;

    new_iterator->next = malloc(sizeof(Composite));
    new_iterator = new_iterator->next;
    new_iterator->factor = original_iterator->factor;
  }

  new_iterator->next = NULL;

  return new_composite;
}

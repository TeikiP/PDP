#ifndef COMPOSITES_H
#define COMPOSITES_H

#include <stdint.h>

typedef struct composite_t Composite;

typedef struct composites_set_t CompositesSet;

void free_composite(Composite* composite);

void free_composites_set(CompositesSet* set);

void print_composites_set(CompositesSet* set);

Composite* generate_empty_composite();

CompositesSet* generate_empty_set();

CompositesSet* find_composites(int product);

void add_composite_to_set(Composite* first_factor, uint64_t factor);

void add_composites_to_set(Composite* first_factor,
                           uint64_t factor1,
                           uint64_t factor2);

Composite* copy_composite(Composite* composite_to_copy);

void merge_sets(CompositesSet* main_set, CompositesSet* sub_set);

#endif /* COMPOSITES_H */

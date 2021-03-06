#ifndef BITSET_H
#define BITSET_H

#include <stdint.h>

/*  ACCESS, SET & GET  */

/* Sets the bit at a specific position of the provided value to 1. */
uint64_t set_bit(uint64_t value, unsigned short position);

/* Sets the bit at a specific position of the provided value to 0. */
uint64_t clear_bit(uint64_t value, unsigned short position);

/* Toggle the bit at a specific position of the provided value. */
uint64_t toggle_bit(uint64_t value, unsigned short position);

/* Returns the value of the bit at a specific position of the provided value. */
unsigned short check_bit(uint64_t value, unsigned short position);

/* Prints the value of each bit for a given number. */
void print_bits(uint64_t value);

/*  BASIC OPERATIONS  */

/* Returns the bitwise intersection of two values. */
uint64_t bits_and(uint64_t value1, uint64_t value2);

/* Returns the bitwise union of two values. */
uint64_t bits_or(uint64_t value1, uint64_t value2);

/* Returns the bitwise exclusive union of two values. */
uint64_t bits_xor(uint64_t value1, uint64_t value2);

/* Returns the bitwise flip of a value. */
uint64_t bits_flip(uint64_t value);

/*  SINGLETON & FFS  */

/* Returns the position of the first bit set to 1 within the provided integer.
 * If no bits are set, returns 0. */
unsigned short find_first_set(uint64_t value);

/* Returns 1 if the value is a singleton, otherwise 0. */
unsigned short is_singleton(uint64_t value);

/* Returns the position of the single bit set,
 * returns 0 if more than one bit is set or none. */
unsigned short find_singleton_position(uint64_t value);

/*  POPULATION COUNTING  */

/* Cardinality #1 */
/* SWAR algorthim to count the number of bits set within an integer. */
/* Method provided by Guemon Amelie (Sudoku) and Matt Howells (StackOverflow).
 */
unsigned short popcount_mit_hakmem(uint64_t value);

/* Cardinality #2 */
/* SWAR algorthim to count the number of bits set within an integer. */
/* Source: http://graphics.stanford.edu/~seander/bithacks.html */
unsigned short popcount_lookup_table(uint64_t value);

/* Cardinality #3 */
/* Algorthim to count the number of bits set within an integer. */
/* Source: http://graphics.stanford.edu/~seander/bithacks.html */
unsigned short popcount_naive(uint64_t value);

/* Cardinality #4 */
/* Brian Kernighan's algorthim to count the number of bits set within an
 * integer. */
/* Source: http://graphics.stanford.edu/~seander/bithacks.html */
unsigned short popcount_kernighan(uint64_t value);

/* Cardinality #5 */
/* GCC function to call upon system specific preprocessor population counting
 * algorithm. */
unsigned short popcount_preprocessor(uint64_t value);

#endif /* BITSET_H */

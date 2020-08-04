#include "providedCode/bf.h"
#include "providedCode/bv.h"
#include "providedCode/speck.h"
#include <stdio.h>
#include <stdlib.h>

// Creates bloomfilter (bitvector) with size (size)
// Returns bloomfilter
//
// size:  size of bloomfilter (bitvector)
//
BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf) {
    bf->primary[0] = 0xfc28ca6885711cf7;
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3;
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0;
    bf->tertiary[1] = 0x911d454886ca7cf7;
    bf->filter = bv_create(size);
    return bf;
  }
  return (BloomFilter *)NIL;
}

// Frees memory allocated by bloomfilter and bitvector
//
// b:	BloomFilter to free memory
//
void bf_delete(BloomFilter *b) {

  if (b) {
    bv_delete(b->filter);
    free(b);
  }
}

// Returns length of bloomfilter
//
// b:	BloomFilter to get length
//
uint32_t bf_length(BloomFilter *b) {

  if (b) {
    return bv_length(b->filter);
  }
  return 0;
}

// Inserts hashed key into bitvector, uses speck.c hash
//
// b:	BloomFilter
// key:	Key (oldspeak) to insert
//
void bf_insert(BloomFilter *b, char *key) {

  uint32_t size = bf_length(b);
  if (b && key) {
    bv_set_bit(b->filter, hash(b->primary, key) % size);
    bv_set_bit(b->filter, hash(b->secondary, key) % size);
    bv_set_bit(b->filter, hash(b->tertiary, key) % size);
  }
}

// Checks bloomfilter if key is in the bloomfilter
// Returns true or false
//
// b:	BloomFilter
// key:	Key to to filter
//
bool bf_probe(BloomFilter *b, char *key) {

  uint32_t size = bv_length(b->filter);
  bool first, second, third;
  first = second = third = false;
  if (bv_get_bit(b->filter, hash(b->primary, key) % size)) {
    first = true;
  }
  if (bv_get_bit(b->filter, hash(b->secondary, key) % size)) {
    second = true;
  }
  if (bv_get_bit(b->filter, hash(b->tertiary, key) % size)) {
    third = true;
  }
  if (first && second && third) {
    return true;
  }
  return false;
}

// Counts how many indexes in bloomfilter
// Returns number of indexed bits
//
// b:	BloomFilter
//
uint32_t bf_count(BloomFilter *b) {

  uint32_t size = bv_length(b->filter);
  uint32_t count = 0;
  for (uint32_t i = 0; i < size; i++) {
    if (bv_get_bit(b->filter, i)) {
      count += 1;
    }
  }
  return count;
}

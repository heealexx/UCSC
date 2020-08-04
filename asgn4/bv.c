#include "bv.h"

#include <stdio.h>
#include <stdlib.h>

// Creates and returns a bitvector
//
// bit_len:	Length of BitVector
//
BitVector *bv_create(uint32_t bit_len) {

  BitVector *bitvector = (BitVector *)malloc(sizeof(BitVector));
  if (bitvector == NULL) {
    printf("error, malloc return null");
    return NULL;
  }
  bitvector->vector = (uint8_t *)malloc((bit_len / 8 + 1) * sizeof(uint8_t));
  if (bitvector->vector == NULL) {
    printf("error, malloc return null");
    return NULL;
  }
  bitvector->length = bit_len;

  return bitvector;
}

// Frees the BitVector
//
// v:	Bitvector to free
//
void bv_delete(BitVector *v) {

  free(v->vector);
  free(v);
  return;
}

// Returns length of bitvector
//
// v:	Bitvector to get length from
//
uint32_t bv_get_len(BitVector *v) { 
  
  return v->length;

}

// Set bit to 1 in BitVector
//
// v:	BitVector
// i:	index of bit to set
//
void bv_set_bit(BitVector *v, uint32_t i) {

  uint8_t x = 0x80;
  x = x >> (i % 8);
  v->vector[i / 8] = v->vector[i / 8] | x;
  return;
}

// Clear bit to 0 in BitVector
//
// v:	BitVector
// i: 	index of bit to clear
//
void bv_clr_bit(BitVector *v, uint32_t i) {

  uint8_t x = 0x80;
  x = x >> (i % 8);
  x = ~x;
  v->vector[i / 8] = v->vector[i / 8] & x;
  return;
}

// Get value of bit in bitvector
// Returns value of bit, either 0 or 1
//
// v:	Bitvector to get bit from
// i:	index of bit to get
uint8_t bv_get_bit(BitVector *v, uint32_t i) {

  uint8_t x = 0x80;
  x = x >> i % 8;
  if ((v->vector[i / 8] & x) > 0) {
    return 1;
  } else {
    return 0;
  }
}

// Set all bits of bitvector to 1
//
// v:	BitVector to set
//
void bv_set_all_bits(BitVector *v) {

  uint8_t x = 0xFF;
  for (uint8_t i = 0; i <= (v->length / 8 + 1); i++) {
    v->vector[i] = v->vector[i] | x;
  }
  return;
}

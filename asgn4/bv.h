// bv.h - Contains function declarations for BitVector ADT

#ifndef __BV_H__
#define __BV_H__

#include <inttypes.h>
#include <stdbool.h>

// Struct definition for a BitVector
//
// vector:	Vector of bytes to hold bits
// length: 	Length in bits of the BitVector
//
typedef struct BitVector {
  uint8_t *vector;
  uint32_t length;
} BitVector;

// Creates new BitVector of specified length
//
// bit_len:	Length in bits of BitVector
//
BitVector *bv_create(uint32_t bit_len);

// Frees memory allocated for a BitVector
//
// v:	The BitVecotr
//
void bv_delete(BitVector *v);

// Returns the length in bits of the BitVector
//
// v:	The BitVector
//
uint32_t bv_get_len(BitVector *v);

// Sets the bit at index in the BitVecotr
//
// v:	The BitVector
// i:	index of the bit to set
//
void bv_set_bit(BitVector *v, uint32_t i);

// Clears the bit at index in the BitVector
//
// v:	The BitVector
// i:	Index of the bit to clear
//
void bv_clr_bit(BitVector *v, uint32_t i);

// Gets a bit from a BitVector
//
// v:	The BitVector
// i:	Index of bit to get
//
uint8_t bv_get_bit(BitVector *v, uint32_t i);

// Sets all bits in a BitVector
//
// v:	The BitVector
//
void bv_set_all_bits(BitVector *v);

#endif

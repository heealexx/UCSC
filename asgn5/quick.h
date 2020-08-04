#ifndef __QUICK_H__
#define __QUICK_H__

#include <inttypes.h>

extern uint64_t quick_moves;
extern uint64_t quick_compare;

int64_t partition(uint32_t arr[], int64_t left, int64_t right);

int quicksort(uint32_t arr[], int64_t left, int64_t right);

#endif

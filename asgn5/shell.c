#include "shell.h"
#include <inttypes.h>

uint64_t shell_compare = 0;
uint64_t shell_moves = 0;

// Code based off pseudcode from Prof Long
// Uses a gap to sort elements far apart first, then finishes with smaller gaps
// between
//
// arr[]:  Array to be sorted
// length:  Length of the array
//
int shellsort(uint32_t arr[], uint32_t length) {

  uint32_t temp;
  for (uint32_t gap = length * 5 / 11; gap >= 1;
       gap = gap * 5 / 11) { // Gap generator
    if (gap <= 2) {
      gap = 1;
    }
    for (uint32_t i = gap; i < length; i++) {
      for (uint32_t j = i; j > gap - 1; j -= gap) { // Each step in the gap
        shell_compare += 1;
        if (arr[j] < arr[j - gap]) {
          temp = arr[j];
          arr[j] = arr[j - gap];
          arr[j - gap] = temp;
          shell_moves += 3;
        }
      }
    }
  }

  return 0;
}

#include "bubble.h"
#include <inttypes.h>
#include <stdio.h>

uint64_t bub_compare = 0;
uint64_t bub_moves = 0;

// Code based of off psuedocode provided by Prof Long
// Uses bubblesort to sort an array, swapping pair values until fully sorted
//
// arr[]:  Array to be sorted
// length:  Length of the array
int bubblesort(uint32_t arr[], uint32_t length) {

  uint32_t temp;
  for (uint32_t i = 0; i <= length - 1; i++) { // Loop through whole array
    uint32_t j = length - 1;
    while (j > i) {
      bub_compare += 1;
      if (arr[j] < arr[j - 1]) { // Checks if values should be swapped
        temp = arr[j - 1];
        arr[j - 1] = arr[j];
        arr[j] = temp;
        bub_moves += 3;
      }
      j -= 1;
    }
    if (bub_moves == 0) { // If no moves made in first round, ends loop
      break;
    }
  }
  return 0;
}

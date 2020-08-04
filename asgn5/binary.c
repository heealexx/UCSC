#include "binary.h"
#include <inttypes.h>
#include <stdio.h>

uint64_t binary_compare = 0;
uint64_t binary_moves = 0;

// Code based of psuedocode provided by Prof Long
// Uses binary insertion to sort an array, finds correct position using binary
// search
//
// arr[]:  Array to be sorted
// length:  Length of the array
//
int binary_insert(uint32_t arr[], uint32_t length) {

  uint32_t value, left, right, mid, temp;

  for (uint32_t i = 1; i <= length; i++) { // Loops through whole array
    value = arr[i];                        // Value to be sorted
    left = 0;
    right = i;

    while (left < right) {
      mid = left + ((right - left) / 2);
      binary_compare += 1;
      if (value >= arr[mid]) { // Decides if value is left or right of mid
        left = mid + 1;
      } else {
        right = mid;
      }
    }

    for (uint32_t j = i; j > left; j -= 1) {
      temp = arr[j];
      arr[j] = arr[j - 1];
      arr[j - 1] = temp;
      binary_moves += 3;
    }
  }

  return 0;
}

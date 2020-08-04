#include "quick.h"
#include <inttypes.h>
#include <stdbool.h>

uint64_t quick_compare = 0;
uint64_t quick_moves = 0;

// Code based of psuedocode provided by Prof Long
// "Splits" array with a pivot point, lesser on left, greater on right
// Called multiple times on the "splitted" array until sorted
//
// arr[]:  Array to be sorted
// left:  Left index
// right:  Right index
//
int64_t partition(uint32_t arr[], int64_t left, int64_t right) {

  int64_t pivot = arr[left]; // Left most value is pivot
  quick_moves += 1;
  int64_t lo = left + 1;
  int64_t hi = right;
  int64_t temp;

  while (true) {
    while (lo <= hi && arr[hi] >= pivot) { // While low is less than high index
      hi -= 1;
      quick_compare += 1;
    }
    if (lo > hi || arr[hi] < pivot) { // Counts compare if while breaks
      quick_compare += 1;
    }
    while (lo <= hi && arr[lo] <= pivot) {
      lo += 1;
      quick_compare += 1;
    }
    if (lo > hi || arr[lo] > pivot) {
      quick_compare += 1;
    }
    if (lo <= hi) { // Swaps when found two values to switch and low < high
      temp = arr[lo];
      arr[lo] = arr[hi];
      arr[hi] = temp;
      quick_moves += 3;
    } else {
      break;
    }
  }

  temp = arr[left];
  arr[left] = arr[hi];
  arr[hi] = temp;
  quick_moves += 3;

  return hi;
}
// Calls partition function if still not sorted, stops calling when done
//
// arr[]:  Array to be sorted
// left:  Left bound
// right:  Right bound
//
int quicksort(uint32_t arr[], int64_t left, int64_t right) {

  if (left < right) { // Checks if left index went over right
    int64_t index = partition(arr, left, right);
    quicksort(arr, left, index - 1);
    quicksort(arr, index + 1, right);
  }

  return 0;
}

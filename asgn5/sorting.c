#include "binary.h"
#include "bubble.h"
#include "quick.h"
#include "shell.h"

#include <getopt.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PRINT 100
#define DEFAULT_SEED 8222022
#define DEFAULT_SIZE 100

int make_array(uint32_t *array, uint32_t size);
int print_array(uint32_t *array, uint32_t n, uint32_t size, int sort);

// Parses through user input, calling and printing the appropriate sorts.
//
int main(int argc, char **argv) {

  int c = 0;
  bool bub, binary, shell, quick;
  bub = binary = shell = quick = false;
  uint32_t n = DEFAULT_PRINT;
  uint32_t s = DEFAULT_SEED;
  uint32_t size = DEFAULT_SIZE;

  while ((c = getopt(argc, argv, "Absqip:r:n:")) != -1) {
    switch (c) {
    case 'A':
      bub = true;
      shell = true;
      quick = true;
      binary = true;
      break;
    case 'b':
      bub = true;
      break;
    case 's':
      shell = true;
      break;
    case 'q':
      quick = true;
      break;
    case 'i':
      binary = true;
      break;
    case 'p':
      if (atoi(optarg) > 0) {
        n = atoi(optarg);
      } else {
        printf("Invalid input");
        return -1;
      }
      break;
    case 'r':
      if (atoi(optarg) > 0) {
        s = atoi(optarg);
      } else {
        printf("Invalid seed");
        return -1;
      }
      break;
    case 'n':
      if (atoi(optarg) > 0) {
        size = atoi(optarg);
      } else {
        printf("Invalid size");
        return -1;
      }
      break;
    default:
      break;
    }
  }

  uint32_t *array = (uint32_t *)calloc(size, sizeof(uint32_t));

  if (n > size) {
    n = size;
  }

  if (bub) {
    srand(s); // resets seed
    make_array(array, size);
    bubblesort(array, size);
    print_array(array, n, size, 0);
  }

  if (shell) {
    srand(s);
    make_array(array, size);
    shellsort(array, size);
    print_array(array, n, size, 1);
  }

  if (quick) {
    srand(s);
    make_array(array, size);
    quicksort(array, 0, size - 1);
    print_array(array, n, size, 2);
  }

  if (binary) {
    srand(s);
    make_array(array, size);
    binary_insert(array, size - 1);
    print_array(array, n, size, 3);
  }

  free(array);

  return 0;
}

// Makes array of random numbers from specified seed
// Numbers limited to 30 bit size
//
// array:  Array pointer
// size:  Size of array
//
int make_array(uint32_t *array, uint32_t size) {

  for (uint32_t i = 0; i < size; i++) {
    uint32_t num = rand() & 0x3FFFFFFF; // Masks random number
    array[i] = num;
  }

  return 0;
}

// Prints array, deciding which sort it is and printing specified performance
// stats
//
// array:  Array pointer to print
// n:  Number of elements in array to print
// size:  Size of array
// sort:  Which sort to print
//
int print_array(uint32_t *array, uint32_t n, uint32_t size, int sort) {

  if (sort == 0) {
    printf("Bubble Sort\n");
    printf("%" PRIu32 " elements, "
           "%" PRIu64 " moves, "
           "%" PRIu64 " compares\n",
           size, bub_moves, bub_compare);
  } else if (sort == 1) {
    printf("Shell Sort\n");
    printf("%" PRIu32 " elements, "
           "%" PRIu64 " moves, "
           "%" PRIu64 " compares\n",
           size, shell_moves, shell_compare);
  } else if (sort == 2) {
    printf("Quick Sort\n");
    printf("%" PRIu32 " elements, "
           "%" PRIu64 " moves, "
           "%" PRIu64 " compares\n",
           size, quick_moves, quick_compare);
  } else if (sort == 3) {
    printf("Binary Insertion Sort\n");
    printf("%" PRIu32 " elements, "
           "%" PRIu64 " moves, "
           "%" PRIu64 " compares\n",
           size, binary_moves, binary_compare);
  }

  for (uint32_t i = 0; i < n; i++) {
    printf("%12" PRIu32, array[i]);
    if ((i + 1) % 7 == 0) {
      printf("\n");
    }
  }
  printf("\n");

  return 0;
}

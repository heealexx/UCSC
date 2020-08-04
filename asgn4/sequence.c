#include "bv.h"
#include "sieve.h"

#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define OPTIONS "spn:"
#define DEFAULT 1000
#define BYTES 15 // Log[18446744073709551616] / Log[36] + 1 + 1

uint32_t fib(uint32_t n);
uint32_t luc(uint32_t n);
uint32_t mers(uint32_t n);
int printer(BitVector *v);
char *convert(uint32_t n, int base);
bool isPalindrome(char *s);
int palindrome_pr(BitVector *v, int base);

// Parse through arguements for flags
int main(int argc, char **argv) {

  int c = 0;
  int n = DEFAULT;
  bool printp = false;
  bool printpal = false;

  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'p':
      printpal = true;
      break;
    case 's':
      printp = true;
      break;
    case 'n':
      if (atoi(optarg) > 0) {
        n = atoi(optarg);
      } else {
        printf("Invalid number");
        return -1;
      }
      break;
    default:
      break;
    }
  }

  BitVector *v = bv_create(n);
  sieve(v);

  if (printp) {
    printer(v);
  }

  if (printpal) {
    palindrome_pr(v, 2);
    palindrome_pr(v, 10);
    palindrome_pr(v, 14);
    palindrome_pr(v, 18);
  }

  bv_delete(v);
  return 0;
}

// Calculates fibonnaci number until it is equal or greater than input
// Returns Fibonnaci number
//
// n:	input
//
uint32_t fib(uint32_t n) {

  static uint32_t first = 0;
  static uint32_t second = 1;
  static uint32_t sum = 0;

  if (n == first || n == second) {
    return n;
  }

  while (sum < n) {
    sum = first + second;
    first = second;
    second = sum;
  }
  return sum;
}

// Calculates Lucas number until it is greater or equal to input
// Returns Lucas number
//
// n:	input
//
uint32_t luc(uint32_t n) {

  static uint32_t first = 2;
  static uint32_t second = 1;
  static uint32_t luc = 0;

  if (n == first | n == second) {
    return n;
  }

  while (luc < n) {
    luc = first + second;
    first = second;
    second = luc;
  }

  return luc;
}

// Calculates Mersenne number until it is greater or equal to input
// Returns that Mersenne number
//
// n:	input
//
uint32_t mers(uint32_t n) {

  static uint32_t mers = 0;

  if (n == mers) {
    return mers;
  }

  while (mers < n) {
    mers *= 2;
    mers += 1;
  }

  return mers;
}

// Prints prime number one at a time, including if it is special
// 
// v:	bitvector with prime numbers set as 1
//
int printer(BitVector *v) {

  printf("\n");
  for (uint32_t i = 0; i < bv_get_len(v); i++) {
    if (bv_get_bit(v, i) >= 1) {
      printf("%"PRIu32": prime", i);
      if (mers(i) == i) {
        printf(", mersenne");
      }
      if (luc(i) == i) {
        printf(", lucas");
      }
      if (fib(i) == i) {
        printf(", fibonacci");
      }
      printf("\n");
    }
  }

  return 0;
}

// (Based off/taken from Prof Long)
// Converts decimal input to specified base
// Returns the string of the converted number

// n:	number in base 10 to convert
// base:	base to convert
//
char *convert(uint32_t n, int base) {

  static char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
  static char s[BYTES];
  char *t = s + BYTES;
  *--t = '\0';

  do {
    *--t = digits[n % base];
    n /= base;

  } while (n > 0);
  return t;
}

// (Based off/from pseudocode on assignment page)
// Checks if a string is a palindrome
// Returns true if it is, false otherwise
//
// s:	input string
//
bool isPalindrome(char *s) {

  int length = strlen(s);
  bool f = true;
  for (int i = 0; i <= (length / 2); i++) {
    if (s[i] != s[length - i - 1]) {
      f = false;
    }
  }

  return f;
}

// prints out prime palindromes in a specified base
//
// v:	bitvector with primes set as 1
// base:	specified base to print
int palindrome_pr(BitVector *v, int base) {

  printf("\n");
  printf("Base %d\n", base);
  printf("---- -\n");
  for (uint32_t i = 0; i < v->length; i++) {
    if (bv_get_bit(v, i) == 1 && isPalindrome(convert(i, base))) {
      printf("%"PRIu32 "= %s\n", i, convert(i, base));
    }
  }

  return 0;
}

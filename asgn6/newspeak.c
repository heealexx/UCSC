#include "providedCode/bf.h"
#include "providedCode/gs.h"
#include "providedCode/hash.h"
#include "providedCode/ll.h"
#include "providedCode/parser.h"

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define H_DEFAULT 10000
#define F_DEFAULT 1048576

bool suppress = false;
bool b = false;
bool isfile = false;
char *infile;
bool bad_print, good_print;
int printmessage(ListNode *bad, ListNode *trans);

// Reads the badspeak.txt file
// Adds forbidden words to bloomfilter and hashtable
//
// fp:	File pointer to badspeak
// bf:	BloomFilter to insert
// ht:	HashTable to insert
//
int read_bad(FILE *fp, BloomFilter *bf, HashTable *ht) {

  char *x = calloc(128, sizeof(char));
  if (x == NULL) {
    printf("error calloc");
    return -1;
  }

  if (fp == NULL) {
    printf("invalid pointer");
    return -1;
  }

  while (fscanf(fp, "%s\n", x) != EOF) {
    bf_insert(bf, x);
    GoodSpeak *gs = gs_create(x, NULL);
    ht_insert(ht, gs);
  }

  free(x);
  return 0;
}

// Reads newspeak text, add oldspeak newspeak translation
// Adds oldspeak with translation to bf and ht
//
// fp:	File pointer to newspeak
// bf:	BloomFilter to insert
// ht:	HashTable to insert
//
int read_new(FILE *fp, BloomFilter *bf, HashTable *ht) {

  char *x = calloc(128, sizeof(char));
  if (x == NULL) {
    printf("error calloc");
    return -1;
  }
  char *y = calloc(128, sizeof(char));
  if (y == NULL) {
    printf("error calloc");
    return -1;
  }

  if (fp == NULL) {
    printf("invalid pointer");
    return -1;
  }

  while (fscanf(fp, "%s %s\n", x, y) != EOF) {
    bf_insert(bf, x);
    GoodSpeak *gs = gs_create(x, y);
    ht_insert(ht, gs);
  }

  free(x);
  free(y);
  return 0;
}

// Uses parser.c to get next word and checks if it's in bloomfilter
// If it is, checks if it has translation
// Splits filtered words into two lists
//
// bf:	BloomFilter to check words
// ht:	HashTable to insert words
// bad:	Linkedlist of forbidden words
// trans:  Linkedlist of translated words
//
int readex(BloomFilter *bf, HashTable *ht, ListNode *bad, ListNode *trans) {

  char *word = calloc(128, sizeof(char));
  if (word == NULL) {
    printf("error calloc");
    return -1;
  }
  regex_t regex;
  int rc;

  FILE *fp = stdin;
  if (isfile) {
    fp = fopen(infile, "r");
  }

  rc = regcomp(&regex, "([A-Za-z0-9À-ÿ_'-])+", REG_EXTENDED);
  if (rc) {
    regerror(rc, &regex, word, 128);
    fprintf(stderr, "Regex compilation failed: %s\n", word);
    return -1;
  }

  while ((word = next_word(fp, &regex)) != NULL) {

    unsigned char *c = (unsigned char *)word;
    while (*c) {
      *c = tolower(*c);
      c++;
    }
    if (bf_probe(bf, word)) {
      ListNode *node = ht_lookup(ht, word);
      if (gs_newspeak(node->gs) != NULL) {
        ll_insert(&trans, node->gs);
        good_print = true;
      } else {
        ll_insert(&bad, node->gs);
        bad_print = true;
      }
    }
  }

  if (!suppress) {
    printmessage(bad, trans);
  }

  free(word);
  clear_words();
  fclose(fp);

  return 0;
}

// Prints message, depending on words used
//
// bad:	Linkedlist of forbidden words
// trans:  Linkedlist of words to be translated
//
int printmessage(ListNode *bad, ListNode *trans) {

  if ((bad_print) && (!good_print)) {
    printf("Dear Comrade,\n\n");
    printf("You have chosen to use degernate words that may cause hurt\n");
    printf("feelings or cause your comrades to think unpleasant thoughts.\n");
    printf("This is doubleplus bad. To correct your wrongthink and\n");
    printf("preserve community consensus we will be sending you to joycamp\n");
    printf("administered by Miniluv.\n\n");
    printf("Your errors:\n\n");
    ll_print(bad);
  }

  if ((!bad_print) && (good_print)) {
    printf("Dear Comrade,\n\n");
    printf("Submitting your text helps to preserve feelings and prevent\n");
    printf("badthink. Some of the words that you used are not goodspeak.\n");
    printf("The list shows how to turn the oldspeak words into newspeak.\n\n");
    ll_print(trans);
  }

  if ((bad_print) && (good_print)) {
    printf("Dear Comrade,\n\n");
    printf("You have chosen to use degenerate words that may cause hurt\n");
    printf("feelings or cause your comrades to think unpleasant thoughts.\n");
    printf("This is doubleplus bad. To correct your wrongthink and\n");
    printf("preserve community consensus we will be sending you to joycamp\n");
    printf("administered by Miniluv.\n\n");
    printf("Your errors:\n\n");
    ll_print(bad);
    printf("\nThink of these words on your vacation!\n\n");
    ll_print(trans);
  }

  return 0;
}

// Main function, parses through arguments
//
int main(int argc, char **argv) {

  int c = 0;
  uint32_t h_size = H_DEFAULT;
  uint32_t f_size = F_DEFAULT;

  while ((c = getopt(argc, argv, "sh:f:mbi:")) != -1) {
    switch (c) {
    case 's':
      suppress = true;
      break;
    case 'h':
      if (atoi(optarg) > 0) {
        h_size = atoi(optarg);
      } else {
        printf("Invalid number");
        return -1;
      }
      break;
    case 'f':
      if (atoi(optarg) > 0) {
        f_size = atoi(optarg);
      } else {
        printf("Invalid number");
        return -1;
      }
      break;
    case 'm':
      move_to_front = true;
      break;
    case 'b':
      b = true;
      break;
    case 'i':
      infile = optarg;
      isfile = true;
      break;
    }
  }

  if (move_to_front && b) {
    printf("invalid flag combination");
    return -1;
  }

  BloomFilter *bf = bf_create(f_size);
  HashTable *ht = ht_create(h_size);

  FILE *fp;
  fp = fopen("badspeak.txt", "r");
  read_bad(fp, bf, ht);
  fclose(fp);

  fp = fopen("newspeak.txt", "r");
  read_new(fp, bf, ht);
  fclose(fp);

  ListNode *bad = NIL;
  ListNode *trans = NIL;
  readex(bf, ht, bad, trans);

  if (suppress) {
    printf("Seeks: %" PRIu32 "\n", seeks);
    printf("Average seek length: %" PRIu32 "\n", links / seeks);
    printf("Hash table load: %" PRIu32 "%%\n", ht_count(ht) / h_size);
    printf("Bloom filter load: %" PRIu32 "%%\n", bf_count(bf) / f_size);
  }

  bf_delete(bf);
  ht_delete(ht);

  return 0;
}

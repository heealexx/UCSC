#include "providedCode/hash.h"
#include "providedCode/ll.h"
#include "providedCode/speck.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// Part of code taken from Prof Long
// Creates hashtable with size length
// Returns hashtable created
//
// length:  Length of pointers (hashtable)
//
HashTable *ht_create(uint32_t length) {

  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) {
    ht->salt[0] = 0x85ae998311115ae3;
    ht->salt[1] = 0xb6fac2ae33a40089;
    ht->length = length;
    ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
    return ht;
  }
  return (HashTable *)NIL;
}

// Frees memory from hashtable
//
// ht:	HashTable to free
//
void ht_delete(HashTable *ht) {

  if (ht) {
    for (uint32_t i = 0; i < ht->length; i++) {
      ll_delete(ht->heads[i]);
    }
  }
  free(ht->heads);
  free(ht);
}

// Looks up if key is in hashtable or not
// Returns listnode of found key if it is there, NULL otherwise
//
// ht:	HashTable
// key:	Key string to search for
//
ListNode *ht_lookup(HashTable *ht, char *key) {

  if (ht && key) {
    return ll_lookup(&ht->heads[hash(ht->salt, key) % ht->length], key);
  }
  return NULL;
}

// Inserts goodspeak struct into hashtable, calling ll_insert
//
// ht:	HashTable
// gs:	Goodspeak struct to add
//
void ht_insert(HashTable *ht, GoodSpeak *gs) {

  if (ht && gs) {
    ll_insert(&ht->heads[hash(ht->salt, gs->oldspeak) % 10000], gs);
  }
}

// Counts how many hashtable indexes are occupied
// Returns number of entries occupied
//
// h: HashTable
//
uint32_t ht_count(HashTable *h) {

  uint32_t length = h->length;
  uint32_t count = 0;
  for (uint32_t i = 0; i < length; i++) {
    if (h->heads[i] != NULL) {
      count += 1;
    }
  }
  return count;
}

// Prints heads of occupied hashtable entries
//
// h:	Hashtable to print
//
void ht_print(HashTable *h) {

  uint32_t length = h->length;
  for (uint32_t i = 0; i < length; i++) {
    if (h->heads[i] != NULL) {
      printf("old: %s\tnew: %s\n", h->heads[i]->gs->oldspeak,
          h->heads[i]->gs->newspeak);
    }
  }
}

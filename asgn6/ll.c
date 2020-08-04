#include "providedCode/ll.h"
#include "providedCode/gs.h"
#include "providedCode/hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool move_to_front;
uint32_t seeks = 0;
uint32_t links = 0;

// Code partially based off of Prof Long
// Creates ListNode with the goodspeak struct
// Returns listnode
//
// gs:	Goodspeak struct
//
ListNode *ll_node_create(GoodSpeak *gs) {

  ListNode *n = (ListNode *)malloc(sizeof(ListNode));
  if (n) {
    n->gs = gs;
    n->next = NIL;
  }

  return n;
}

// Frees memory of single linkedlist node
//
// n:	Node to free
//
void ll_node_delete(ListNode *n) {

  if (n) {
    if (n->gs) {
      gs_delete(n->gs);
      free(n);
    }
  }
}

// Frees memory of whole linked list
//
// head:  Head of linked list
//
void ll_delete(ListNode *head) {

  if (head) {
    ListNode *p = head;
    while (p) {
      ListNode *r = p;
      p = p->next;
      ll_node_delete(r);
    }
  }
}

GoodSpeak *ll_node_gs(ListNode *n) {

  if (n) {
    return n->gs;
  }
  return NULL;
}

ListNode *ll_insert(ListNode **head, GoodSpeak *gs) {

  ListNode *node = ll_node_create(gs);
  if (node) {
    node->next = *head;
    *head = node;
    return node;
  }
  return NULL;
}

ListNode *ll_lookup(ListNode **head, char *oldspeak) {

  seeks += 1;
  if (head && oldspeak) {
    ListNode *p = *head;
    ListNode *prev = *head;
    while (p != NIL) {
      links += 1;
      if (strcmp(p->gs->oldspeak, oldspeak) == 0) {
        if (move_to_front) {
          if (p->next) {
            printf("here");
            prev->next = p->next;
          } else {
            prev->next = NIL;
          }
          p->next = *head;
          *head = p;
        }
        return p;
      }
      prev = p;
      p = p->next;
    }
  }
  return NULL;
}

void ll_node_print(ListNode *n) {

  if (n) {
    if (n->gs->oldspeak && n->gs->newspeak) {
      printf("%s -> %s\n", n->gs->oldspeak, n->gs->newspeak);
    } else {
      printf("%s\n", n->gs->oldspeak);
    }
  }
}

void ll_print(ListNode *h) {

  if (h) {
    ListNode *p = h;
    while (p != NIL) {
      ll_node_print(p);
      p = p->next;
    }
  }
}

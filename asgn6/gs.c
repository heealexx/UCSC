#include "providedCode/gs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creates goodspeak structure of oldspeak newspeak
// Returns goodspeak structure
//
// oldspeak:  Oldspeak to add
// newspeak:  Newspeak to add
//
GoodSpeak *gs_create(char *oldspeak, char *newspeak) {

  GoodSpeak *gs = (GoodSpeak *)malloc(sizeof(GoodSpeak));
  if (gs) {
    if (oldspeak != NULL) {
      char *s = calloc(strlen(oldspeak) + 1, sizeof(char));
      if (s) {
        s = strcpy(s, oldspeak);
        gs->oldspeak = s;
      } else {
        printf("error with calloc");
        return NULL;
      }
    } else {
      gs->oldspeak = NULL;
    }
    if (newspeak != NULL) {
      char *s = calloc(strlen(newspeak) + 1, sizeof(char));
      if (s) {
        s = strcpy(s, newspeak);
        gs->newspeak = s;
      } else {
        printf("error calloc");
        return NULL;
      }
    } else {
      gs->newspeak = NULL;
    }
  }
  return gs;
}

// Frees memory allocated by goodspeak struct
//
// g:	Goodspeak struct to free
//
void gs_delete(GoodSpeak *g) {

  if (g) {
    free(g->oldspeak);
    free(g->newspeak);
    free(g);
  }
}

// Returns oldspeak of goodspeak struct
//
// g:	Goodspeak struct
//
char *gs_oldspeak(GoodSpeak *g) {

  if (g) {
    return g->oldspeak;
  }
  return NULL;
}

// Returns newspeak of goodspeak struct
//
// g:	Goodspeak struct
//
char *gs_newspeak(GoodSpeak *g) {

  if (g) {
    return g->newspeak;
  }
  return NULL;
}

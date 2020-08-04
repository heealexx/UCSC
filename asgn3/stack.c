#include "stack.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MINIMUM 26
#define upcase 65


Stack *stack_create(void) {

  Stack *stack = (Stack *)malloc(sizeof(Stack));
  if (stack == NULL) {
    printf("error null");
  }
  stack->capacity = MINIMUM;
  stack->top = 0;
  stack->items = (uint32_t *)calloc(MINIMUM, sizeof(uint32_t));
  return stack;
}

void stack_delete(Stack *stack) { free(stack->items); }

bool stack_empty(Stack *stack) {

  if (stack->top == 0) {
    printf("true");
    return true;
  } else {
    return false;
  }
}

uint32_t stack_size(Stack *stack) { return stack->top; }

bool stack_push(Stack *stack, uint32_t item) {

  if (stack->top == stack->capacity) {
    stack->capacity *= 2;
    stack->items =
        (uint32_t *)realloc(stack->items, stack->capacity * sizeof(uint32_t));
  }

  stack->items[stack->top] = item;
  stack->top += 1;

  return true;
}

bool stack_pop(Stack *stack, uint32_t *item) {

  if (stack->top <= 0) {
    return false;
  } else {
    item = &stack->items[stack->top - 1];
    stack->top -= 1;
    return true;
  }
}

void stack_print(Stack *s) {

  printf("Found path: ");
  for (uint32_t i = 0; i < s->top; i++) {
    if (i == s->top - 1) {
      printf("%c", s->items[i] + upcase);
    } else {
      printf("%c -> ", s->items[i] + upcase);
    }
  }
  printf("\n");
}

// stack.h - contains stack definitions

#ifndef __STACK_H__	// checks if defined already
#define __STACK_H__

#include <inttypes.h>
#include <stdbool.h>

#define MINIMUM 26

//
// Definition of stack, allocated memory to hold values
//
// items: stack holds uint32_t
// top: top of stack, number of elements
// capacity: amount of space in stack
//
typedef struct Stack {
  uint32_t *items;
  uint32_t top;
  uint32_t capacity;
} Stack;

// Creates and returns a stack
Stack *stack_create(void);

// Frees the stack, deleting it and freeing memory
void stack_delete(Stack *stack);

// Checks if stack is empty, returns true if empty, false if not
bool stack_empty(Stack *stack);

// Returns the number of elements in stack
uint32_t stack_size(Stack *stack);

// Pushes item into stack, returns true if successful
// item: element being pushed
bool stack_push(Stack *stack, uint32_t item);

// Pops item off of stack, returns true if successful
// item: pointer holding element being popped
bool stack_pop(Stack *stack, uint32_t *item);

// Prints stack, depending on program specifications
void stack_print(Stack *stack);
#endif

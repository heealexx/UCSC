#include "stack.h"

#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OPTIONS "udmi: "
#define vertices 26
#define upcase 65
#define lowcase 97

int read_file(FILE *fp, int matrix[vertices][vertices]);
int print_matrix(int matrix[vertices][vertices]);
void dfs(Stack *stack, uint32_t junc);

int matrix[vertices][vertices] = {{0}};
bool visited[vertices] = {false};
int found = 0;
uint32_t shortest = vertices;
bool undirected = true;
bool inerror = false;

// Parse through arguments for flags
// Calls DFS with stack made in main to solve maze
// Calls print maze if flag detected
int main(int argc, char **argv) {

  int c = 0;
  bool print = false;
  bool isfile = false;
  char *infile;
  FILE *fp = stdin;
  bool directed = false;

  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'i':
      infile = optarg;
      isfile = true;
      break;
    case 'u':
      undirected = true;
      break;
    case 'd':
      directed = true;
      break;
    case 'm':
      print = true;
      break;
    default:
      fp = stdin;
      undirected = true;
      break;
    }
  }

  if (undirected && directed) {
    printf("Can't be undirected and directed\n");
    return -1;
  }

  if (isfile) {
    fp = fopen(infile, "r");
  }
  read_file(fp, matrix);

  if (print) {
    print_matrix(matrix);
  }

  Stack *stack = stack_create();
  dfs(stack, 0);
  stack_delete(stack);

  if (inerror == true){		// if input error, ends program
	return -1;
  }else if (found == 0){
	printf("No paths found!\n");
  }else{
  	printf("Number of paths found: %d\n", found);
  	printf("Length of shortest path found: %u\n", shortest);
  }

  return 0;
}

// Reads file from fp, line by line
// Changes input pairs to corresponding number and makes matrix of maze
// 
// fp: pointer to file stream, whether it is stdin or inputted file
// matrix: matrix passed to be altered, so it can add 1
//
int read_file(FILE *fp, int matrix[vertices][vertices]) {

  char x, y;
  int row, col;

  if (fp == NULL) {
    printf("error");
    return -1;
  }

  while (fscanf(fp, "%c%c\n", &x, &y) != EOF) {
    if (isalpha(x) && isalpha(y)) {	// checks if input is letter
      if (isupper(x)) {			// checks which case letter is in
        row = (int)(x - upcase);
      } else {
        row = (int)(x - lowcase);
      }
      if (isupper(y)) {
        col = (int)(y - upcase);
      } else {
        col = (int)(y - lowcase);
      }

      matrix[row][col] = 1;
      if (undirected) {
        matrix[col][row] = 1;
      }
    } else {
      inerror = true;
      printf("Nodes must be between the range of A - Z!\n");
      return -1;
    }
  }

  return 0;
}

// Prints matrix of 0 and 1, representing maze
//
// matrix: matrix of 0 and 1/
int print_matrix(int matrix[vertices][vertices]) {

  for (int i = 0; i < vertices; i++) {
    printf("  %c", (char)(i + upcase));
  }
  printf("\n");
  for (int i = 0; i < vertices; i++) {
    printf("%c", (char)(i + upcase));
    for (int j = 0; j < vertices; j++) {
      printf(" %d ", matrix[i][j]);
    }
    printf("\n");
  }

  return 0;
}

// When called, dfs explores all the possible paths from a junction
// Utilizes the stack, and when stack hits the end, it prints the path
//
// stack: stack to be used to store current path
// junc: current junc, will explore edges connected to this junction
void dfs(Stack *stack, uint32_t junc) {

  uint32_t *poped = 0;
  if (junc == 25) {
    stack_push(stack, junc);
    stack_print(stack);
    found += 1;
    if (stack_size(stack) < shortest) {
      shortest = stack_size(stack);
    }
    return;
  }

  visited[junc] = true;
  stack_push(stack, junc);

  for (int i = 0; i < vertices; i++) {
    if (matrix[junc][i] == 1 & visited[i] == false) {
      dfs(stack, i);
      stack_pop(stack, poped);
    }
  }

  visited[junc] = false;

  return;
}

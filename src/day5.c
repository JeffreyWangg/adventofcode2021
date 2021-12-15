
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "day5.h"

#define SWAP(x, y) { int SWAP = x; x = y; y = SWAP; };

#define N 1000
int board[N][N] = {0};

struct line {
  int x1;
  int y1;
  int x2;
  int y2;
};

#define lines_cap 512
struct line lines[lines_cap];
int lines_size = 0;
char* ptr;

void day5(int argc, char *argv[]) {
	char* firstset = malloc(8);
	char* secondset = malloc(8);
  for (int i = 1; i < argc - 1; i = i + 3) {
	strcpy(firstset, argv[i]);
	strcpy(secondset, argv[i + 2]);

	char* firstsetx = strtok(firstset, ",");
	char* firstsety = strtok(NULL, ",");
	char* secondsetx = strtok(secondset, ",");
	char* secondsety = strtok(NULL, ",");

    lines[lines_size].x1 = (int)strtol(firstsetx, &ptr, 10);
    lines[lines_size].x2 = (int)strtol(secondsetx, &ptr, 10);
    lines[lines_size].y1 = (int)strtol(firstsety, &ptr, 10);
    lines[lines_size].y2 = (int)strtol(secondsety, &ptr, 10);
    lines_size++;
  }

  // Problema 1
  {
    int count = 0;

    int curr = 0;
    while (curr < lines_size) {
      int x1 = lines[curr].x1;
      int x2 = lines[curr].x2;
      int y1 = lines[curr].y1;
      int y2 = lines[curr].y2;
      curr++;

      if (x1 != x2 && y1 != y2) continue; // diagonal

      if (x1 > x2) SWAP(x1, x2)
      if (y1 > y2) SWAP(y1, y2)

      for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
          if (board[y][x] == 1) count++;
          board[y][x]++;
        }
      }
    }

    printf("Answer 1: %d\n", count);
  }

  memset(board, 0, N * N * sizeof(int));

  // Problema 2
  {
    int count = 0;

    int curr = 0;
    while (curr < lines_size) {
      int x1 = lines[curr].x1;
      int x2 = lines[curr].x2;
      int y1 = lines[curr].y1;
      int y2 = lines[curr].y2;
      curr++;

      if (x1 != x2 && y1 != y2) { // diagonal
        int yDir = y2 > y1 ? 1 : -1;

        if (x2 > x1) {
          for (int x = x1; x <= x2; x++) {
            int y = y1 + (x - x1) * yDir;
            if (board[y][x] == 1) count++;
            board[y][x]++;
          }
        } else {
          for (int x = x1; x >= x2; x--) {
            int y = y1 + (x1 - x) * yDir;
            if (board[y][x] == 1) count++;
            board[y][x]++;
          }
        }
      } else {
        if (x1 > x2) SWAP(x1, x2)
        if (y1 > y2) SWAP(y1, y2)

        for (int x = x1; x <= x2; x++) {
          for (int y = y1; y <= y2; y++) {
            if (board[y][x] == 1) count++;
            board[y][x]++;
          }
        }
      }
    }

    printf("Answer 2: %d\n", count);
  }
}

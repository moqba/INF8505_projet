//  file: sort.c

// Called function:  (locate maximum value in array)

#include "stdio.h"

const int WORD_MAX = 0x7fff;

int find_min_location(int A[], int start, int len) {
  int U = WORD_MAX;
  int loc = -1;
  [[chess::min_loop_count(2)]]
  for (int i = start; i < len; i++) {
    if (A[i] < U) {
      U = A[i];
      loc = i;
    }
  }
  return loc;
}

// Called function:  (sort array)

void sort(int A[], int len) {
  for (int i = 0 ; i < len-1; i++) {
    int loc = find_min_location(A,i,len);
    int temp = A[i];
    A[i] = A[loc];
    A[loc] = temp;
  }
}

// Driver :

int some_array[] = {-15, -20, 30, 40, 60, -300, 35, 45, 285, 80};

#ifdef NO_HOSTEDIO
#define PRINTF(...)
#else
#define PRINTF(...) { printf(__VA_ARGS__); }
#endif

int main() {
  int const N = sizeof(some_array) / sizeof(int);

  PRINTF("unsorted:");
  for (int i = 0; i < N; i++) PRINTF(" %d", some_array[i]);
  PRINTF("\n");

  chess_profile_begin();
  sort(some_array, N);
  chess_profile_end();

  PRINTF("sorted:");
  for (int i = 0; i < N; i++) PRINTF(" %d", some_array[i]);
  PRINTF("\n");

  return 0;
}

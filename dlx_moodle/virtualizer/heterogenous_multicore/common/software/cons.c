#include <stdio.h>
#include <stdlib.h>

/* shared stuff */
volatile char* array = (char*) 0x0;
volatile char* counter = (char*) 0x40;
volatile char* turn = (char*) 0x41;

void consumer(int rounds)
{
  int ncons;
  while(rounds) {
    ncons = (rand() % 10) + 1;
    while (*turn != 1);
    while (ncons > 0) {
      if (*counter == 0) {
        printf("Consumer: Array is empty!!\n");
        break;
      } else {      
        (*counter)--;
        printf("Consumer: consumed %d at array[%d]\n", *(array + *counter), *counter);
      }
      ncons--;
    }
    *turn = 0;
    rounds--;
  }
}


int main()
{
  consumer(100);
  return 0;
}

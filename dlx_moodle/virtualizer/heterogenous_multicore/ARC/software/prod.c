#include <stdio.h>
#include <stdlib.h>

/* shared stuff */
volatile char* array = (char*) 0x90000000;
volatile char* counter = (char*) 0x90000040;
volatile char* turn = (char*) 0x90000041;

void producer(int rounds)
{
  int i = 0, nprod;
  while(rounds) {
    nprod = (rand() % 10) + 1;
    while (*turn != 0);
    while (nprod > 0) {
      if (*counter == 50) {
        printf("Producer: Array is full!!\n");
        break;
      } else {      
        *(array + *counter) = i;
        printf("Producer: produced %d at array[%d]\n", i, *counter);
        fflush(stdout);
        (*counter)++;
      }
      nprod--;
    }
    *turn = 1;
    i = i + 1;
    if (i > 100) i = 0;
    rounds--;
  }
}

int main()
{
    producer(100);
    return 0;
}

void _sys_exit(int return_code)
{
  while (1);
}

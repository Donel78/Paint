#include "main.h"

void *draw(void *arg)
{
  while (1)
  {
    printf("draw\n");
  }

    pthread_exit(NULL);
}



#include "project1.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  
  
  for(size_t i = 0; i < 5; i++){
    int *ptr = ff_malloc(128);
    printf("%d",*ptr);
  }
  
  
  return EXIT_SUCCESS;
}

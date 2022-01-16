#include "project1.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  
  int *ptr = NULL;
  for(size_t i = 0; i < 5; i++){
    ff_free(ptr);
  }
  
  
  return EXIT_SUCCESS;
}

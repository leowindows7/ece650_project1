#include "project1.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  
  block *ptr;
  for(size_t i = 0; i < 5; i++){
    ptr = ff_malloc(128);
    // printf("%d",*ptr);
    // printf("%ld\n", get_data_segment_size());
  }
  ptr =(block *) ((char*)ptr - sizeof(block));
 
  print_blocks();
  printf("%ld\n", ptr->size);
  
  return EXIT_SUCCESS;
}

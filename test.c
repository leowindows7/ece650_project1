#include "project1.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  
  block *ptr1;
  block *ptr2;
  //for(size_t i = 0; i < 5; i++){
    ptr1 = ff_malloc(128);
    print_blocks();
    ptr2 = ff_malloc(128);
    print_blocks();
    ff_free(ptr2);
    print_blocks();
    ff_free(ptr1);
    print_blocks();
	  
    // printf("%d",*ptr);
    // printf("%ld\n", get_data_segment_size());
    // }
  //ptr = (block *) ((char*)ptr - sizeof(block)); 
  
  // printf("%ld\n", ptr->size);
  
  return EXIT_SUCCESS;
}

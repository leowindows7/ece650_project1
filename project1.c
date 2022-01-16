#include "project1.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

block * head_block = NULL;
block * tail_block = NULL;
size_t data_size = 0;
size_t free_space = 0;

void *ff_malloc(size_t size){
  block * new_block = head_block;
  if(new_block == NULL){
    new_block = sbrk(size + sizeof(block));
    new_block->size = size;
    new_block->prev = NULL;
    new_block->next = NULL;
    new_block->isFree = 0;
    data_size += size + sizeof(block);
    head_block = new_block;
    tail_block = new_block;
    printf("Head block Added! data size = %ld\n",data_size);
    
  } else {
    // may use exisiting block or generate a new block
    while (new_block->next != NULL) {
       new_block = new_block->next;
    }
    new_block->next->size = size;
    new_block->next->prev = NULL;
    new_block->next->next = NULL;
    new_block->next->isFree = 0;
    data_size += size + sizeof(block);
    printf("New Block Added! data size = %ld\n",data_size);
  }
   
  return (char *)new_block + sizeof(block);
  
}

void ff_free(int *ptr){
  printf("Hello World bitch\n");
}


unsigned long get_data_segment_size() {
  return data_size;
}

unsigned long get_data_segment_free_space_size() {
  return free_space;
}

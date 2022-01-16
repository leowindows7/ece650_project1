#include "project1.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

block * head_block = NULL;
//block * tail_block = NULL;
size_t data_size = 0;
size_t free_space = 0;


void print_blocks(){
  block * curr = head_block;
  int i = 0;
  while (curr != NULL) {
    printf("%d(%ld)->", i, curr->size);
    curr = curr->next;
    i += 1;
  }
  printf("\n");
}


void *add_new_block(block * curr_block, size_t size, block * pre_block){
    block * new_block = sbrk(size + sizeof(block));
    new_block->size = size;
    new_block->prev = pre_block;
    new_block->next = NULL;
    new_block->isFree = 0;
    return new_block;
}



void *split_block(){

}



void *ff_malloc(size_t size){
  block * curr_block = head_block;
  if(curr_block == NULL){
    curr_block = add_new_block(curr_block,size,NULL);
    data_size += size + sizeof(block);
    head_block = curr_block;
    // printf("Head block Added! data size = %ld\n",data_size);
   
  } else {
    // may use exisiting block or generate a new block
    block * currPre_block = NULL;
    while (curr_block != NULL) {
      if(curr_block->size >= size) {
	return split_block(curr_block,size);
      }
      currPre_block = curr_block;
      curr_block = curr_block->next;
    }
    curr_block = add_new_block(curr_block,size,currPre_block);
    currPre_block->next = curr_block; 
    data_size += size + sizeof(block);
   
  }
   
   return (char *)curr_block + sizeof(block);
 
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

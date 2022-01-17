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
    printf("%d(%ld,%d)->", i, curr->size,curr->isFree);
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


/*void *split_block(block * curr_block, size_t size){
 if (curr_block->size > size + sizeof(block)) {
    block * splitted_block;
    splitted_block = (block *)((char *)curr_block + sizeof(block) + size);
    splitted_block->size = curr_block->size - size - sizeof(block);
    splitted_block->isFree = 1;
    splitted_block->next = NULL;
    splitted_block->prev = NULL;

    //remove_block(p);
    // add_block(splitted_block);
    curr_block->size = size;
    free_space -= (size + sizeof(block));
  }
  else {
    //remove_block(p);
    free_space -= (curr_block->size + sizeof(block));
  }
  curr_block->isFree = 0;
  curr_block->next = NULL;
  curr_block->prev = NULL;
  return (char *)curr_block + sizeof(block);
  }*/



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
	//return split_block(curr_block,size);
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

void check_merge(){
  block * curr = head_block;
  while (curr != NULL) {
   if ((curr->next != NULL) && ((char *)curr + curr->size + sizeof(block) == (char *)curr->next)) {
     curr->size += sizeof(block) + curr->next->size;
     curr->next->next = NULL;
     curr->next->prev = NULL;
   }
   if ((curr->prev != NULL) && ((char *)curr->prev + curr->prev->size + sizeof(block) == (char *)curr)) {
    curr->prev->size += sizeof(block) + curr->size;
    curr->next = NULL;
    curr->prev = NULL;
   }
   curr = curr->next;
 }
}

void ff_free(void *ptr){
  block * block_toFree;
  block_toFree = (block *)((char *)ptr - sizeof(block));
  block_toFree->isFree = 1;
  free_space += block_toFree->size + sizeof(block);
  check_merge();
  //printf("%ld\n",block_toFree->size);
}


unsigned long get_data_segment_size() {
  return data_size;
}

unsigned long get_data_segment_free_space_size() {
  return free_space;
}

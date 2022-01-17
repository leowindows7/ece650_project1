#include "project1.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

block *head_block = NULL;
block *free_list_head = NULL;
size_t data_size = 0;
size_t free_space = 0;

void print_blocks() {
  block *curr = free_list_head;
  int i = 0;
  while (curr != NULL) {
    printf("%d(%ld,%d)->", i, curr->size, curr->isFree);
    curr = curr->next;
    i += 1;
  }
  printf("\n");
}

/*void *add_new_block(block *curr_block, size_t size, block *pre_block) {
  block *new_block = sbrk(size + sizeof(block));
  new_block->size = size;
  new_block->prev = pre_block;
  new_block->next = NULL;
  new_block->isFree = 0;
  return new_block;
  }*/

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

void *ff_malloc(size_t size) {
  block *curr_block = head_block;
  if (curr_block == NULL) {
    data_size += size + sizeof(block);
    block *new_block = sbrk(size + sizeof(block));
    new_block->size = size;
    new_block->prev = NULL;
    new_block->next = NULL;
    head_block = new_block;
    curr_block = new_block;
    new_block->isFree = 0;
    // printf("Head block Added! data size = %ld\n",data_size);

  } else {
    // may use exisiting block or generate a new block
    curr_block = free_list_head;
    printf("enter malloc");
    while (curr_block != NULL) {
      if (curr_block->size >= size) {
        // return split_block(curr_block,size);
      }
      curr_block = curr_block->next;
    }
    data_size += size + sizeof(block);
  }

  return (char *)curr_block + sizeof(block);
}

void add_block(block *block_toAdd) {
  if (free_list_head == NULL) {
    free_list_head = block_toAdd;
    return;
  }

  block_toAdd->next = free_list_head;
  free_list_head->prev = block_toAdd;
  free_list_head = block_toAdd;
}

void check_merge(block *block_toFree) {

  int merge_occur = 0;
  block *curr = free_list_head;
  block *block_toFree_ass =
      (block *)((char *)block_toFree + block_toFree->size + sizeof(block));
  while (curr != NULL) {
    block *curr_ass = (block *)((char *)curr + curr->size + sizeof(block));
    if (curr == block_toFree_ass) {
      // remove curr
      // remove_block(curr) {}
      // insert new block to list
      merge_occur = 1;
    }
    if (curr_ass == block_toFree) {
      curr->size += sizeof(block) + block_toFree->size;
      merge_occur = 1;
    }
    curr = curr->next;
  }
  if (!merge_occur) {
    add_block(block_toFree);
  }
}

void ff_free(void *ptr) {
  block *block_toFree;
  block_toFree = (block *)((char *)ptr - sizeof(block)); // go to tag

  // block_toFree->isFree = 1;
  free_space += block_toFree->size + sizeof(block);
  check_merge(block_toFree);
  // printf("%ld\n",block_toFree->size);
}

unsigned long get_data_segment_size() { return data_size; }

unsigned long get_data_segment_free_space_size() { return free_space; }

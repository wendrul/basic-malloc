#pragma once

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stdio.h>

typedef struct meta 
{
	int size; /* size in bytes */
	int is_free; /* 1 if adjacent data block is free 0 otherwise */
	struct meta *prev; /* pointer to previous block */
	struct meta *next; /* pointer to next block */
}t_meta;

t_meta	*global_base;
t_meta	*global_last;

void	my_free(void *ptr);
void	*stupid_malloc(int size);
t_meta	*extend_heap(int size);
void	print_heap_state();
void	*my_malloc(int size);

#endif

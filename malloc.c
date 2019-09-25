#include "malloc.h"
#include <stdio.h>

void	*stupid_malloc(int size) 
{
	void *ptr = sbrk(0); /* pointer to break */
	void *request = sbrk(size); /* shifts break forwards */

	if (request == (void *) -1) { /* tests if call to sbrk failed */
		return NULL;
	}
	return (ptr); /* returns pointer to memory block */
}

t_meta	*find_free_block(int size)
{
	t_meta	*current;
	
	current = global_base;
	while (current)
	{
		if (current->is_free && current->size >= size + (int)sizeof(t_meta*))
			return (current);
		current = current->next; 
	}
	return (NULL);
}

void	print_heap_state()
{
	t_meta *current;
	
	printf("***Heap State ***\n");
	current = global_base;
	while (current)
	{
		printf("address: %p size: %d, is_free: %d\n", current, current->size, current->is_free);
		current = current->next;
	}
	printf("***Heap State ***\n");
}

void	my_free(void *ptr)
{
	t_meta *meta;

	meta = (t_meta*)ptr - 1;
	meta->is_free = 1;
}

void	*my_malloc(int size) 
{
	t_meta	*meta;

	if (global_base == NULL) 
	{
		global_base = extend_heap(size);
		if (!global_base)
			return (NULL);
		return (global_base + 1);
	} 
	else
	{
		if ((meta = find_free_block(size)))
		{
			t_meta	*new;
			new = (t_meta*)((void*)(meta) + sizeof(t_meta*) + size);
			new->size = meta->size - size - (int)sizeof(t_meta*);
			new->is_free = 1;
			meta->size = size;
			meta->is_free = 0;
			new->next = meta->next;
			new->prev = meta;
			meta->next = new;
			return (meta + 1);
		}
		else
		{
			if (!(meta = extend_heap(size)))
				return (NULL);
			return (meta + 1);
		}
		return (NULL);
	}
}

t_meta	*extend_heap(int size)
{
	t_meta	*new_block;
	void	*request;

	new_block = sbrk(0);
	if ((request = sbrk(size + sizeof(t_meta*))) == (void*) -1)
		return (NULL);
	new_block->is_free = 0;
	new_block->size = size;
	new_block->next = NULL;
	new_block->prev = global_last;
	if (global_last != NULL)
		global_last->next = new_block;
	global_last = new_block;
	return (new_block);
}

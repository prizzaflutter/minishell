#include "minishell.h"

void	free_element_gc_malloc(t_gc *gc)
{
	gc_clear(gc, 0);
	gc_clear(gc, 1);
	gc_clear(gc, 3);
}

void	*gc_malloc(t_gc *gc, size_t size, int is_token)
{
	void		*ptr;
	t_gc_node	*new;

	ptr = malloc(size);
	if (!ptr)
	{
		free_element_gc_malloc(gc);
		exit(1);
	}
	if (gc_exist(gc, ptr))
		return (ptr);
	new = malloc(sizeof(t_gc_node));
	if (!new)
	{
		free(ptr);
		free_element_gc_malloc(gc);
		exit(1);
	}
	new->ptr = ptr;
	new->next = gc->head;
	new->is_token = is_token;
	gc->head = new;
	return (ptr);
}

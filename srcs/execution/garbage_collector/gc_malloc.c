/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:52:26 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/16 11:33:00 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*gc_malloc(t_gc *gc, size_t size, int is_token)
{
	void		*ptr;
	t_gc_node	*new;

	ptr = malloc(size);
	if (!ptr)
	{
		gc_clear(gc, 0);
		gc_clear(gc, 1);
		gc_clear(gc, 3);
		exit(1);
	}
	if (gc_exist(gc, ptr))
		return (ptr);
	new = malloc(sizeof(t_gc_node));
	if (!new)
	{
		free(ptr);
		gc_clear(gc, 0);
		gc_clear(gc, 1);
		gc_clear(gc, 3);
		exit(1);
	}
	new->ptr = ptr;
	new->next = gc->head;
	new->is_token = is_token;
	gc->head = new;
	return (ptr);
}

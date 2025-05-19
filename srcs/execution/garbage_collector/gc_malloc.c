/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:52:26 by iaskour           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/16 11:33:00 by iaskour          ###   ########.fr       */
=======
/*   Updated: 2025/05/16 15:01:26 by aykassim         ###   ########.fr       */
>>>>>>> 2fa37c4e5b80c6d798fe369874d7f7d9862a6be9
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
<<<<<<< HEAD
		gc_clear(gc, 0);
		gc_clear(gc, 1);
		gc_clear(gc, 3);
=======
		gc_clear(gc, 1);
		gc_clear(gc, 3);
		gc_clear(gc, 0);
>>>>>>> 2fa37c4e5b80c6d798fe369874d7f7d9862a6be9
		exit(1);
	}
	if (gc_exist(gc, ptr))
		return (ptr);
	new = malloc(sizeof(t_gc_node));
	if (!new)
	{
		free(ptr);
<<<<<<< HEAD
		gc_clear(gc, 0);
		gc_clear(gc, 1);
		gc_clear(gc, 3);
=======
		gc_clear(gc, 1);
		gc_clear(gc, 3);
		gc_clear(gc, 0);
>>>>>>> 2fa37c4e5b80c6d798fe369874d7f7d9862a6be9
		exit(1);
	}
	new->ptr = ptr;
	new->next = gc->head;
	new->is_token = is_token;
	gc->head = new;
	return (ptr);
}

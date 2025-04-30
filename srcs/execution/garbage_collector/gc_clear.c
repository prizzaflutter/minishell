/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:55:02 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/30 16:42:47 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gc_clear(t_gc *gc, int is_token)
{
	t_gc_node	*curr;
	t_gc_node	*prev;
	t_gc_node	*next;

	curr = gc->head;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		if (curr->is_token == is_token)
		{
			if (prev)
				prev->next = next;
			else
				gc->head = next;
			if (curr->ptr)
				free(curr->ptr);
			free(curr);
		}
		else
			prev = curr;
		curr = next;
	}
}

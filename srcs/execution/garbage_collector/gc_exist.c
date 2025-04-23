/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_exist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:53:27 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/22 14:53:12 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gc_exist(t_gc *gc, void *ptr)
{
	t_gc_node	*current;
	current = gc->head;
	while (current)
	{
		if (current->ptr == ptr)
			return (1);
		current = current->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:55:02 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/20 12:57:09 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gc_clear(t_gc *gc)
{
	printf("the gc clear called\n");
	t_gc_node *tmp;

	while (gc->head)
	{
		tmp = gc->head;
		gc->head = gc->head->next;
		free(tmp->ptr);
		free(tmp);
	}
}

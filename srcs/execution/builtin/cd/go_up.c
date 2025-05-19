/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_up.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:16:02 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/19 12:50:08 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// just ignore the node skip it 

void	go_up(t_stack **stack)
{
	t_stack	*current;
	t_stack	*prev;

	if (!stack || !*stack)
		return ;
	current = *stack;
	if (!current->next)
	{
		free(current->path);
		free(current);
		*stack = NULL;
		return ;
	}
	while (current->next->next)
		current = current->next;
	prev = current->next;
	free(prev->path);
	
	free(prev);
	current->next = NULL;
}

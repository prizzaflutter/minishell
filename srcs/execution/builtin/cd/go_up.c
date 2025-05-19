/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_up.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:16:02 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/19 13:16:26 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_up(t_stack **stack)
{
	t_stack	*current;

	if (!stack || !*stack)
		return ;
	current = *stack;
	if (!current->next)
	{
		*stack = NULL;
		return ;
	}
	while (current->next->next)
		current = current->next;
	current->next = NULL;
}

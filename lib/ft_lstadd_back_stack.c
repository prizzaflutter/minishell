/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_stack.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:26:37 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/09 20:56:40 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_stack(t_stack **stack, t_stack *new)
{
	t_stack	*ptr;

	if (!stack || new == NULL)
		return ;
	if (*stack == NULL)
	{
		*stack = new;
	}
	else
	{
		ptr = *stack;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

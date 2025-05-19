/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_stack.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:06:33 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/19 12:45:24 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack	*ft_lstnew_stack(t_gc *gc, void	*content)
{
	t_stack	*head;

	head = gc_malloc(gc, sizeof(t_stack), 9);
	if (head == NULL)
		return (NULL);
	head->path = content;
	head->next = NULL;
	return (head);
}

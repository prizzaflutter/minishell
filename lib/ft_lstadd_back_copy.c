/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_copy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:59:33 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/19 13:26:36 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_copy(t_copy **copy, t_copy *new)
{
	t_copy	*ptr;

	if (!copy || new == NULL)
		return ;
	if (*copy == NULL)
	{
		*copy = new;
	}
	else
	{
		ptr = *copy;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

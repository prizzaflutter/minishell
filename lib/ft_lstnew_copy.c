/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:56:36 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/19 13:26:49 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_copy	*ft_lstnew_copy(t_gc *gc, void	*key, void *value)
{
	t_copy	*head;

	head = gc_malloc(gc, sizeof(t_copy), 0);
	if (head == NULL)
		return (NULL);
	head->key = key;
	head->value = value;
	head->next = NULL;
	return (head);
}

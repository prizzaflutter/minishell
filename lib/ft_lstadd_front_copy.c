/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_copy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:59:40 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/11 12:00:30 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_front_copy(t_copy **copy, t_copy *new_copy)
{
	if (!copy || new_copy == NULL)
		return ;
	new_copy -> next = *copy;
	*copy = new_copy;
}

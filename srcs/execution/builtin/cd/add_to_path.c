/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:15:43 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/12 10:20:29 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_path(t_gc *gc, char *path, t_stack **stack)
{
	t_stack	*new;

	new = ft_lstnew_stack(gc, path);
	if (!new)
		return ;
	ft_lstadd_back_stack(stack, new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:42:41 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/11 11:35:32 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmdsize(t_command *cmd)
{
	int	counter;

	counter = 0;
	if (cmd == NULL)
		return (counter);
	while (cmd->next != NULL)
	{
		counter++;
		cmd = cmd->next;
	}
	counter++;
	return (counter);
}

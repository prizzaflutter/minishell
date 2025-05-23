/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:36:19 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/23 11:59:18 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_echo(char **cmd_args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	while (cmd_args[i] && !ft_strncmp(cmd_args[i], "-n", 2))
	{
		new_line = 1;
		i++;
	}
	i = 1;
	while (cmd_args[i])
	{
		write(1, cmd_args[i], ft_strlen(cmd_args[i]));
		if (cmd_args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line == 1)
		write(1, "\n", 1);
}

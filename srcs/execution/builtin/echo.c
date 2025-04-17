/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:36:19 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/17 09:27:59 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_echo(char **cmd_args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	if (cmd_args[1] && ft_strncmp(cmd_args[1], "-n", 2) == 0)
	{
		new_line = 1;
		i++;
	}
	while (cmd_args[i])
	{
		printf("%s", cmd_args[i]);
		if (cmd_args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line == 1)
		printf("\n");
}
